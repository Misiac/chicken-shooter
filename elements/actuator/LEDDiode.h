#pragma once

#include "AActuator.h"

class LEDDiode : public AActuator
{
    private:
    int pin;

   public:
    LEDDiode(int aPin)
    {
        pin = aPin;
        pinMode(aPin, OUTPUT);
    }

    virtual void turnOn() override
    {
        digitalWrite(pin, HIGH);
    }

    virtual void turnOff() override
    {
        digitalWrite(pin, LOW);
    }
};