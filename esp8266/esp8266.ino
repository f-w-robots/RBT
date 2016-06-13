#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>
#include <SPI.h>

#include "Led.h"
#include "Config.h"

WebSocketsClient *webSocket;

Led *led;
Config *config;

const char SYS_SSID[] = "robolight";
const char SYS_PASS[] = "robolight";

int8_t status = 0;

const int slavesCount = 2;
uint8_t slaves[slavesCount] = {4, 5};
SPISettings settingsSPI(2000000, MSBFIRST, SPI_MODE0);

byte** inputPackages = new byte*[slavesCount];
size_t* inputPackagesSizes = new size_t[slavesCount];

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
    case WStype_BIN:     
      byte* newPackage = new byte[lenght-1];
      inputPackagesSizes[payload[0]] = lenght-1;
      for(int f = 1; f < lenght; f++) {
        newPackage[f - 1] = payload[f];
//      Serial.print("r: ");
//      Serial.println(newPackage[f - 1]);
      }
      inputPackages[payload[0]] = newPackage;
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

void configFromLH() {
  connectToWiFi(SYS_SSID, SYS_PASS, 1);
  config->loadConfig();
  led->set(HIGH, HIGH);
  while (!config->fetchConfig()) {
    delay(1000);
  }
  WiFi.disconnect();
}

void setup() {
  WiFi.softAPdisconnect(true);

  led = new Led(2, 0);

  Serial.begin(115200);

  config = new Config();

  //  configFromLH();

  config->loadConfig();

  led->set(LOW, LOW);
  connectToWiFi(config->getSsid(), config->getPass());

  webSocket = new WebSocketsClient();

  webSocket->begin(config->getHost(), 2500, String("/") + config->getUrl());
  webSocket->onEvent(webSocketEvent);

  for (int i = 0; i < slavesCount; i++) {
    inputPackages[i] = NULL;
  }

  digitalWrite(slaves[0], HIGH);
  digitalWrite(slaves[1], HIGH);
  SPI.begin();
}

int currentSlave;

void nextCurrentSlave() {
  currentSlave = currentSlave + 1;
  if (currentSlave == slavesCount)
    currentSlave = 0;
}

void loop() {
  SPI.beginTransaction(settingsSPI);
  digitalWrite(slaves[currentSlave], LOW);

  byte result = 0;
  if (inputPackages[currentSlave] != NULL) {
//    Serial.println("NN");
    byte *tmp = inputPackages[currentSlave];

    result = SPI.transfer(inputPackagesSizes[currentSlave]);
//    Serial.print("xtrasfer: ");
//    Serial.println(inputPackagesSizes[currentSlave]);

    if (result != 0) {
      // set read all package
    }

    for (uint8_t i = 0; i < inputPackagesSizes[currentSlave]; i++) {
      SPI.transfer(tmp[i]);
//      Serial.print("strasfer: ");
//      Serial.println(tmp[i]);
    }
    delete inputPackages[currentSlave];
    inputPackages[currentSlave] = NULL;
  } else {
    result = SPI.transfer(0);
    if (result != 0) {
//       read package
    }
  }
  digitalWrite(slaves[currentSlave], HIGH);
  SPI.endTransaction();

  nextCurrentSlave();
  webSocket->loop();
}
