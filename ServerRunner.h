#include <WebSocketServer.h>
#include "HardwareAggregator.h"
#include "game/GameController.h"

using namespace net;

class ServerRunner {

private:
  static GameController gameController;

public:
  static void configure(WebSocketServer &wss, HardwareAggregator hwAggregator) {
    static GameController gameController(hwAggregator);

    wss.onConnection([](WebSocket &ws) {
      const auto protocol = ws.getProtocol();
      if (protocol) {
        Serial.print(F("Client protocol: "));
        Serial.println(protocol);
      }

      ws.onMessage([](WebSocket &ws, const WebSocket::DataType dataType,
                      const char *message, uint16_t length) {
        Serial.print(F("Received: "));
        Serial.println(message);

        String reply = gameController.react(message);
        Serial.println(reply);
        ws.send(dataType, reply.c_str(), reply.length());
      });

      ws.onClose([](WebSocket &, const WebSocket::CloseCode, const char *,
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
