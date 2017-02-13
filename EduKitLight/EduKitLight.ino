#include <SPI.h>
#include "Motor28BYJ.h"
#include "SR04.h"

//declare sonars
SR04 *sr04a = new SR04(11, 12);
SR04 *sr04b = new SR04(A0, 13);
//declare motors
Motor28BYJ *motor1 = new Motor28BYJ(2, 3, 4, 5);
Motor28BYJ *motor2 = new Motor28BYJ(9, 8, 7, 6);

void setup() {
  Serial.begin(115200);
  Serial.println("begin");
  //delay(2000);
}


uint8_t timer = 0;
const int8_t FORWARD_THRESHOLD = 15;// sonar delay time value threshold for moving forward
const int8_t BACKWARD_THRESHOLD = 7;// sonar delay time value threshold for moving forward
const int8_t GESTURE_THRESHOLD = 40;// sonar delay time value threshold  for moving forward
int8_t move1 = 0;
int8_t move2 = 0;
int8_t _move2 = 0;
int8_t _move1 = 0;
unsigned long oldTimeValue = 0;
unsigned long currentTime = 0;
uint8_t gestureStep = 0;
uint16_t lastStepChangeTime = 0;

void setDirection(int8_t s1, int8_t s2)
{
  if (s1 > FORWARD_THRESHOLD && s2 > FORWARD_THRESHOLD)
  {
    setMode(0, 0);
  }
  else
    // move forward
    if (s1 <= FORWARD_THRESHOLD && s2 <= FORWARD_THRESHOLD)
    {
      setMode(1, 1);
    }
  //move backward
  if (s1 <= BACKWARD_THRESHOLD && s2 <= BACKWARD_THRESHOLD)
  {
    setMode(-1, -1);
  }
  //turns
  else if (s1 <= BACKWARD_THRESHOLD && s2 >= BACKWARD_THRESHOLD && s2>s1 )
  {
    setMode(-1, 1);
  }
  else if (s1 >= BACKWARD_THRESHOLD && s2 <= BACKWARD_THRESHOLD && s1>s2)
  {
    setMode(1, -1);
  }
}
void setMode(int m1, int m2) {
  //  if (move1 == m1 && move2 == m2) {
  //    return;
  //  }
  //  currentTime = millis();
  move1 = m1;
  move2 = m2;
}

void jackalGesture (int8_t s1, int8_t s2)
{
  if (millis() - lastStepChangeTime > 2000 && gestureStep != 0)
    {
      resetStep();
      return;
    }
  if (s1 <= BACKWARD_THRESHOLD && s2 <= BACKWARD_THRESHOLD && gestureStep == 0)
    {
      gestureStep = 1;
      lastStepChangeTime = millis();
    }
  if (s1 > GESTURE_THRESHOLD && s2 > GESTURE_THRESHOLD && gestureStep == 1 && millis() - lastStepChangeTime < 1000 && millis() - lastStepChangeTime > 500)
    {
      gestureStep = 2;
      lastStepChangeTime = millis();
      return;
    }
  if (s1 <= BACKWARD_THRESHOLD && s2 <= BACKWARD_THRESHOLD && gestureStep == 2 && millis() - lastStepChangeTime < 1000 && millis() - lastStepChangeTime > 500)
    {
      gestureStep = 3;
      lastStepChangeTime = millis();
      return;
    }
    if (s1 > GESTURE_THRESHOLD && s2 > GESTURE_THRESHOLD && gestureStep == 3 && millis() - lastStepChangeTime < 1000 && millis() - lastStepChangeTime > 500)
    {
      gestureStep = 4;
//declare motors
      lastStepChangeTime = millis();
      return;
    }
  if (s1 <= BACKWARD_THRESHOLD && s2 <= BACKWARD_THRESHOLD && gestureStep == 4 && millis() - lastStepChangeTime < 1000 && millis() - lastStepChangeTime > 500)
    {
      for (int i = 0; i < 1800; i++)
      {
        motor1->step(1);
        motor2->step(1);
        delay(2);
      }
      for (int i = 0; i < 1800; i++)
      {
        motor1->step(-1);
        motor2->step(-1);
        delay(2);
      }
      for (int q = 0; q < 10; q++)
      {
        int r = 1, l = -1;
        if (q % 2 == 1) 
        {
          r = -1;
          l = 1;
        }
        for (int i = 0; i < 240; i++)
        {
          motor1->step(r);
          motor2->step(l);
          delay(2);
        }
      }
        resetStep();
        return;
    }
}

void resetStep ()
{
  gestureStep = 0;
  lastStepChangeTime = 0;
}

void loop() {
  unsigned long newTimeValue = micros() / 1800;
  sr04a->tick();
  sr04b->tick();

  uint16_t s1 = sr04a->getValue();
  uint16_t s2 = sr04b->getValue();


  setDirection(s1, s2);
//  jackalGesture(s1, s2);
  if (millis() - currentTime > 100 ) {
    _move1 = move1;
    _move2 = move2;
  }
  if (newTimeValue != oldTimeValue)
  {
    oldTimeValue = newTimeValue;
    motor1->step(_move1);
    motor2->step(_move2);
  }

//    if (timer == 1)
//    {
//      Serial.print("s1 ");
//      Serial.print(s1);
//      Serial.print(" ");
//      Serial.print("s2 ");
//      Serial.println(s2);
//    }
//    timer++;
}


