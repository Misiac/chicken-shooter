#pragma once

#include "../elements/actuator/LEDDiode.h"
#include "../elements/sensor/Microswitch.h"

class Target {
private:
  Microswitch microswitch;
  LEDDiode ledDiode;
  int pointValue;

public:
  Target(LEDDiode leddiode, Microswitch microswitchObj, int pointVal);
};