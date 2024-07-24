#pragma once

#include "../hardware/elements/actuator/LEDDiode.h"
#include "../hardware/elements/sensor/Microswitch.h"

class Target {
private:
  LEDDiode ledDiode;
  Microswitch microswitch;
  int pointValue;

public:
  Target(LEDDiode leddiode, Microswitch microswitchObj, int pointVal)
    : ledDiode(leddiode), microswitch(microswitchObj), pointValue(pointVal) {}

  LEDDiode& getLedDiode() {
    return ledDiode;
  }

  int getPointsIfHit() {
    float sense = microswitch.sense();
    if (sense == 1) {
      return pointValue;
    }
    return 0;
  }
  int getpointValue() {
    return pointValue;
  }
};