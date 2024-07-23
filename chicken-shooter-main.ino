#include <WiFiS3.h>
#include <WebSocketServer.h>
#include "PageHolder.h"
#include "WiFiManager.h"
#include "ServerRunner.h"
#include "game/Target.h"
#include "HardwareController.h"
#include "data/CredentialHolder.h"

using namespace net;

WebSocketServer wss(81);
WiFiServer server(80);

CredentialHolder credentials;

void setup() {

  Serial.begin(9600);

  WiFiManager::connect(credentials.getSSID(), credentials.getPass());
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

    delay(50);

    client.stop();
  }
}