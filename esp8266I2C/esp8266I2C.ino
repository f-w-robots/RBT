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

char address[] = "192.168.43.252";
uint16_t port = 2500;
char hwid[] = "i2c";
char baseUrl[] = "/";
char *url = new char[strlen(hwid) + strlen(baseUrl) + 1];

char* getUrl() {
  url[0] = 0;
  strcat(url, baseUrl);
  strcat(url, hwid);  
}

String debugString;

long int time1 = 0;
long int time4 = 0;

void dbgMsg(char msg[], bool newLine = true) {
//  if(newLine) Serial.println(msg);else Serial.print(msg);
}

void webSocketEvent(WStype_t type, uint8_t *payload, size_t lenght) {
  switch (type) {
    case WStype_DISCONNECTED:
      if(status) {
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
      time1 = micros();
      for(int i = 0; payload[i] != 0; i++)
        Serial.write(payload[i]);
      break;
    case WStype_BIN:
      break;
  }
}

void setup() {
  WiFi.softAPdisconnect(true);

  pinMode(PIN_LED_WIFI, OUTPUT);
  pinMode(PIN_LED_SOCKET, OUTPUT);
  digitalWrite(PIN_LED_WIFI, HIGH);
  digitalWrite(PIN_LED_SOCKET, LOW);
  
  Serial.begin(115200);
  delay(10);
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    dbgMsg(".", false);
    delay(50);
    digitalWrite(PIN_LED_WIFI, LOW);
    delay(50);
    digitalWrite(PIN_LED_WIFI, HIGH);
  }
  getUrl();

  webSocket.begin(address, port, getUrl());
  webSocket.onEvent(webSocketEvent);
}

int incomePackageLen = 0;
int incomePackageI = 0;
char message[256];

void readPackages() {
  if(Serial.available() > 0) {
    if(incomePackageLen == 0) {
      incomePackageLen = Serial.read() - 48;
      message[incomePackageLen] = 0;
    }
    while(Serial.available() > 0) {
      message[incomePackageI] = Serial.read();
      incomePackageI++;
      if(incomePackageI == incomePackageLen) {
        incomePackageLen = 0;
        incomePackageI = 0;
        time4 = micros();
        webSocket.sendTXT(message);
        debugString = String(time4 - time1);
        webSocket.sendTXT(debugString);
      }
    }
  }
}

void loop() {
  webSocket.loop();
  readPackages();
}

