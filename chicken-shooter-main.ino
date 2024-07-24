#include <WiFiS3.h>
#include <WebSocketServer.h>
#include "PageHolder.h"
#include "WiFiManager.h"
#include "ServerRunner.h"
#include "game/Target.h"
#include "HardwareController.h"

using namespace net;

WebSocketServer wss(Config::WEBSOCKET_PORT);
WiFiServer server(Config::HTTP_PORT);

void setup() {
  Serial.begin(Config::SERIAL_BAUD_RATE);

  WiFiManager::connect();
  server.begin();
  ServerRunner::configure(wss);
}

void loop() {
  wss.listen();

  WiFiClient client = server.available();
  if (client) {

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();

    String html = String(HTML_CONTENT);

    client.println(html);
    client.flush();

    delay(Config::GAME_LOOP_DELAY);
    client.stop();
  }
}