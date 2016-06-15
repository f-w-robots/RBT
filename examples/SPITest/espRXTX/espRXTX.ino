#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h>

boolean conn = false;
ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;
void webSocketEvent(WStype_t type, uint8_t * payload, size_t lenght) {
  switch (type) {
    case WStype_DISCONNECTED:
      break;
    case WStype_CONNECTED:
      conn = true;
      Serial.write('~');
      break;
    case WStype_TEXT:
      break;
    case WStype_BIN:
      break;
  }
}

void setup (void)
{
  Serial.begin(2000000);
  WiFiMulti.addAP("ssid", "password");
  while (WiFiMulti.run() != WL_CONNECTED) {
    delay(100);
  }
  webSocket.begin("192.168.100.4", 2500);
  webSocket.onEvent(webSocketEvent);
  Serial.println("1333");

}


uint8_t *buf2 = new uint8_t[100];

int position = 0;

long iii = 0;

void loop (void)
{
  webSocket.loop();
  if (!conn) {
    while (Serial.available() > 0)
      Serial.read();
    return;
  }

  if (iii == 0) {
    char c;
    String hello = "Hello World!";

    long mi = micros();
    for (int f = 0 ; f < hello.length(); f++) {
      Serial.write(hello[f]);
    }

    while (position < hello.length()) {
      while (Serial.available() > 0) {
        buf2[position] = Serial.read();
        position++;
      }
    }
    long q = micros();
    long delta = q - mi;

    webSocket.sendBIN(buf2, position);
    char b[50];

    String str = String(mi) + " " + String(q) + " = " + String(delta);
    str.toCharArray(b, 50);
    webSocket.sendTXT(b);
    position = 0;
  }
  iii++;
  if (iii > 1000)
    iii = 0;

  delay(1);
}
