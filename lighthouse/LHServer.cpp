#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "LHServer.h"

LHServer::LHServer(Config* _config, WebSocketsClient *_webSocket) {
  this->config = _config;
  this->webSocket = _webSocket;

  server = new ESP8266WebServer(80);

  server->on("/ssid", [&]() {

    server->send(200, "text/plain", config->getSsid());
  });

  server->on("/password", [&]() {
    server->send(200, "text/plain", config->getPass());
  });

  server->on("/host", [&]() {
    if (server->hasArg("id")) {
      if (allowConenctFor(server->arg("id"))) {
        server->send(200, "text/plain", config->getHost());
      } else {
        webSocket->sendTXT("id:" + server->arg("id"));
        server->send(403, "text/plain", "");
      }
    } else {
      server->send(404, "text/plain", "");
    }
  });

  server->on("/", HTTP_GET, [&]() {
    server->sendHeader("Connection", "close");
    server->sendHeader("Access-Control-Allow-Origin", "*");

    //TODO memory
    String page = "<html><head><title>Configure</title><style>body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }</style></head>";
    page += "<body><h1>Please enter you router config!</h1><form action='/' method='POST'>SSID:<br><input type='text' name='ssid' value='";
    page += config->getSsid();
    page += "'><br>PASSWORD:<br><input type='password' name='password'><br>HOST:<br><input type='host' name='host' value='";
    page += config->getHost();
    page += "'><br><input type='submit'></form></body></html>";
    server->send( 200, "text/html", page);
  });

  server->on("/", HTTP_POST, [&]() {
    if (server->hasArg("ssid") && server->hasArg("password")) {
      char* payload = new char[32];
      server->arg("ssid").toCharArray(payload, 32);
      config->writeConfig(0, payload, strlen(payload));
      server->arg("password").toCharArray(payload, 32);
      config->writeConfig(1, payload, strlen(payload));
      server->arg("host").toCharArray(payload, 32);
      config->writeConfig(2, payload, strlen(payload));
      config->writeConfig(3, config->getUrl(), 32);
    }
    server->sendHeader("Connection", "close");
    server->sendHeader("Access-Control-Allow-Origin", "*");
    server->send( 200, "text/html", "all_saved");
  });

  server->begin();
}

boolean LHServer::allowConenctFor(String id) {
  int len = strlen(allowIds);
  int j = 0;
  for (int i = 0; i < len; i++) {
    if (allowIds[i] == id[j]) {
      if (j == 0) {
        if (i == 0 || allowIds[i - 1] == '|') {
          j++;
        }
      } else {
        j++;
      }
      if (j == id.length()) {
        if (allowIds[i + 1] == 0 || allowIds[i + 1] == '|') {
          return true;
        } else {

        }
      }
    } else {
      j = 0;
    }
  }
  return false;
}

void LHServer::handleClient() {
  server->handleClient();
}

void LHServer::updateAllowIds(char *allowIds) {

  this->allowIds = allowIds;
}

