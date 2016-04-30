#include <Arduino.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include "Package.h"

Package::Package(WebSocketsClient webSocket) {
  this->webSocket = webSocket;
}

void Package::readPackages() {
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

