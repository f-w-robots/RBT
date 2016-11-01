boolean start = false;
boolean read = false;
int timingsIndex = 0;

const int sigSize = 1024;

unsigned int *timings = new unsigned int[sigSize];

long currentTime;
long lastTime;
int superLen = 0;

const int MIN_DELTA = 200;
const int MAX_DELTA = 100000;
uint8_t longCount = 0;
uint8_t veryLongCount = 0;

const uint8_t PIN = 5;

void stopInterrupt() {
  detachInterrupt(PIN);
  read = true;
}

void handleInterrupt() {
  if (timingsIndex > sigSize) {
    stopInterrupt();
    return;
  }
  currentTime = micros();
  long delta = currentTime - lastTime;
  timings[timingsIndex] = delta;
  lastTime = currentTime;

  timingsIndex ++;
  if (!start) {
    if (delta > MIN_DELTA) {
      longCount++;
    } else {
      longCount = 0;
    }
    if (longCount > 10) {
      start = true;
    }
    if (!start && timingsIndex > 60) {
      // memcpy()
      for (int i = 35; i < timingsIndex; i++) {
        timings[i - 35] = timings[i];
      }
      timingsIndex = timingsIndex - 35;
    }
  }

  if (delta > MAX_DELTA) {
    veryLongCount ++;
  }

  if(veryLongCount > 1) {
    stopInterrupt();
  }

  //  if(enable || ext) {
  //    return;
  //  }
  //  if(!start) {
  //    start = true;
  //    timings[0] = 0;
  //    lastTime = micros();
  //    ii = 1;
  //    return;
  //  } else {
  //    if(ii >= sigSize) {
  //      enable = true;
  //      return;
  //    }
  //    currentTime = micros();
  //    long delta = currentTime - lastTime;
  //    if(superLen == 0 && delta > 1000000) {
  //      superLen = ii;
  //    }
  //
  //    timings[ii] = delta;
  //    lastTime = currentTime;
  //    ii++;
  //  }
}



void setup() {
  Serial.begin(115200);
  Serial.println();
  for (int i = 0; i < sigSize; i++) {
    timings[i] = 0;
  }
  pinMode(2, OUTPUT);
  //  while(!digitalRead(4)){delay(1);}
  Serial.println("Start");
  attachInterrupt(PIN, handleInterrupt, CHANGE);
}

void loop() {
  if (read) {
    read = false;
    for (int i = 0; i < timingsIndex; i++) {
      Serial.println(timings[i]);
    }
  }
}

