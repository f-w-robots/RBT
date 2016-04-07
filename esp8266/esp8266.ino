#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>

#define MAX_MSG_LEN 255

#define PIN_LED_WIFI 2
#define PIN_LED_SOCKET 0

int8_t status = 0;

WebSocketsClient webSocket;

char ssid[] = "robohub";
char password[] = "robohub1";

char address[] = "192.168.33.2";
uint16_t port = 2500;
char hwid[] = "bugDebug";
char baseUrl[] = "/";

const uint16_t wifiBlinkDelay = 50;

char* url = new char[strlen(hwid) + strlen(baseUrl) + 1];
char* getUrl() {
  url[0] = 0;
  strcat(url, baseUrl);
  strcat(url, hwid);
}

//String debugString;
//long int time1 = 0;
//long int time4 = 0;

void webSocketEvent(WStype_t type, uint8_t *payload, size_t lenght) {
  switch (type) {
    case WStype_DISCONNECTED:
      if (status) {
        digitalWrite(PIN_LED_WIFI, HIGH);
        digitalWrite(PIN_LED_SOCKET, HIGH);
      }
      break;
    case WStype_CONNECTED:
      status = 1;
      digitalWrite(PIN_LED_WIFI, LOW);
      digitalWrite(PIN_LED_SOCKET, HIGH);
      break;
    case WStype_TEXT:
      //      time1 = micros();
      for (int i = 0; payload[i] != 0; i++)
        Serial.write(payload[i]);
      break;
    case WStype_BIN:
      break;
  }
}

void resetConnection() {
  WiFi.disconnect();
  for (int i = 0; i < 10; i++) {
    delay(50);
    digitalWrite(PIN_LED_SOCKET, HIGH);
    delay(50);
    digitalWrite(PIN_LED_SOCKET, LOW);
  }
}

void setup() {
  WiFi.softAPdisconnect(true);

  pinMode(PIN_LED_WIFI, OUTPUT);
  pinMode(PIN_LED_SOCKET, OUTPUT);
  digitalWrite(PIN_LED_WIFI, HIGH);
  digitalWrite(PIN_LED_SOCKET, LOW);

  Serial.begin(57600);
  delay(10);

  while (WiFi.status() != WL_CONNECTED) {

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(wifiBlinkDelay);
      digitalWrite(PIN_LED_WIFI, LOW);
      delay(wifiBlinkDelay);
      digitalWrite(PIN_LED_WIFI, HIGH);
      if (WiFi.status() == WL_CONNECT_FAILED) {
        resetConnection();
        break;
      }
    }
  }

  webSocket.begin(address, port, getUrl());
  webSocket.onEvent(webSocketEvent);
}

int packageLen = 0;
int packageI = 0;
char package[256];

void readPackages() {
  if (Serial.available() > 0) {
    if (packageLen == 0) {
      packageLen = Serial.read() - 48;
      package[packageLen] = 0;
    }
    while (Serial.available() > 0) {
      package[packageI] = Serial.read();
      packageI++;
      if (packageI == packageLen) {
        packageLen = 0;
        packageI = 0;
        //        time4 = micros();
        webSocket.sendTXT(package);
        //        debugString = String(time4 - time1);
        //        webSocket.sendTXT(debugString);
      }
    }
  }
}

void loop() {
  webSocket.loop();
  readPackages();
}

