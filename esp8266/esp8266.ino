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

const int slavesCount = 3;
uint8_t slaves[slavesCount] = {4, 5, 10};
SPISettings settingsSPI(2500, MSBFIRST, SPI_MODE0);

byte** inputPackages = new byte*[slavesCount];
size_t* inputPackagesSizes = new size_t[slavesCount];
byte** outputPackages = new byte*[slavesCount];
size_t* outputPackagesSizes = new size_t[slavesCount];

void webSocketEvent(WStype_t type, uint8_t *payload, size_t lenght) {
  switch (type) {
    case WStype_DISCONNECTED:
      if (status) {
        led->set(LOW, LOW);
      }
      break;
    case WStype_CONNECTED:
      status = 1;
      led->set(HIGH, LOW);
      break;
    case WStype_TEXT:
    case WStype_BIN:
      byte* newPackage = new byte[lenght - 1];
      inputPackagesSizes[payload[0]] = lenght - 1;
      for (int f = 1; f < lenght; f++) {
        newPackage[f - 1] = payload[f];
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
    outputPackages[i] = NULL;
  }

  pinMode(slaves[0], OUTPUT);
  pinMode(slaves[1], OUTPUT);
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

  byte recived = 0;

  byte *output = inputPackages[currentSlave];
  byte *input = NULL;

  int exchangeSize = 0;
  int inputSize = 0;
  int outputSize = 0;
  if (output != NULL) {
    outputSize = inputPackagesSizes[currentSlave];
  } else {
    outputSize = 0;
  }

  SPI.transfer(outputSize + 1);
  recived = SPI.transfer(0);

  if (recived != 0) {
    inputSize = recived;
    input = new byte[inputSize];
  }

  if (inputSize < outputSize) {
    exchangeSize = outputSize;
  } else {
    exchangeSize = inputSize;
  }

  for (uint8_t i = 0; i < exchangeSize; i++) {
    if (outputSize > i) {
      recived = SPI.transfer(output[i]);
    } else {
      recived = SPI.transfer(0);
    }
    if (inputSize > i) {
      input[i] = recived;
    }
  }
  if (output != NULL) delete output;
  inputPackages[currentSlave] = NULL;
  outputPackages[currentSlave] = input;
  outputPackagesSizes[currentSlave] = inputSize;

  digitalWrite(slaves[currentSlave], HIGH);
  SPI.endTransaction();

  if (outputPackages[currentSlave] != NULL) {
    webSocket->sendBIN(outputPackages[currentSlave], outputPackagesSizes[currentSlave]);
    delete outputPackages[currentSlave];
    outputPackages[currentSlave] = NULL;
  }

  nextCurrentSlave();

  webSocket->loop();
}
