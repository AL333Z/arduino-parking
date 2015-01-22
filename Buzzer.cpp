#include "Buzzer.h"
#include <Arduino.h>

Buzzer::Buzzer(int pin){
  port = pin;
}
  
void Buzzer::startBuzzing(){  
  tone(this->port, 255);
}

void Buzzer::stopBuzzing(){  
  noTone(this->port);
}

