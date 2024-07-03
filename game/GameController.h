#pragma once
#include "../HardwareAggregator.h"

class GameController {
private:
  HardwareAggregator& hardware;

public:
  GameController(HardwareAggregator& hardware)
    : hardware(hardware) {}

  String react(const String& message) {
    return "test";
  }
};