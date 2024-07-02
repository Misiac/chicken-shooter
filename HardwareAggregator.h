#pragma once

#include "game/Target.h"
#include "elements/actuator/LEDDiode.h"
#include "elements/actuator/Buzzer.h"

class HardwareAggregator {
private:
  static const int NUM_TARGETS = 4;
  Target targets[NUM_TARGETS];
  LEDDiode connectDiode;
  Buzzer buzzer;

public:
  HardwareAggregator(Target target1, Target target2, Target target3, Target target4, Buzzer buzzer, LEDDiode connectLed)
    : targets{ target1, target2, target3, target4},
      buzzer(buzzer),                                 
      connectDiode(connectLed)                        
  {
  
  } 
};