#pragma once

#include "ASensor.h"

class Microswitch : public ASensor {

private:
  int pin;


public:
  Microswitch(int aPin) {
    pin = aPin;
    pinMode(pin, INPUT_PULLUP);
  }

  virtual float sense() override {
    int read = digitalRead(pin);
    return (read == 1) ? 0.0f : 1.0f;
  }
};