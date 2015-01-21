#ifndef __THREELEDSTASK__
#define __THREELEDSTASK__

#include "Task.h"
#include "Led.h"

#define MAX_LEDS 9

class LedStripTask: public Task {

  int pin[MAX_LEDS];
  int nLed;
  Light* led[MAX_LEDS];
  
  int state;

public:

  LedStripTask(int leds[], int length);  
  void init(int period);  
  void tick();
};

#endif
