#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>

#define MAX_MSG_LEN 255

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
      break;
    case WStype_CONNECTED:
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
  
  Serial.begin(115200);
  delay(10);
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    dbgMsg(".", false);
    delay(100);
  }
  getUrl();

  webSocket.begin(address, port, getUrl());
  webSocket.onEvent(webSocketEvent);
}

int incomePackageLen = 0;
int incomePackageI = 0;
char message[256];
char c;

void loop() {
  webSocket.loop();
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

