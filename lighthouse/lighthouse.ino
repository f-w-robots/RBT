#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>
#include <Ticker.h>

#include "Led.h"
#include "Config.h"
#include "LHServer.h"
#include "Package.h"
#include "DeviceRC522.h"

Led *led;
Config *config;
DeviceRC522 *device = NULL;
LHServer *server;
Package *package;
WebSocketsClient *webSocket;

int8_t status = 0;

const char SYS_SSID[] = "robolight";
const char SYS_PASS[] = "robolight";

char *allowIds = new char[0];

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
      // TODO - payload[0] == 0, binary
      if (payload[0] == 48) {
        // TODO - free mem
        //        delete allowIds;
        delete[] allowIds;
        allowIds = new char[lenght];
        for (int i = 1; lenght != i; i++) {
          allowIds[i - 1] = payload[i];
        }
        allowIds[lenght - 1] = 0;
        server->updateAllowIds(allowIds);
      } else {
        for (int i = 0; lenght != i; i++)
          Serial.write(payload[i]);
      }
      break;
    case WStype_BIN:
      for (int i = 0; lenght != i; i++)
        Serial.write(payload[i]);
      break;
  }
}

Ticker sta_tick;

void setup() {
  WiFi.softAP(SYS_SSID, SYS_PASS);

  Serial.begin(115200);

  webSocket = new WebSocketsClient();

  led = new Led(2, 0);
  led->set(LOW, HIGH);

  config = new Config();
  config->loadConfig();

  device = new DeviceRC522(4, 5, led);
  server = new LHServer(config, webSocket);

  WiFi.begin(config->getSsid(), config->getPass());
  sta_tick.attach(30, staCheck);

  package = new Package(webSocket);

  webSocket->begin(config->getHost(), 2500, config->getUrl());
  webSocket->onEvent(webSocketEvent);
}

void staCheck() {
  sta_tick.detach();
  if (!(uint32_t)WiFi.localIP()) {
    WiFi.mode(WIFI_AP);
  }
}

void checkInternalVirtualDevice() {
  if (device != NULL && status > 0) {
    device->tick();
    if (device->newData()) {
      webSocket->sendTXT(device->readData(), 4);
    }
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    led->set(HIGH, LOW);

    webSocket->loop();
    package->readPackages();
    checkInternalVirtualDevice();
  }
  server->handleClient();
}

