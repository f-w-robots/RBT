#include "Package.h"

Package::Package(WebSocketsClient *webSocket) {
  this->webSocket = webSocket;
}

void Package::readPackages() {
  if (Serial.available() > 0) {
    c = Serial.read();
    if (packageLen == 0) {
      packageLen = c - 48;
    } else {
      package[packageI] = c;
      packageI++;
      if (packageI == packageLen) {
        webSocket->sendTXT(package, packageLen);
        packageLen = 0;
        packageI = 0;
      }
    }
  }
}

