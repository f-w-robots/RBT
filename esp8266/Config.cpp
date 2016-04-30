#include <Arduino.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include "Config.h"

Config::Config() {
  EEPROM.begin(512);
  data = new char*[4];
}

Config::~Config() {
  EEPROM.end();
}

void Config::loadConfig() {
  for (int x = 0; x < 4; x++) {
    data[x] = new char[32];
    for (int i = 32 * x; i < 32 * (x + 1); i++) {
      data[x][i - 32 * x] = EEPROM.read(i);
    }
  }
}

char *Config::getSsid() {
  return data[0];
}

char *Config::getPass() {
  return data[1];
}

char *Config::getHost() {
  return data[2];
}

char *Config::getUrl() {
  return data[3];
}

void Config::writeConfig(uint8_t i, char* line, uint8_t length) {
  Serial.println("write");
  int j = 0;
  for (; j < 32 && j < length; j++) {
    EEPROM.write(i * 32 + j, line[j]);;
    data[i][j] = line[j];
  }
  EEPROM.write(i * 32 + length - 1, 0);
  data[i][length - 1] = 0;
}

boolean Config::fetchConfig() {
  String requestUrl = "http://192.168.4.1/host?id=";
  requestUrl += this->getUrl();

  char *payload = this->getHost();
  http.begin(requestUrl);
  if (http.GET() == 200) {
    http.getString().toCharArray(payload, 32);
    writeConfig(2, payload, strlen(payload));
  } else {
    return false;
  }

  payload = this->getSsid();
  http.begin("http://192.168.4.1/ssid");
  http.GET();
  http.getString().toCharArray(payload, 32);
  writeConfig(0, payload, strlen(payload));

  payload = this->getPass();
  http.begin("http://192.168.4.1/password");
  http.GET();
  http.getString().toCharArray(payload, 32);
  writeConfig(1, payload, strlen(payload));

  EEPROM.commit();
  return true;
}

