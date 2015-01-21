#include "LedStripTask.h"

#include <Arduino.h>

#define GREEN_THRESHOLD   50
#define RED_THRESHOLD     10

/**
 * Constructor of LedStripTask, given an array of pins and a Context
 */
LedStripTask::LedStripTask(int leds[], int length, Context* pContext){
  
  this->pContext = pContext;
  this->nLed = length;
  this->intervalSize = (GREEN_THRESHOLD - RED_THRESHOLD) / (length - 1);
  
  for(int i=0; i< length; i++){
    this->pin[i] = leds[i]; 
  }   
}

/**
 * Init the LedStripTask, given a period
 */
void LedStripTask::init(int period){
  
  Task::init(period);
  
  for (int i = 0; i < this->nLed; i++){
    led[i] = new Led(pin[i]); 
  }  
}
  
/**
 * Update the state of the led strip, reading the current value from context object
 */
void LedStripTask::tick(){
  
  float distance = pContext->getObjDistance();
  
  for(int i=0; i< nLed; i++){
    if (shouldSwitchOn(i, distance)) {
      led[i]->switchOn();
    } else {
      led[i]->switchOff();
    }
  }
}

/**
 * Given an index and a distance, return if the led should be on or off
 */
bool LedStripTask::shouldSwitchOn(int index, float distance){
  
  float normDistance = GREEN_THRESHOLD - distance;
  
  if(normDistance >= (this->intervalSize * index)){  
    return true;
  }
  return false;
}
