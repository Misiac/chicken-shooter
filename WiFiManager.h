#pragma once

using namespace net;

#include "data/Config.h"
#include <WiFiS3.h>

class WiFiManager {
public:
  static void connect() {
    int status = WL_IDLE_STATUS;
    while (status != WL_CONNECTED) {
      Serial.print("Attempting to connect to SSID: ");
      Serial.println(Config::WIFI_SSID);
      status = WiFi.begin(Config::WIFI_SSID, Config::WIFI_PASSWORD);
      delay(Config::WIFI_RETRY_DELAY);
    }

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  }
};
