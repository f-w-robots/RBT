#ifndef Package_h
#define Package_h

#include <ESP8266WebServer.h>
#include <WebSocketsClient.h>

class Package {
  public:
    Package(WebSocketsClient *webSocket);
    void readPackages();
  private:
    int packageLen = 0;
    int packageI = 0;
    char package[256];
    char c;
    WebSocketsClient *webSocket;

};

#endif

