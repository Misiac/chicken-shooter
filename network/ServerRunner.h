#include <WebSocketServer.h>
#include "../hardware/HardwareController.h"
#include "../game/GameController.h"
#include "../data/Config.h"
#include "../util/DebugLogger.h"

using namespace net;

class ServerRunner {
private:
  static GameController gameController;
  static WebSocket* ws;

public:
  static void configure(WebSocketServer& wss) {
    DebugLogger::log("Configuring WebSocket Server...");

    wss.onConnection([](WebSocket& socket) {
      ws = &socket;

      const auto protocol = ws->getProtocol();
      if (protocol) {
        DebugLogger::log("Client protocol", protocol);
      } else {
        DebugLogger::log("Client protocol: None");
      }

      ws->onMessage([](WebSocket& socket, const WebSocket::DataType dataType,
                       const char* message, uint16_t length) {
        DebugLogger::log("Received message", message);
        DebugLogger::log("Message length", length);

        String response = gameController.react(String(message));
        socket.send(WebSocket::DataType::TEXT, response.c_str(), response.length());

        DebugLogger::log(F("Sent response"), response);
      });

      ws->onClose([](WebSocket&, const WebSocket::CloseCode, const char* reason,
                     uint16_t reasonLength) {
        if (reasonLength > 0) {
          DebugLogger::log(F("Disconnected. Reason"), String(reason));
        } else {
          DebugLogger::log("Disconnected. No reason provided.");
        }
        ws = nullptr;
      });
    });

    wss.begin();
    DebugLogger::log("WebSocket Server started.");
    DebugLogger::log("Ending socket configuration");
  }
};

GameController ServerRunner::gameController;
WebSocket* ServerRunner::ws = nullptr;