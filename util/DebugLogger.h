#pragma once
#include <Arduino.h>
#include "../data/Config.h"

class DebugLogger {
public:
  static void log(const String& message) {
    if (Config::DEBUG_MODE) {
      Serial.println(message);
    }
  }

  static void log(const String& label, const String& message) {
    if (Config::DEBUG_MODE) {
      Serial.print(label);
      Serial.print(": ");
      Serial.println();
      Serial.println(message);
    }
  }

  static void log(const String& label, int value) {
    if (Config::DEBUG_MODE) {
      Serial.print(label);
      Serial.print(": ");
      Serial.println();
      Serial.println(value);
    }
  }
};