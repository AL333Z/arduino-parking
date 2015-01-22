#ifndef __CARDETECTIONTASK__
#define __CARDETECTIONTASK__

#include "Task.h"
#include "Context.h"

class CarDetectionTask: public Task {

  Context* pContext;
  int echoPin;
  int trigPin;
    
public:

  /**
   * Constructor of CarDetectionTask, given trigPin and echoPin, and a Context
   */
  CarDetectionTask(int trigPin, int echoPin, Context* pContext);  
  
   /**
    * Init the CarDetectionTask, given a period
    */
  void init(int period);  
  
  /**
   * Refresh the context with update distance value
   */
  void tick();
};

#endif
