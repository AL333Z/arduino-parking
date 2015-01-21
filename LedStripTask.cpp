#include "LedStripTask.h"

LedStripTask::LedStripTask(int leds[], int length){
  this->nLed = length;
  for(int i=0; i< length; i++){
    this->pin[i] = leds[i]; 
  }   
}
  
void LedStripTask::init(int period){
  Task::init(period);
  for (int i = 0; i < this->nLed; i++){
    led[i] = new Led(pin[i]); 
  }
  state = 0;    
}
  
void LedStripTask::tick(){
  led[state]->switchOff();
  state = (state + 1) % this->nLed;
  led[state]->switchOn();
}
