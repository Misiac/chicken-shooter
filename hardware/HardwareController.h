#pragma once

#include "../game/Target.h"
#include "elements/actuator/LEDDiode.h"
#include "elements/actuator/Buzzer.h"
#include "elements/sensor/Microswitch.h"
#include "../sound/TimerMelody.h"
#include "../sound/HitSound.h"
#include "../sound/GameStartMelody.h"
#include "../sound/WinnerMelody.h"
#include "../sound/MissSound.h"

class HardwareController {
private:
  static const int NUM_TARGETS = 4;
  Target targets[NUM_TARGETS];
  LEDDiode connectDiode;
  Buzzer buzzer;

public:
  HardwareController()
    : targets{
        Target(LEDDiode(Config::Pins::LED_TARGET_1), Microswitch(Config::Pins::MS_TARGET_1), Config::TARGET_POINTS[0]),
        Target(LEDDiode(Config::Pins::LED_TARGET_2), Microswitch(Config::Pins::MS_TARGET_2), Config::TARGET_POINTS[1]),
        Target(LEDDiode(Config::Pins::LED_TARGET_3), Microswitch(Config::Pins::MS_TARGET_3), Config::TARGET_POINTS[2]),
        Target(LEDDiode(Config::Pins::LED_TARGET_4), Microswitch(Config::Pins::MS_TARGET_4), Config::TARGET_POINTS[3])
      },
      buzzer(Config::Pins::BUZZER, Config::DEFAULT_FREQUENCY), connectDiode(Config::Pins::CONNECT_DIODE) {
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