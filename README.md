# arduino-parking
A parking lot management system, implemented with Arduino and Raspberry pi.

This project is an attempt to focus on a paradigmatic and engineering point of view in developping embedded systems.

*NB: This repo contains only the arduino skecth. For a complete running example, see instruction [here](https://github.com/AL333Z/play-parking-pi).*

#Structure

The system has 3 main tasks, modelled as *syncronous finite state machine*:
- **CarDetectionTask**, detecting the presence of a car nearby the distance sensor and comunicating that distance to the system
- **LedStripTask**, that reacts to the presence of a car nearby the sensor turning on and off a led strip (the number of leds turned on is inversely proportional to the distance of the car from the sensor)
- **DistanceAlarmTask**, that reacts to the presence of a car nearby emitting a sound (with a buzzer) that is related to the distance of the car and sending a message to the serial port when:
  - a car did arrived
  - a car did gone

The priority of each task is implicitly determined by the order in which they are added to the scheduler, in the `setup` method.
The period is 100ms for all tasks.

The interaction between each task is mediated by a shared class `Context`, that is a singleton instance containing information about the current system status.
Since we can consider state transition for each FSM (task) occurring atomically, in accessing `Context` there aren't race conditions at all.

#Tasks diagram

![](tasks.png)

#Hardware
![](arduino-parking_bb.png)

#Credits

The original idea has been taken from [here](https://sarpur.wordpress.com/2012/08/18/arduino-uno-parking-sensor/).
