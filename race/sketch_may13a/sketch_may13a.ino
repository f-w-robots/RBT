#include <Servo.h>
#include "SR04.h"

Servo myservo;

SR04 sr04(11, 10);


#define MIN_SPEED 50
#define MAX_SPEED 85
#define CENTR_ALGNLE 97

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(2, LOW);
  digitalWrite(4, HIGH);
  analogWrite(3, 0);

  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  
  myservo.attach(5);
  myservo.write(97);
  delay(3000);
//  myservo.write(135);

setSpeed(30);
Serial.begin(115200);
}

void setSpeed(int speed) {
  if(speed > MAX_SPEED)
    return;
  speed = MIN_SPEED + speed;
  analogWrite(3, speed);
}

void setDirection(int direction) {
  if(direction) {
    digitalWrite(2, LOW);
    digitalWrite(4, HIGH);
  } else {
    digitalWrite(2, HIGH);
    digitalWrite(4, LOW);
  }
}

int direction = true;
int x = -1;

int time = 0;

void loop() {
  
//  
//  for(int i =0; i < 35; i++) {
//    setSpeed(i);
//    delay(100);
//    myservo.write(CENTR_ALGNLE  + i * x);
//  }
//  for(int i = 35; i > 0; i--) {
//    setSpeed(i);
//    delay(100);
//    myservo.write(CENTR_ALGNLE + i * x);
//  }
//
//  x = x * (-1);
//  if(time + 2000 < micros()) {
//    myservo.write(CENTR_ALGNLE + 30);
//  }
//  
//    myservo.write(CENTR_ALGNLE + 30);
//    delay(3800);
//    myservo.write(CENTR_ALGNLE - 30);
//    delay(3800);
sr04.read();

if(sr04.getValue() < 100) {
  setDirection(false);
} else {
  setDirection(true);
}
  
    
//  direction = !direction;
//  setDirection(direction);

}
