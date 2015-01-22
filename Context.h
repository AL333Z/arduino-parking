#include "Arduino.h"

#ifndef __CONTEXT__
#define __CONTEXT__

class Context {

  bool objDetected;
  float objDistance;
  float maxDistance;
  long deltaTime; // time that has to expire to consider a car parked
  
public:

  Context(float maxDistance, float deltaTime){
    objDetected = false;  
    this->maxDistance = maxDistance;
    this->deltaTime = deltaTime;
  }
  
  void setDetectedObj(float distance){
    objDetected = true;
    objDistance = distance;  
  }
  
  void setNoObjDetected(){
    objDetected = false; 
  }
  
  bool isObjDetected(){
    return objDetected;
  }
  
  float getObjDistance(){
    return objDistance; 
  }
  
  float getMaxDistance(){
    return maxDistance; 
  }
  
  long getDeltaTime(){
    return deltaTime; 
  }
  
  // Utility method, used to check if 2 distances are equals, with a tollerance
  bool compareDistances(float d1, float d2){
    return abs(d1 - d2) < 0.02;
  }
};

#endif
