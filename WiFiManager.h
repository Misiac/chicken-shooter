using namespace net;

class WiFiManager {
public:
  static void connect(const char* ssid, const char* pass) {

      int status = WL_IDLE_STATUS;
    while (status != WL_CONNECTED) {
      Serial.print("Attempting to connect to SSID: ");
      Serial.println(ssid);
      status = WiFi.begin(ssid, pass);
      delay(4000);
    }

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  }
};