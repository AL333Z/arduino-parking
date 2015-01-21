#include "Scheduler.h"
#include "LedStripTask.h"

Scheduler sched;

Context* pContext = new Context(4); // move context inside setup 
int i = 50;  // delete this..

void setup(){
  
  sched.init(100);
  
  Serial.begin(9600);
 
  int leds[] = {13, 12, 11, 10, 9 , 8};
  Task* t1 = new LedStripTask(leds, 6, pContext);
  t1->init(100);
  sched.addTask(t1);  
    
}

void loop(){
  
  // manually simulating values, for now
  Serial.println(i);
  pContext->setDetectedObj(i);  
  
  if (i < 0) {
    i = 50; 
  } else {
    i--; 
  }
  
  sched.schedule();

}
