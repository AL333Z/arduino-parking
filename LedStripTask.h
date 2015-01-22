#ifndef __LEDSTRIPTASK__
#define __LEDSTRIPTASK__

#include "Task.h"
#include "Led.h"
#include "Context.h"

#define MAX_LEDS 9

class LedStripTask: public Task {

  Context* pContext;
  
  enum {WAIT_MOVE, OBJ_IN_RANGE, WAIT_STOP, OBJ_STOP, OBJ_GONE} state;
  float lastDistance;
    
  long deltaTime;
  long objStoppedMovingTimeStamp;
  
  int pin[MAX_LEDS];
  Light* led[MAX_LEDS];
  
  int nLed;
  float intervalSize;

public:

  /**
   * Constructor of LedStripTask, given an array of pins and a Context
   */
  LedStripTask(int leds[], int length, Context* pContext);  

  /**
   * Init the LedStripTask, given a period
   */
  void init(int period);  
  
  /**
   * Update the state of the led strip, reading the current value from context object
   */
  void tick();
  
private:

  bool shouldSwitchOn(int pin, float distance);
  void updateLedStatus(float distance);
  void turnOffAllLeds();

};

#endif
