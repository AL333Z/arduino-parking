#include "Scheduler.h"
#include "LedStripTask.h"
#include "DistanceAlarmTask.h"
#include "CarDetectionTask.h"
#include "MsgService.h"

Scheduler sched;

void setup(){
  
  MsgService.init("arduino-parkinig");
  //  Serial.begin(9600);
  
  sched.init(100);
  
  Context* pContext = new Context(4, 3000); // max distance: 4m, delta: 5s
  
  Task* t0 = new CarDetectionTask(3, 4, pContext);
  t0->init(100);
  sched.addTask(t0);
 
  int leds[] = {13, 12, 11, 10, 9 , 8};
  Task* t1 = new LedStripTask(leds, 6, pContext);
  t1->init(100);
  sched.addTask(t1); 
  
  Task* t2 = new DistanceAlarmTask(6, pContext);
  t2->init(100);
  sched.addTask(t2);

}

void loop(){  
  sched.schedule();
}
