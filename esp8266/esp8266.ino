#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>

#define MAX_MSG_LEN 255

WebSocketsClient webSocket;

char ssid[] = "kernel";
char password[] = "axtr456E";

char address[] = "192.168.1.4";
uint16_t port = 2500;
char url[] = "/car2";
char msg[MAX_MSG_LEN];

int i = 0;

void processMsg(char msg[]) {
  if (msg[0] == 'S') {
    Serial.print(msg[1]);
  }
}

void webSocketEvent(WStype_t type, uint8_t *payload, size_t lenght) {
  switch (type) {
    case WStype_DISCONNECTED:
      break;
    case WStype_CONNECTED:
      webSocket.sendTXT("waiting");
      break;
    case WStype_TEXT:
      i = 0;
      while (i < MAX_MSG_LEN && payload[i] != 0) {
        msg[i] = payload[i];
        i++;
      }
      msg[i] = 0;
      processMsg(msg);
      break;
    case WStype_BIN:
      break;
  }
}

void setup() {
  Serial.begin(9600);
  delay(10);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }

  webSocket.begin(address, port, url);
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();
  if(Serial.available() > 0) {
    char response = Serial.read();
    if(response == 'w')
      webSocket.sendTXT("wait");
  }
}

