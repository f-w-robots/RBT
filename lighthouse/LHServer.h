#ifndef LHServer_h
#define LHServer_h

#include <ESP8266WebServer.h>
#include <WebSocketsClient.h>
#include "Config.h"

class LHServer {
  public:
    LHServer(Config* config, WebSocketsClient *webSocket);
    void handleClient();
    void updateAllowIds(char *allowIds);
  private:
    boolean allowConenctFor(String id);
    ESP8266WebServer *server;
    char *allowIds = "";
    Config *config;
    WebSocketsClient *webSocket;
};

#endif

