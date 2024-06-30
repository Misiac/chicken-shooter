#include <WebSocketServer.h>

using namespace net;

class ServerRunner {
public:
  static void configure(WebSocketServer &wss) {
    wss.onConnection([](WebSocket &ws) {
      const auto protocol = ws.getProtocol();
      if (protocol) {
        Serial.print(F("Client protocol: "));
        Serial.println(protocol);
      }

      ws.onMessage([](WebSocket &ws, const WebSocket::DataType dataType,
                      const char *message, uint16_t length) {
        switch (dataType) {
          case WebSocket::DataType::TEXT:
            Serial.print(F("Received: "));
            Serial.println(message);
            break;
          case WebSocket::DataType::BINARY:
            Serial.println(F("Received binary data"));
            break;
        }

        String reply = "Received: " + String((char *)message);  
        ws.send(dataType, reply.c_str(), reply.length()); // replying
      });

      ws.onClose([](WebSocket &, const WebSocket::CloseCode, const char *,
                    uint16_t) {
        Serial.println(F("Disconnected"));
      });

      Serial.print(F("New WebSocket Connection from client: "));
      Serial.println(ws.getRemoteIP());

      const char message[]{ "Hello from Arduino server!" };  // sends message
      ws.send(WebSocket::DataType::TEXT, message, strlen(message));
    });

    wss.begin();

    Serial.println("Ending socket configuration");
  }
};
