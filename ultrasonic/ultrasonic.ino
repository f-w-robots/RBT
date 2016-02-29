#include "ESP8266Serial.h"
#include "RGBIndication.h"
//#include "LineSensor.h"
#include "EngineStep.h"
#include "Motor28BYJ.h"
#include <SoftwareSerial.h>

Motor28BYJ motor1(2,3,4,5);
Motor28BYJ motor2(6,7,8,9);

// TX, RX
ESP8266Serial esp;
//Red, Green, Blue
RGBIndication rgb(11, 12, 13);
// S0, S1, S2, Z
//LineSensor line(A3, A4, A5, A2);

SoftwareSerial dbgSerial(A0, A1);
//#define dbgSerial Serial

String ssid = "kernel";
String password = "axtr456E";
String host = "192.168.1.4";
String sha = "car";

String response = "";
int rightSpeed = 0;
int leftSpeed = 0;

boolean lineMode = false;
const uint8_t lineModeSpeed = 100;

int requestTimeout = 0;

// TODO - binary protocol
void parseResponse(String response) {
  boolean left = false;
  boolean right = false;
  int leftSign = 1;
  int rightSign = 1;
  leftSpeed = 0;
  rightSpeed = 0;
  for (int i = 0; i < response.length(); i++) {
    if (response[i] == 'l') {
      right = false;
      left = true;
      if (response[i + 1] == '-')
        leftSign = -1;
    }
    if (response[i] == 'r') {
      left = false;
      right = true;
      if (response[i + 1] == '-')
        rightSign = -1;
    }
    if (response[i] > 47 && response[i] < 58) {
      if (left)
        leftSpeed = leftSpeed * 10 + response[i] - 48;
      if (right)
        rightSpeed = rightSpeed * 10 + response[i] - 48;
    }
  }
  leftSpeed = leftSpeed * leftSign;
  rightSpeed = rightSpeed * rightSign;

  leftSpeed = constrain(leftSpeed, -255, 255);
  rightSpeed = constrain(rightSpeed, -255, 255);
}

void connect() {
  rgb.power();
  delay(500);
  dbgSerial.println("prepare");
  while (!esp.prepare()) {
    dbgSerial.println("try prepare");
    rgb.error();
    delay(500);
    rgb.power();
  }
  rgb.connection();
  delay(300);
  rgb.power();
  dbgSerial.println("connect to wifi");
  while (!esp.upWiFi(ssid, password)) {
    dbgSerial.println("try connect to wifi");
    rgb.error();
    delay(500);
    rgb.power();
  }
  rgb.connection();
  delay(300);
  rgb.power();
  dbgSerial.println("connect to socket");
  while (!esp.connectToSocket(host, "2500", sha)) {
    dbgSerial.println("try connect to socket");
    rgb.error();
  }
}

void setup()
{
  Serial.begin(9600); // ESP8266Serial
  dbgSerial.begin(9600);

  connect();
  rgb.connection();
  esp.request("waiting");
  
  dbgSerial.println("connected");
}

boolean moveMode = false;
int8_t right = 0;
int8_t left = 0;

unsigned long oldTimeValue = 0;
unsigned long newTimeValue = 0;

int speed = 1200;

int stepCount = 0;

void loop()
{
  if (!esp.connected()) {
    rgb.error();
    connect();
    rgb.connection();
    return;
  }
  if (esp.responseAvailable()) {
    response = esp.getResponse();
    dbgSerial.println(response);
    if (response.startsWith("FAIL:")) {
      rgb.error();
      return;
    }
    if (response.startsWith("S") && !moveMode) {
      moveMode = true;
      stepCount = 0;
      if(response.substring(1) == "f") {
        left = 1;
        right = 1;
      }
      if(response.substring(1) == "l") {
        left = 0;
        right = 1;
      }
      if(response.substring(1) == "r") {
        left = 1;
        right = 0;
      }
    }
  }
  if(moveMode) {
    newTimeValue = micros() / speed;
 
    if (newTimeValue != oldTimeValue) {
      oldTimeValue = newTimeValue ;
      motor1.step(right);
      motor2.step(left);
      stepCount++;
      if(stepCount > 3000) {
        moveMode = false;
        esp.request("wait");
      }
    }
    
  }
//  requestTimeout += 1;
//  if (requestTimeout > 1000) {
//    line.readSensors();
//    String req = line.printSensorsBool();
//    dbgSerial.println(req);
//    esp.request(req);
//    requestTimeout = 0;
//  }
}
