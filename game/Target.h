#pragma once

#include "../elements/actuator/LEDDiode.h"
#include "../elements/sensor/Microswitch.h"

class Target {
private:
  LEDDiode ledDiode;
  Microswitch microswitch;
  int pointValue;

public:
  Target(LEDDiode leddiode, Microswitch microswitchObj, int pointVal)
    : ledDiode(leddiode), microswitch(microswitchObj), pointValue(pointVal) {}
};