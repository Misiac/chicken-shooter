#include "../HardwareAggregator.h"

class GameController {


private:
  HardwareAggregator hardware;

public:
  GameController(HardwareAggregator hardware) {}

  String react(String message) {
    return "test";
  }
};
