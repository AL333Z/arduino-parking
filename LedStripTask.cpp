#include "LedStripTask.h"

#include <Arduino.h>

#define GREEN_THRESHOLD   1.0  //   1 m 
#define RED_THRESHOLD     0.15 //   15 cm 

LedStripTask::LedStripTask(int leds[], int length, Context* pContext){
  this->pContext = pContext;
  this->nLed = length;
  this->intervalSize = (GREEN_THRESHOLD - RED_THRESHOLD) / (length - 1);
  
  for(int i=0; i< length; i++){
    this->pin[i] = leds[i]; 
  }   
}

void LedStripTask::init(int period){ 
  Task::init(period);
 
  state = WAIT_MOVE;
  for (int i = 0; i < this->nLed; i++){
    led[i] = new Led(pin[i]); 
  }  
}
  
void LedStripTask::tick(){
  
  float distance = pContext->getObjDistance();  
  //  Serial.print("Current distance: ");   Serial.println(distance);
  
  switch (state) {
  case WAIT_MOVE:
//    Serial.println("WAIT_MOVE");
    if (pContext->isObjDetected() && distance <= GREEN_THRESHOLD){
      state = OBJ_IN_RANGE;
    }
    break;
  case OBJ_IN_RANGE:
//    Serial.println("OBJ_IN_RANGE");

    objStoppedMovingTimeStamp =  millis();
    
    if (pContext->compareDistances(lastDistance, distance)) {
      state = WAIT_STOP;
    } else if (!pContext->isObjDetected()) {
      state = OBJ_GONE;
    }

    updateLedStatus(distance);

    break;
  case WAIT_STOP:  
//    Serial.println("WAIT_STOP");

    if (!pContext->compareDistances(lastDistance, distance)) {
      state = OBJ_IN_RANGE;
      updateLedStatus(distance);
    } else {
      int dt = millis() - objStoppedMovingTimeStamp;
      if (dt > pContext->getDeltaTime()){
        state = OBJ_STOP;
        turnOffAllLeds();
      }
    }
    
    break;
  
  case OBJ_STOP:  
//    Serial.println("OBJ_STOP");
   
    if (!pContext->compareDistances(lastDistance, distance)) {
      state = OBJ_IN_RANGE;
    } else if (!pContext->isObjDetected()) {
      state = OBJ_GONE;
    }
    break;
  
  case OBJ_GONE:  
//    Serial.println("OBJ_GONE");
    
    state = WAIT_MOVE;
    
    break;
  }
  
  lastDistance = distance;
}

void LedStripTask::updateLedStatus(float distance){
    for(int i=0; i< nLed; i++){
      if (shouldSwitchOn(i, distance)) {
        led[i]->switchOn();
      } else {
        led[i]->switchOff();
      }
    }
}

void LedStripTask::turnOffAllLeds(){
  for(int i=0; i< nLed; i++){
    led[i]->switchOff();
  }
}

bool LedStripTask::shouldSwitchOn(int index, float distance){
  float normDistance = GREEN_THRESHOLD - distance;
  return (normDistance >= (this->intervalSize * index));
}
