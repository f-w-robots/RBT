#ifndef Server_h
#define Server_h

#include <ESP8266WebServer.h>
#include <WebSocketsClient.h>
#include "Config.h"

class LHServer {
  public:
    LHServer(Config* config, WebSocketsClient webSocket, char *allowIds);
    void handleClient();
  private:
    boolean allowConenctFor(String id);
    ESP8266WebServer *server;
    char *allowIds;
    Config *config;
};

#endif

