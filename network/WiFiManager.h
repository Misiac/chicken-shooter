#pragma once

#include "../data/Config.h"
#include <WiFiS3.h>
#include "../util/DebugLogger.h"

using namespace net;

class WiFiManager {
public:
  static void connect() {
    int status = WL_IDLE_STATUS;
    while (status != WL_CONNECTED) {
      if (Config::DEBUG_MODE) {
        DebugLogger::log("Attempting to connect to SSID", Config::WIFI_SSID);
      }
      status = WiFi.begin(Config::WIFI_SSID, Config::WIFI_PASSWORD);
      delay(Config::WIFI_RETRY_DELAY);
    }

    if (Config::DEBUG_MODE) {
      DebugLogger::log("IP Address", WiFi.localIP().toString());
    }
  }
};