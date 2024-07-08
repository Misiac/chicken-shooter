#include <WiFiS3.h>
#include <WebSocketServer.h>
#include "PageHolder.h"
#include "WiFiManager.h"
#include "ServerRunner.h"
#include "game/Target.h"
#include "HardwareAggregator.h"
#include "data/CredentialHolder.h"

using namespace net;

WebSocketServer wss(81);
WiFiServer server(80);

CredentialHolder credentials;

void setup() {

  Serial.begin(9600);

  Target t1 = Target(LEDDiode(2), Microswitch(8), 10);
  Target t2 = Target(LEDDiode(2), Microswitch(8), 10);
  Target t3 = Target(LEDDiode(2), Microswitch(8), 10);
  Target t4 = Target(LEDDiode(2), Microswitch(8), 10);

  Buzzer buzzer(9, 2300);
  LEDDiode connectLed(5);

  HardwareAggregator hardwareAggregator(t1, t2, t3, t4, buzzer, connectLed);

  WiFiManager::connect(credentials.getSSID(),credentials.getPass());
  server.begin();
  ServerRunner::configure(wss, hardwareAggregator);
}

void loop() {
  wss.listen();

  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {

    // send the HTTP response header
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");  // the connection will be closed after completion of the response
    client.println();                     // the separator between HTTP header and body

    String html = String(HTML_CONTENT);

    client.println(html);
    client.flush();

    // give the web browser time to receive the data
    delay(50);

    // close the connection:
    client.stop();
  }
}
