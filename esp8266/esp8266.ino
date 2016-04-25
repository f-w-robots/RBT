#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>
#include <EEPROM.h>
#include <ESP8266HTTPClient.h>

#define MAX_MSG_LEN 256

#define PIN_LED_WIFI 2
#define PIN_LED_SOCKET 0

boolean pin_led_socket_value = LOW;

int8_t status = 0;

WebSocketsClient webSocket;

const char SYS_SSID[] = "robolight";
const char SYS_PASS[] = "robolight";

char *ssid;
char *password;

char *host;
const uint16_t port = 2500;
char *url;

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
      for (int i = 0; lenght != i; i++)
        Serial.write(payload[i]);
      break;
    case WStype_BIN:
      for (int i = 0; lenght != i; i++)
        Serial.write(payload[i]);
      break;
  }
}

uint8_t connectToWiFi(const char* ssid, const char* pass) {
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(wifiBlinkDelay);
    digitalWrite(PIN_LED_WIFI, LOW);
    delay(wifiBlinkDelay);
    digitalWrite(PIN_LED_WIFI, HIGH);
    if (WiFi.status() == WL_CONNECT_FAILED || WiFi.status() == WL_NO_SSID_AVAIL) {
      int status = WiFi.status();
      WiFi.disconnect();
      return status;
    }
  }
  return WiFi.status();
}

void loadConfig() {
  ssid = new char[32];
  for (int i = 0; i < 32; i++) {
    ssid[i] = EEPROM.read(i);
  }
  password = new char[32];
  for (int i = 32; i < 64; i++) {
    password[i - 32] = EEPROM.read(i);
  }
  host = new char[32];
  for (int i = 64; i < 96; i++) {
    host[i - 64] = EEPROM.read(i);
  }
  url = new char[32];
  for (int i = 96; i < 128; i++) {
    url[i - 96] = EEPROM.read(i);
  }
}

void updateConfig() {
  while (WiFi.status() != WL_CONNECTED) {
    connectToWiFi(SYS_SSID, SYS_PASS);
  }
  HTTPClient http;
  char* payload = new char[32];

  http.begin("http://192.168.4.1/ssid");
  http.GET();
  http.getString().toCharArray(payload, 32);
  payload[strlen(payload)] = 0;
  writeConfig(0, payload, strlen(payload));
  http.begin("http://192.168.4.1/password");
  http.GET();
  http.getString().toCharArray(payload, 32);
  payload[strlen(payload)] = 0;
  writeConfig(1, payload, strlen(payload));
  http.begin("http://192.168.4.1/host");
  http.GET();
  http.getString().toCharArray(payload, 32);
  payload[strlen(payload)] = 0;
  writeConfig(2, payload, strlen(payload));

  EEPROM.commit();
  WiFi.disconnect();
}

void writeConfig(uint8_t i, char* data, uint8_t length) {
  int j = 0;
  for (; j < 32 && j < length; j++) {
    EEPROM.write(i * 32 + j, data[j]);
  }
  EEPROM.write(i * 32 + j, 0);
}

void setup() {
  WiFi.softAPdisconnect(true);

  pinMode(PIN_LED_WIFI, OUTPUT);
  pinMode(PIN_LED_SOCKET, OUTPUT);
  digitalWrite(PIN_LED_WIFI, HIGH);
  digitalWrite(PIN_LED_SOCKET, LOW);

  Serial.begin(115200);
  delay(10);

  EEPROM.begin(512);
  loadConfig();

  while (WiFi.status() != WL_CONNECTED) {
    int status = connectToWiFi(ssid, password);
    if (status == WL_NO_SSID_AVAIL) {
      updateConfig();
      loadConfig();
    }
  }

  webSocket.begin(host, port, url);
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
