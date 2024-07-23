#pragma once

#include "AActuator.h"

class Buzzer : public AActuator {
private:
  int pin;
  int frequency;

public:
  Buzzer(int aPin, int aFrequency) {
    pin = aPin;
    frequency = aFrequency;
    pinMode(aPin, OUTPUT);
  }

  void setFrequency(int aFrequency) {
    frequency = aFrequency;
  }

  virtual void turnOn() override {
    tone(pin, frequency);
  }

  void turnOnWithFrequency(int aFrequency) {
    tone(pin, aFrequency);
  }

  virtual void turnOff() override {
    noTone(pin);
  }
};