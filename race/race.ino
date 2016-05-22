#include <Servo.h>
#include "SR04.h"

int8_t sign(int num) {
  if (num == 0)
    return 0;
  if (num > 0)
    return 1;
  else
    return -1;
}


Servo myservo;

//передние
SR04 sr04_r(7, 6);
SR04 sr04_l(12, 13);

//бококвые
SR04 sr04_l_n(8, 9);
SR04 sr04_r_n(10, 11);

SR04 sr04_c(A0, A1);

//передние
int stop_right;
int stop_left;
int stop_center;

//боковые
int stop_right_n;
int stop_left_n;

const int STOP_VALUE_1 = 110;
const int STOP_VALUE_2 = 35;
const int STOP_VALUE_N = 35;
const int STOP_VALUE_C = 100;

int i = 0;
int valueArray[5] = {0, 0, 0, 0, 0};
int valueArray_2[5] = {0, 0, 0, 0, 0};
int result = 0;

#define MIN_SPEED 60
#define MAX_SPEED 125
#define CENTR_ALGNLE 97

#define MIN_ANGLE 15/*20*/
#define MAX_ANGLE 35

#define SPEED_ONE -15
#define SPEED_TWO -10
#define SPEED_THREE 50


void setup() {
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  setDirection(true);
  analogWrite(3, 0);

  myservo.attach(5);
  myservo.write(CENTR_ALGNLE);

  //  setSpeed(30);
  Serial.begin(115200);
}

void setSpeed(int speed) {
  if (speed == -1)
    speed = 0;
  else
    speed = MIN_SPEED + speed;
  if (speed > MAX_SPEED)
    speed = MAX_SPEED;

  analogWrite(3, speed);
}

void setDirection(int direction) {
  if (direction) {
    digitalWrite(2, LOW);
    digitalWrite(4, HIGH);
  } else {
    digitalWrite(2, HIGH);
    digitalWrite(4, LOW);
  }
}

//сначала мелкие
void Result() {
  //едем возле стенки
  if (valueArray[0] == 0) {
    result = 104;
    return;
  }
  if (valueArray[4] == 0) {
    result = -104;
    return;
  }

  // перед нами узкое препятсвие
  if ( valueArray[2] == 0) {
    result = 12;
    return;
  }

  // в западне
  if (valueArray[1] == 0 && valueArray[3] == 0 || valueArray[2] < 2) {
    result = 18;
    return;
  }

  // дорога свободна
  if (valueArray[1] == 2 && valueArray[3] == 2 && valueArray[0] == 1 && valueArray[4] == 1) {
    result = 0;
    return;
  }

  //приближаемся к пепятсвие, и по бокам занято
  /*18*/  if (valueArray[1] == 1 && valueArray[3] == 1 && valueArray[0] == 0 && valueArray[4] == 0) {
    result = 18;
    return;
  }

  // препятсвие середине, угловым далеко
  /*12*/   if (valueArray[2] == 1 && valueArray[1] < 2 && valueArray[3] < 2 ) {
    result = 12;
    return;
  }

  // по бокам занято, правый передний показывает препятсвие
  /*2'*/  if (valueArray[3] == 1 && valueArray[0] == 0 && valueArray[4] == 0) {
    result = 5;
    return;
  }

  // по бокам занято, левый передний показывает препятсвие
  /*4'*/  if (valueArray[1] == 1 && valueArray[0] == 0 && valueArray[4] == 0) {
    result = 6;
    return;
  }

  // слева занято спереди ещё есть свободного немного пространства
  /*4'*/  if (valueArray[1] == 1 && valueArray[3] == 1 && valueArray[0] == 0) {
    result = 6;
    return;
  }

  // спереди занято, справа свободно
  /*2'*/  if (valueArray[1] == 1 && valueArray[3] == 1 && valueArray[4] == 0) {
    result = 5;
    return;
  }

  // спереди близко и слева тоже близко
  /*10*/   if (valueArray[2] == 1 && (valueArray[1] == 1 || valueArray[1] == 0)) {
    result = 10;
    return;
  }
  // спереди близко и справа тоже близко
  /*11*/   if (valueArray[2] == 1 && (valueArray[3] == 1 || valueArray[3] == 0) ) {
    result = 11;
    return;
  }

  // побокам близко - НЕРАБОТАЕТ
  /*8*/   if (valueArray[0] == 0 && valueArray[4] == 0) {
    result = 8;
    return;
  }

  
  /*0*/   if (valueArray[3] == 1 && valueArray[0] == 0) {
    result = 0;
    return;
  }
  /*2*/   if (valueArray[3] == 1 && valueArray[4] == 0) {
    result = 2;
    return;
  }
  /*4*/   if (valueArray[1] == 1 && valueArray[0] == 0) {
    result = 4;
    return;
  }
  /*0*/   if (valueArray[1] == 1 && valueArray[4] == 0) {
    result = 0;
    return;
  }
  /*7*/   if (valueArray[1] == 1 && valueArray[3] == 1) {
    result = 7;
    return;
  }
  /*4'*/  if (valueArray[1] == 0 ) {
    result = 6;
    return;
  }
  /*2'*/  if (valueArray[3] == 0) {
    result = 5;
    return;
  }

  /*3*/   if (valueArray[1] == 1) {
    result = 3;
    return;
  }
  /*1*/   if (valueArray[3] == 1) {
    result = 1;
    return;
  }
  return;
}

