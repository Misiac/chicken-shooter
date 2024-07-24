#pragma once

#include "Secrets.h"

namespace Config {
// WiFi
using Secrets::WIFI_SSID;
using Secrets::WIFI_PASSWORD;

// Pin Assignments
namespace Pins {
constexpr int BUZZER = 9;
constexpr int CONNECT_DIODE = 12;

// Microswitches for targets
constexpr int MS_TARGET_1 = 3;
constexpr int MS_TARGET_2 = 3;
constexpr int MS_TARGET_3 = 3;
constexpr int MS_TARGET_4 = 3;

//Leds for targets
constexpr int LED_TARGET_1 = 11;
constexpr int LED_TARGET_2 = 11;
constexpr int LED_TARGET_3 = 11;
constexpr int LED_TARGET_4 = 11;
}

//Sound
constexpr int DEFAULT_FREQUENCY = 2300;

// Network Settings
constexpr int WEBSOCKET_PORT = 81;
constexpr int HTTP_PORT = 80;
constexpr unsigned long WIFI_RETRY_DELAY = 4000;
constexpr unsigned long GAME_LOOP_DELAY = 50;

// Game Settings
constexpr int ROUNDS_PER_GAME = 5;
constexpr int SHOOT_TIME_LIMIT = 7000;
constexpr int MAX_PLAYERS = 4;

// Target Settings
constexpr int NUM_TARGETS = 4;
constexpr int TARGET_POINTS[NUM_TARGETS] = { 40, 30, 20, 10 };

// Debug Settings
constexpr unsigned long SERIAL_BAUD_RATE = 9600;
constexpr bool DEBUG_MODE = true;
}