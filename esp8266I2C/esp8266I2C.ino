#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>

#define MAX_MSG_LEN 255

WebSocketsClient webSocket;

char ssid[] = "kernel";
char password[] = "axtr456E";

char address[] = "192.168.1.7";
uint16_t port = 2500;
char hwid[] = "car2";
char baseUrl[] = "/";
char *url = new char[strlen(hwid) + strlen(baseUrl) + 1];

char* getUrl() {
  url[0] = 0;
  strcat(url, baseUrl);
  strcat(url, hwid);  
}

void dbgMsg(char msg[], bool newLine = true) {
  if(newLine)
    Serial.println(msg);
   else
    Serial.print(msg);
}

void webSocketEvent(WStype_t type, uint8_t *payload, size_t lenght) {
  switch (type) {
    case WStype_DISCONNECTED:
      break;
    case WStype_CONNECTED:
      for(int i = 0; payload[i] != 0; i++) 
        Serial.write(payload[i]);
      break;
    case WStype_TEXT:
      webSocket.sendTXT("x");
      break;
    case WStype_BIN:
      break;
  }
}

void setup() {
  WiFi.softAPdisconnect(true);
  
  Serial.begin(9600);
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

void loop() {
  webSocket.loop();
}

