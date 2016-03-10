#define in1a 2
#define in2a 3
#define in3a 4
#define in4a 5
#define in1b 6
#define in2b 7
#define in3b 8
#define in4b 9

#define input1 A1
#define input2 A2
#define input3 A3
#define input4 A4

const boolean sequence[8][4] = {
  {LOW, LOW, LOW, HIGH },
  {LOW, LOW, HIGH, HIGH},
  {LOW, LOW, HIGH, LOW },
  {LOW, HIGH, HIGH, LOW},
  {LOW, HIGH, LOW, LOW },
  {HIGH, HIGH, LOW, LOW},
  {HIGH, LOW, LOW, LOW },
  {HIGH, LOW, LOW, HIGH}
};

uint8_t position = 0;

uint8_t pins[8];
uint8_t inputs[4];
boolean signals[4];

int8_t right = 0;
int8_t left = 0;

unsigned long oldTimeValue = 0;
unsigned long newTimeValue = 0;

int speed = 1000;

void setup() {
  pins[0] = in1a;
  pins[1] = in2a;
  pins[2] = in3a;
  pins[3] = in4a;
  pins[4] = in1b;
  pins[5] = in2b;
  pins[6] = in3b;
  pins[7] = in4b;

  inputs[0] = input1;
  inputs[1] = input2;
  inputs[2] = input3;
  inputs[3] = input4;

  for (int i = 0; i < 8; i++) {
    pinMode(pins[i], OUTPUT);
  }

  for (int i = 0; i < 4; i++) {
    pinMode(inputs[i], INPUT);
  }
}

void loop() {
  for(int i = 0; i < 4; i++) 
    signals[i] = digitalRead(inputs[i]);

  if(signals[0] == 1 && signals[1] == 0)
    left = 1;
  else if(signals[0] == 0 && signals[1] == 1)
    left = -1;
  else 
    left = 0;

  if(signals[2] == 1 && signals[3] == 0)
    right = 1;
  else if(signals[2] == 0 && signals[3] == 1)
    right = -1;
  else 
    right = 0;

  newTimeValue = micros() / speed;
 
  if (newTimeValue != oldTimeValue) {
    oldTimeValue = newTimeValue ;
    step();
  }
}

void step() {
  for (int pin = 0; pin < 4; pin++) {
    if (right != 0)
      digitalWrite(pins[pin], sequence[(int)(3.5 - (3.5 * right) + (right * position))][pin]);
    if (left != 0)
      digitalWrite(pins[pin + 4], sequence[(int)(3.5 - (3.5 * left) + (left * position))][pin]);
  }
  position ++;
  if (position > 7)
    position = 0;
}

