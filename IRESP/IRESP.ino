#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <WebSocketsClient.h>

#include <Hash.h>

#include <IRremoteESP8266.h>

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;

int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

IRsend irsend(0);

void sendSignal(uint8_t* signal, size_t length) {
  Serial.println("--------------------");
  Serial.println("start send");
  long  int code = 0;
  int type = 0;
  
  type = signal[length - 1];
  Serial.print("type: ");
  Serial.println(signal[length - 1]);

  for(int i=length - 2; i >= 0; i--) {
    code = code | signal[i] << (8 * i);
  }
  Serial.print("code: ");
  Serial.println(code, HEX);
  
  switch (type) {
    default:
    case NEC:
      irsend.sendNEC(code, 36);
      break;
    case RC5:
      irsend.sendRC5(code, 12);
      break;
  }
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t lenght) {
    switch(type) {
      case WStype_DISCONNECTED:
        Serial.println("disconencted");
        break;
      case WStype_CONNECTED:
        Serial.println("connected");
        break;
      case WStype_TEXT:
        Serial.printf("[WSc] get text: %s\n", payload);
        sendSignal(payload, lenght);
        break;
      case WStype_BIN:
        Serial.printf("[WSc] get binary lenght: %u\n", lenght);
        sendSignal(payload, lenght);
        break;
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(4, INPUT);
    irsend.begin();
    WiFi.begin("robohub", "robohub1");
    Serial.println(); 
    Serial.print("connecting");
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(200);
    }
    Serial.println();

    webSocket.begin("192.168.33.3", 3000, "/esp8266");
    webSocket.onEvent(webSocketEvent);

    irrecv.enableIRIn();
}



void loop() {
    webSocket.loop();
    
    if (irrecv.decode(&results)) {
      if(digitalRead(4) && results.value != 0xFFFFFFFF) {
        Serial.println("--------------------");
        Serial.print(results.decode_type);
        Serial.print(": ");
        Serial.println(results.value, HEX);        
        size_t size = results.bits/8;
        if(results.bits % 8 > 0) {
          size++;
        }
        uint8_t *package = new uint8_t[size + 1];
        for(int i = 0; i < size; i ++) {
          package[i] = results.value >> 8*i;          
        }
        package[size] = results.decode_type;
        
        webSocket.sendBIN(package, size + 1);
//        sendSignal(package, size + 1);
      }
      irrecv.resume();
    }
}

