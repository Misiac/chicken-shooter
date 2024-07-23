#pragma once

#include "game/Target.h"
#include "elements/actuator/LEDDiode.h"
#include "elements/actuator/Buzzer.h"
#include "elements/sensor/Microswitch.h"
#include "sound/TimerMelody.h"
#include "sound/HitSound.h"
#include "sound/GameStartMelody.h"
#include "sound/WinnerMelody.h"
#include "sound/MissSound.h"

class HardwareController {
private:
  static const int NUM_TARGETS = 4;
  Target targets[NUM_TARGETS];
  LEDDiode connectDiode;
  Buzzer buzzer;

public:
  HardwareController()
    : targets{
        Target(LEDDiode(11), Microswitch(3), 40),
        Target(LEDDiode(11), Microswitch(3), 30),
        Target(LEDDiode(11), Microswitch(3), 20),
        Target(LEDDiode(11), Microswitch(3), 10)
      },
      buzzer(9, 2300), connectDiode(12) {
  }

  int handleTargetsAndReturnPoints() {

    int points = 0;
    for (int i = 0; i < NUM_TARGETS; i++) {
      points = targets[i].getPointsIfHit();

      if (points > 0) {
        targets[i].getLedDiode().turnOn();
        return points;
      }
    }
    return 0;
  }

  void playTimer() {
    TimerMelody::play(buzzer);
  }
  void playHit() {
    HitSound::play(buzzer);
  }
  void playStartAndTurnConnectDiode() {
    connectDiode.turnOn();
    GameStartMelody::play(buzzer);
  }
  void playWinner() {
    WinnerMelody::play(buzzer);
  }
  void playMiss() {
    MissSound::play(buzzer);
  }
  void resetTargets() {
    for (int i = 0; i < NUM_TARGETS; i++) {
      targets[i].getLedDiode().turnOff();
    }
  }
};