void choice() {
  if (result == 0) {
    setDirection(true);
    myservo.write(CENTR_ALGNLE);
    setSpeed(SPEED_THREE);
    return;
  }
  if (result == 1) {
    setDirection(true);
    myservo.write(CENTR_ALGNLE - MIN_ANGLE);
    setSpeed(SPEED_TWO);
    return;
  }
  if (result == 3) {
    setDirection(true);
    myservo.write(CENTR_ALGNLE + MIN_ANGLE);
    setSpeed(SPEED_TWO);
    return;
  }
  if (result == 104 || result == -104) {
    setDirection(true);
    myservo.write(CENTR_ALGNLE + MAX_ANGLE * sign(result));
    setSpeed(SPEED_ONE);
    return;
  }
  if (result == 5 || result == 11) {
    setDirection(true);
    myservo.write(CENTR_ALGNLE - MAX_ANGLE);
    setSpeed(10);
    return;
  }
  if (result == 6 || result == 10) {
    setDirection(true);
    myservo.write(CENTR_ALGNLE + MAX_ANGLE);
    setSpeed(10);
    return;
  }
  if (result == 7 || result == 12) {
    setDirection(true);
    if (stop_right >= stop_left) {
      myservo.write(CENTR_ALGNLE + MAX_ANGLE);
      setSpeed(SPEED_ONE);
      return;
    } else {
      myservo.write(CENTR_ALGNLE - MAX_ANGLE);
      setSpeed(SPEED_ONE);
      return;
    }
    return;
  }
  if (result == 8 ) {
    setDirection(true);
    if (stop_right_n >= stop_left_n) {
      myservo.write(CENTR_ALGNLE + MAX_ANGLE);
      setSpeed(SPEED_ONE);
      return;
    } else {
      myservo.write(CENTR_ALGNLE - MAX_ANGLE);
      setSpeed(SPEED_ONE);
      return;
    }
    return;
  }
  if (result == 18) {

    setDirection(false);
    setSpeed(MAX_SPEED);
    myservo.write(CENTR_ALGNLE);
    delay(1300);
    setDirection(true);
    setSpeed(MAX_SPEED);
    delay(800);
    return;
  }
  return;
}

void loop() {
  for (int i = 0; i < 5; i++) valueArray[i] = 2;

  //передние исправление фантастической 4

  stop_right = sr04_r.readNow();
  if (stop_right == 30)stop_right = 300;
  stop_left = sr04_l.readNow();
  if (stop_left == 5 || stop_left == 4)stop_left = 300;
  //---------end

  //боковые исправление фантастической 4
  stop_right_n = sr04_r_n.readNow();
  //if(stop_right_n<=6)stop_right_n=300;
  stop_left_n = sr04_l_n.readNow();
  if (stop_left_n == 5 || stop_left_n == 6)stop_left_n = 300;
  //---------end

  stop_center = sr04_c.readNow();

  //задание массива
  if (stop_left_n <= STOP_VALUE_N)
    valueArray[0] = 0;
  else
    valueArray[0] = 1;

  if (stop_left <= STOP_VALUE_1)
    valueArray[1] = 1;
  if (stop_left <= STOP_VALUE_2)
    valueArray[1] = 0;

  if (stop_center <= STOP_VALUE_C)
    valueArray[2] = 1;
  if (stop_center <= STOP_VALUE_C / 4)
    valueArray[2] = 0;

  if (stop_right <= STOP_VALUE_1)
    valueArray[3] = 1;
  if (stop_right <= STOP_VALUE_2)
    valueArray[3] = 0;

  if (stop_right_n <= STOP_VALUE_N)
    valueArray[4] = 0;
  else
    valueArray[4] = 1;
  //------end

  //результат
  Result();
  //-----end

  if (i == 5000) {
    Serial.print("right: ");
    Serial.print(stop_right);
    Serial.print(" left: ");
    Serial.println(stop_left);
    Serial.print("right_n: ");
    Serial.print(stop_right_n);
    Serial.print(" left_n: ");
    Serial.println(stop_left_n);
    Serial.print("result: ");
    Serial.print(result);
    Serial.print("   ");
    Serial.print(valueArray[0] /*result*/);
    Serial.print(valueArray[1]);
    Serial.print(valueArray[2]);
    Serial.print(valueArray[3]);
    Serial.println(valueArray[4]);

    if (valueArray_2[0] == valueArray[0] && valueArray_2[1] == valueArray[1] && valueArray_2[2] == valueArray[2] && valueArray_2[3] == valueArray[3] && valueArray_2[4] == valueArray[4]) {
      setDirection(true);
      setSpeed(MAX_SPEED);
      delay(500);
    }
    for (int i = 0; i < 5; i++)valueArray_2[i] = valueArray[i];
    i = 0;
  }
  i++;

  choice();

  result = 0;
}

