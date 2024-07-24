#include "../AElement.h"
#pragma once

class AActuator : public AElement
{

public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;

    void turn(bool aValue)
    {
        if (true == aValue)
            turnOn();
        else
        {
            turnOff();
        }
    }
};