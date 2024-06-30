#include <Arduino.h>
#include "ASensor.h"

class Microswitch : public ASensor
{

private:
    int pin;

public:
    Microswitch(int pin)
    {
        pin = pin;
        pinMode(pin, INPUT_PULLUP);
    }

    virtual float sense() override
    {
    }
};