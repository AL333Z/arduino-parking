#include "DistanceAlarmTask.h"

#include "Arduino.h"
#include "MsgService.h"

#define BUZZ_THRESHOLD       1.0   // start buzzing when < 1m
#define BUZZ_MAX_INTERVAL    1500  // 1.5 sec 

// Standard-like map function, for floats
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max){
 return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}

DistanceAlarmTask::DistanceAlarmTask(int pin, Context* pContext){
  this->pContext = pContext;
  this->pin = pin;
}

void DistanceAlarmTask::init(int period){
  Task::init(period);
  
  state = NO_CAR;
  buzzer = new Buzzer(pin);
  
  buzzer->stopBuzzing();
  isBuzzing = false;
}
    
void DistanceAlarmTask::tick(){
  float distance = pContext->getObjDistance();  
//  Serial.print("Current distance: ");   Serial.println(distance);
  
  switch (state) {
  case NO_CAR:
//    Serial.println("NO_CAR");
    if (pContext->isObjDetected() && distance <= pContext->getMaxDistance()){
      state = CAR_IN_RANGE;
      
      MsgService.sendMsgTo("centralunit","ARRIVED");
    }
    break;
  case CAR_IN_RANGE:
//    Serial.println("CAR_IN_RANGE");
    if (pContext->compareDistances(lastDistance, distance)) {
      state = WAIT_STOP;
    } else if (!pContext->isObjDetected()) {
      state = CAR_GONE;
    }
    
    carStoppedMovingTimeStamp = millis();
    
    updateBuzzInterval(distance); // car did moved, so update buzz interval
    
    if (distance > BUZZ_THRESHOLD) { // if there's no car, reset buzz delta, so the buzzer will never change state
      buzzDeltaTime =  millis();
    }
    
    updateBuzzStatus();
      
    break;
  case WAIT_STOP:  
//    Serial.println("WAIT_STOP");
    if (!pContext->compareDistances(lastDistance, distance)) {
      state = CAR_IN_RANGE;
    } else {
      int dt = millis() - carStoppedMovingTimeStamp;
      if (dt > pContext->getDeltaTime()){
        state = CAR_STOP;
      }
    }
  
    updateBuzzStatus();
  
    break;
  case CAR_STOP:  
//    Serial.println("CAR_STOP");
     
    if (isBuzzing){
      buzzer->stopBuzzing();
      isBuzzing = false;
    }  
              
    if (!pContext->compareDistances(lastDistance, distance)) {
      state = CAR_IN_RANGE;
    } else if (!pContext->isObjDetected()) {
      state = CAR_GONE;
    }
  
    break;
  case CAR_GONE: 
//    Serial.println("CAR_GONE");
  
    state = NO_CAR;
    MsgService.sendMsgTo("centralunit","GONE");
    
    break;
  }
  
  lastDistance = distance;
}

void DistanceAlarmTask::updateBuzzInterval(float distance){
  if (distance >= BUZZ_THRESHOLD){
    buzzInterval = -1;
  } else {
    buzzInterval = mapfloat(distance, 0.0, BUZZ_THRESHOLD, 100.0, BUZZ_MAX_INTERVAL);
  }
}

void DistanceAlarmTask::updateBuzzStatus(){
  int elapsedBuzzInterval = millis() - buzzDeltaTime;
  
  if (buzzInterval < 0) {
    buzzer->stopBuzzing();
    isBuzzing = false;
  } else if (elapsedBuzzInterval > buzzInterval) {
       buzzDeltaTime = millis(); // reset the count

      if (isBuzzing){
        buzzer->stopBuzzing();
        isBuzzing = false;
      } else {
        buzzer->startBuzzing();
        isBuzzing = true;
      }
  }
}

