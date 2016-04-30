#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>

#include "Led.h"
#include "Config.h"
#include "Package.h"

WebSocketsClient webSocket;

Led *led;
Config *config;
Package *package;

const char SYS_SSID[] = "robolight";
const char SYS_PASS[] = "robolight";

int8_t status = 0;

void webSocketEvent(WStype_t type, uint8_t *payload, size_t lenght) {
  switch (type) {
    case WStype_DISCONNECTED:
      if (status) {
        led->set(HIGH, HIGH);
      }
      break;
    case WStype_CONNECTED:
      status = 1;
      led->set(LOW, HIGH);
      break;
    case WStype_TEXT:
      for (int i = 0; lenght != i; i++)
        Serial.write(payload[i]);
      break;
    case WStype_BIN:
      for (int i = 0; lenght != i; i++)
        Serial.write(payload[i]);
      break;
  }
}

void connectToWiFi(const char* ssid, const char* pass, boolean blinkMode = false) {
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    led->blink(blinkMode, 50);
    if (WiFi.status() == WL_CONNECT_FAILED || WiFi.status() == WL_NO_SSID_AVAIL) {
      WiFi.disconnect();
      WiFi.begin(ssid, pass);
    }
  }
}

void setup() {
  WiFi.softAPdisconnect(true);

  led = new Led(2, 0);

  Serial.begin(115200);

  connectToWiFi(SYS_SSID, SYS_PASS, 1);

  config = new Config();
  config->loadConfig();
  Serial.println(config->getSsid());
  led->set(HIGH, HIGH);
  while (!config->fetchConfig()) {
    delay(1000);
  }
  WiFi.disconnect();

  config->loadConfig();
  delete config;

  led->set(LOW, LOW);
  connectToWiFi(config->getSsid(), config->getPass());

  package = new Package(webSocket);

  webSocket.begin(config->getHost(), 2500, config->getUrl());
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();
  package->readPackages();
}
