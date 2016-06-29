#include <EEPROM.h>

char *ssid;
char *password;
char *host;
char *url;

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

void writeConfig(uint8_t i, char* data) {
  for (int j = 0; j < 32; j++) {
    EEPROM.write(i * 32 + j, data[j]);
  }
  Serial.print("write ");
  Serial.print(i + 1);
  Serial.println(" done");
}

void setup() {
  Serial.begin(115200);
  Serial.println("begin setup");
  EEPROM.begin(512);
  // ssid, password, host, url
  char data[4][32] = {"cyberhub", "cyberpass497", "192.168.100.4", "esp8266"};
  Serial.println("begin cicle");
  for (int i = 0; i < 4; i ++) {
    writeConfig(i, data[i]);
  }
  EEPROM.commit();
  Serial.println("write all done");

  loadConfig();
  Serial.println("load done");
  Serial.println(ssid);
  Serial.println(password);
  Serial.println(host);
  Serial.println(url);
  Serial.println("print done");
}

void loop() {

}
