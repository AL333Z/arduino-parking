
#ifndef __Buzzer_h__
#define __Buzzer_h__

#include <Arduino.h>

class Buzzer{
    
public:
  Buzzer(int pin);
  void startBuzzing();
  void stopBuzzing();

private:
  int port;
};

#endif

