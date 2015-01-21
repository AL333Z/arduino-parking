#ifndef __THREELEDSTASK__
#define __THREELEDSTASK__

#include "Task.h"
#include "Led.h"
#include "Context.h"

#define MAX_LEDS 9

class LedStripTask: public Task {

  Context* pContext;
  
  int pin[MAX_LEDS];
  Light* led[MAX_LEDS];
  
  int nLed;
  float intervalSize;

public:

  LedStripTask(int leds[], int length, Context* pContext);  
  void init(int period);  
  void tick();
  
private:

  bool shouldSwitchOn(int pin, float distance);

};

#endif
