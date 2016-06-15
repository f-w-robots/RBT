#include <SPI.h>

#define SS1 4
#define SS2 5

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h>
ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;
void webSocketEvent(WStype_t type, uint8_t * payload, size_t lenght) {
  switch (type) {
    case WStype_DISCONNECTED:
      break;
    case WStype_CONNECTED:
      break;
    case WStype_TEXT:
      break;
    case WStype_BIN:
      break;
  }
}

SPISettings settingsSPI(2000000, MSBFIRST, SPI_MODE0);

void setup (void)
{
  Serial.begin(115200);
  pinMode(SS1, OUTPUT);
  digitalWrite(SS1, HIGH);
  pinMode(SS2, OUTPUT);
  digitalWrite(SS2, HIGH);
  WiFiMulti.addAP("ssid", "password");
  while (WiFiMulti.run() != WL_CONNECTED) {
    delay(100);
  }
  webSocket.begin("192.168.100.4", 2500);
  webSocket.onEvent(webSocketEvent);
  Serial.println("1333");

  SPI.begin();
}

int i = 0;

uint8_t *buf2 = new uint8_t[100];
char *buf1 = new char[100];
int x = 0;

void loop (void)
{
  char c;
  if(i == 0) {
    long mi = micros();
    SPI.beginTransaction(settingsSPI);
    digitalWrite(SS1, LOW);
    
    for (const char * p = "Hello World!" ; c = *p; p++) {
      buf2[x] = SPI.transfer(c);
      x++;
    }

    buf2[x+1] = 0;
    buf2[0] = 'A';
    
    digitalWrite(SS1, HIGH);
    SPI.endTransaction();
    int delta = micros() - mi;
    webSocket.sendBIN(buf2, x);
    String(delta).toCharArray(buf1, 100);
    webSocket.sendTXT(buf1, x);
    x=0;
  }
  i++;
  if(i > 9) {
    i = 0;
  }    
  webSocket.loop();
  delay(100);
}
