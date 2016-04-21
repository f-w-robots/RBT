#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>

#define MAX_MSG_LEN 256

#define PIN_LED_WIFI 2
#define PIN_LED_SOCKET 0

#define RST_PIN 4
#define SS_PIN  2

boolean pin_led_socket_value = LOW;

int8_t status = 0;

WebSocketsClient webSocket;

char ssid[] = "robohub";
char password[] = "robohub1";

char address[] = "192.168.33.4";
uint16_t port = 2500;
char url[] = "/lh";

const uint16_t wifiBlinkDelay = 50;

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

  Serial.begin(115200);
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

  webSocket.begin(address, port, url);
  webSocket.onEvent(webSocketEvent);
}

int packageLen = 0;
int packageI = 0;
char package[256];

void readPackages() {
  if (Serial.available() > 0) {
    if (packageLen == 0) {
      packageLen = Serial.read() - 48;
    } else {
      package[packageI] = Serial.read();
      packageI++;
      if (packageI == packageLen) {
        webSocket.sendTXT(package, packageLen);
        packageLen = 0;
        packageI = 0;
      }
    }
  }
}

void loop() {
  webSocket.loop();
  readPackages();
}

