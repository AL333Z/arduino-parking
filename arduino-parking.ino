#include "Scheduler.h"
#include "LedStripTask.h"

Scheduler sched;

void setup(){
  
  sched.init(100);
  
  int leds[] = {13, 12, 11, 10, 9 , 8};
  Task* t1 = new LedStripTask(leds, 6);
  t1->init(100);
  sched.addTask(t1);  
    
}

void loop(){
  sched.schedule();
}
