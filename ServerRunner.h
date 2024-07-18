#include <WebSocketServer.h>
#include "HardwareController.h"
#include "game/GameController.h"

using namespace net;

class ServerRunner {
private:
  static GameController gameController;

public:
  static void configure(WebSocketServer& wss, HardwareController& hwController) {
    static GameController gameController(hwController);

    wss.onConnection([](WebSocket& ws) {
      const auto protocol = ws.getProtocol();
      if (protocol) {
        Serial.print(F("Client protocol: "));
        Serial.println(protocol);
      }

      gameController.setWebSocket(ws);

      ws.onMessage([](WebSocket& ws, const WebSocket::DataType dataType,
                      const char* message, uint16_t length) {
         gameController.react(message);
      });

      ws.onClose([](WebSocket&, const WebSocket::CloseCode, const char*,
                    uint16_t) {
        Serial.println(F("Disconnected"));
      });

      Serial.print(F("New WebSocket Connection from client: "));
      Serial.println(ws.getRemoteIP());
    });

    wss.begin();

    Serial.println("Ending socket configuration");
  }
};