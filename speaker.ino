/* Controlling speakers via WiFi*/

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "TjunJet";
const char* password = "vision60";

WebServer server(8000);

const int outputPin = 13;
const int ledChannel = 0;

void handleRoot() {
  server.send(200, "text/plain", "ESP32 Web Server");
}

void handleOn() {
  ledcWrite(ledChannel, 127);  // Turn on the speaker
  server.send(200, "text/plain", "Speaker is ON");
}

void handleOff() {
  ledcWrite(ledChannel, 0);  // Turn off the speaker
  server.send(200, "text/plain", "Speaker is OFF");
}

void setup() {
  pinMode(outputPin, OUTPUT);
  ledcSetup(ledChannel, 440, 8);
  ledcAttachPin(outputPin, ledChannel);

  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);

  server.begin();
}

void loop() {
  server.handleClient();
}
