#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>

#include "DeviceRC522.h"

DeviceRC522 *device = NULL;

#define MAX_MSG_LEN 256

#define PIN_LED_WIFI 2
#define PIN_LED_SOCKET 0
const uint16_t wifiBlinkDelay = 50;
int8_t status = 0;

ESP8266WebServer server(80);
const char SYS_SSID[] = "robolight";
const char SYS_PASS[] = "robolight";

boolean pin_led_socket_value = LOW;

WebSocketsClient webSocket;

char *ssid;
char *password;

char *host;
const uint16_t port = 2500;
char *url;

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

void writeConfig(uint8_t i, char* data, uint8_t length) {
  int j = 0;
  for (; j < 32 && j < length; j++) {
    EEPROM.write(i * 32 + j, data[j]);
  }
  EEPROM.write(i * 32 + j, 0);
}

void startServer() {
  server.on("/ssid", []() {

    server.send(200, "text/plain", ssid);
  });

  server.on("/password", []() {
    server.send(200, "text/plain", password);
  });

  server.on("/host", []() {
    server.send(200, "text/plain", host);
  });

  server.on("/", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send ( 200, "text/html", "<html>\
      <head>\
        <title>Configure</title>\
        <style>\
          body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
        </style>\
      </head>\
      <body>\
        <h1>Please enter you router config!</h1>\
        <form action='/' method='POST'>\
          SSID:<br>\
          <input type='text' name='ssid'><br>\
          PASSWORD:<br>\
          <input type='password' name='password'><br>\
          HOST:<br>\
          <input type='host' name='host'><br>\
          <input type='submit'>\
        </form>\
      </body>\
      </html>");
  });

  server.on("/", HTTP_POST, []() {
    if (server.hasArg("ssid") && server.hasArg("password")) {
      char* payload = new char[32];
      server.arg("ssid").toCharArray(payload, 32);
      writeConfig(0, payload, 32);
      server.arg("password").toCharArray(payload, 32);
      writeConfig(1, payload, 32);
      server.arg("host").toCharArray(payload, 32);
      writeConfig(2, payload, 32);
    }
    server.sendHeader("Connection", "close");
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send ( 200, "text/html", "all_saved");
  });

  server.begin();
}

void setup() {
  pinMode(PIN_LED_WIFI, OUTPUT);
  pinMode(PIN_LED_SOCKET, OUTPUT);
  digitalWrite(PIN_LED_WIFI, HIGH);
  digitalWrite(PIN_LED_SOCKET, LOW);

  WiFi.softAP(SYS_SSID, SYS_PASS);

  Serial.begin(115200);
  delay(10);

  device = new DeviceRC522(4, 5);

  EEPROM.begin(512);
  loadConfig();
  while (WiFi.status() != WL_CONNECTED) {
    connectToWiFi(ssid, password);
  }

  startServer();

  webSocket.begin(host, port, url);
  webSocket.onEvent(webSocketEvent);
}

int packageLen = 0;
int packageI = 0;
char package[256];
char c;

void readPackages() {
  if (Serial.available() > 0) {
    c = Serial.read();
    if (packageLen == 0) {
      packageLen = c;
    } else {
      package[packageI] = c;
      packageI++;
      if (packageI == packageLen) {
        webSocket.sendTXT(package, packageLen);
        packageLen = 0;
        packageI = 0;
      }
    }
  }
}

void checkInternalVirtualDevice() {
  if (device != NULL && status > 0) {
    device->tick();
    if (device->newData()) {
      webSocket.sendTXT(device->readData(), 3);
    }
  }
}

void loop() {
  webSocket.loop();
  server.handleClient();
  readPackages();

  checkInternalVirtualDevice();
}

