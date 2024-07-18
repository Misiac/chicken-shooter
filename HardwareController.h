#pragma once

#include "game/Target.h"
#include "elements/actuator/LEDDiode.h"
#include "elements/actuator/Buzzer.h"

class HardwareController {
private:
  static const int NUM_TARGETS = 4;
  Target targets[NUM_TARGETS];
  LEDDiode connectDiode;
  Buzzer buzzer;

public:
  HardwareController(Target target1, Target target2, Target target3, Target target4, Buzzer buzzer, LEDDiode connectLed)
    : targets{ target1, target2, target3, target4 },
      buzzer(buzzer),
      connectDiode(connectLed) {
  }

  int handleTargetsAndReturnPoints() {
    int points;
    for (int i = 0; i < NUM_TARGETS; ++i) {
      points = targets[i].getPointsIfHit();

      if (points > 0) {
        //hit buzzer, diode for a 0,5sec or so
        targets[i].getLedDiode().turnOn();
        break;
      }
    }

    return 0;
  }
};