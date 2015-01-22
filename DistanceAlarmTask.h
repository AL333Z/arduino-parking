#ifndef __DISTANCEALARMTASK__
#define __DISTANCEALARMTASK__

#include "Task.h"
#include "Context.h"
#include "Buzzer.h"

class DistanceAlarmTask: public Task {

  Context* pContext;  
  int pin;
  Buzzer *buzzer;

  enum {NO_CAR, CAR_IN_RANGE, WAIT_STOP, CAR_STOP, CAR_GONE} state;
  float lastDistance;
    
  long carStoppedMovingTimeStamp;

  bool isBuzzing;
  float buzzInterval;
  long buzzDeltaTime;

public:

  /**
   * Constructor of LedStripTask, given an array of pins, a delta that 
   * indiacates how long a car has not to be moving, and a Context
   */
  DistanceAlarmTask(int pin, Context* pContext);  
  
  /**
   * Init the DistanceAlarmTask, given a period
   */
  void init(int period);  
  
  /**
   * Perform state transition of DistanceAlarmTask FSM
   */
  void tick();
  
private:
  void updateBuzzInterval(float distance);
  void updateBuzzStatus();
};

#endif
