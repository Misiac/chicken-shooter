
#include <Arduino.h>
#include "../AElement.h"
#pragma once

class ASensor : public AElement{

int pin;

public:
  // Returns the value between 0 and 1
    virtual float sense() = 0;
};