#ifndef Config_h
#define Config_h

#include <ESP8266HTTPClient.h>

class Config {
  public:
    Config();
    ~Config();
    char *getSsid();
    char *getPass();
    char *getHost();
    char *getUrl();
    void loadConfig();
    void writeConfig(uint8_t i, char* data, uint8_t length);
  private:
    char **data;
};

#endif

