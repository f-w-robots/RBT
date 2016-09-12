/*
 * IRremoteESP8266: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to ESP8266 pin 0.
 * Version 0.1 June, 2015
 * Based on Ken Shirriff's IrsendDemo Version 0.1 July, 2009, Copyright 2009 Ken Shirriff, http://arcfn.com
 */
//FF50AF - 20 up
//FF6897 - 20 down
//FF48B7 - 35 OK+
//FF906F  - 30 menu
//FFD02F -  D return

#include <IRremoteESP8266.h>

IRsend irsend(0);
IRrecv irrecv(2);

decode_results results;

void setup()
{
  irsend.begin();
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
//  irsend.sendNEC(0xFF50AF, 36);
  if (irrecv.decode(&results)) {
    if(results.value == 0x20) {
      Serial.println(0xFF50AF, HEX);
      irsend.sendNEC(0xFF50AF, 36);
    } if(results.value == 0x21) {
      Serial.println(0xFF6897, HEX);
      irsend.sendNEC(0xFF6897, 36);
    } if(results.value == 0x35) {
      Serial.println(0xFF48B7, HEX);
      irsend.sendNEC(0xFF48B7, 36);
    } if(results.value == 0xD) {
      Serial.println(0xFFD02F, HEX);
      irsend.sendNEC(0xFFD02F, 36);
    } if(results.value == 0x30) {
      Serial.println(0xFF906F, HEX);
      irsend.sendNEC(0xFF906F, 36);
    } else {
      Serial.println(results.value, HEX);
    }    
    irrecv.resume();
  }
  delay(100);

//  Serial.println("NEC");
//  irsend.sendNEC(0xFF50AF, 36);
//  delay(1000);
//  for(int i=0;i< 12;i++) {
//    Serial.println(4+i);
////    irsend.sendSony(9, 4+i);
//    delay(500);
//  }
//  irsend.sendSony(0x809, 12);
//  delay(1000);
//  irsend.sendSony(0x9, 12);
//  delay(100);
//  irsend.sendSony(0x809, 12);
//  delay(1000);
//  irsend.sendSony(0x9, 12);
//  delay(100);
//  irsend.sendSony(0x809, 12);
//  delay(1000);
}
