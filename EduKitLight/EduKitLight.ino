#include <SPI.h>
#include "Motor28BYJ.h"
#include "SR04.h"

Motor28BYJ *motor1 = new Motor28BYJ(2,3,4,5);
Motor28BYJ *motor2 = new Motor28BYJ(6,7,8,9);
SR04 *sr04a = new SR04(12,11);
SR04 *sr04b = new SR04(13,10);

void setup() {
  Serial.begin(115200);
  Serial.println("begin");
}

unsigned long oldTimeValue = 0;

void loop() {
  unsigned long newTimeValue = micros() / 2000;

  sr04a->tick();
  sr04b->tick();

  uint16_t a = sr04a->getValue();
  uint16_t b = sr04b->getValue();
  
  Serial.print(a);
  Serial.print(" ");
  Serial.println(b);

  if (newTimeValue != oldTimeValue) {
    oldTimeValue = newTimeValue;
    motor2->step(1);
    motor1->step(1);
  }
//  motor1->step(1);
//  motor2->step(1);
//  delay(2);
}

