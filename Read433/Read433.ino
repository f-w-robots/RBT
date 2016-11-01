boolean enable = false;
boolean start = false;
boolean ext = false;

int ii = 0;

const int sigSize = 1024*4;

int *timings = new int[sigSize];

long currentTime;
long lastTime;
int superLen = 0;

//const int MIN_DELTA = 200;

void handleInterrupt() {
  if(enable || ext) {
    return;
  }
  if(!start) {
    start = true;
    timings[0] = 0;
    lastTime = micros();
    ii = 1;
    return;
  } else {
    if(ii >= sigSize) {
      enable = true;
      return;
    }
    currentTime = micros();
    long delta = currentTime - lastTime;
    if(superLen == 0 && delta > 1000000) {
      superLen = ii;
    }
    
    timings[ii] = delta;
    lastTime = currentTime;
    ii++;    
  }
}

const int PIN = 5;

void setup() {
  Serial.begin(115200);
  Serial.println();
  for(int i=0; i<sigSize; i++) {
    timings[i] = 0;
  }
  pinMode(2,OUTPUT);
//  while(!digitalRead(4)){delay(1);}
  Serial.println("Start");
  attachInterrupt(PIN, handleInterrupt, CHANGE);
}

void loop() {
  if(enable) {
    enable = false;
    ext = true;
    for(int i=0; i< sigSize- 1;i++) {
      Serial.println(timings[i]);
    }
  }
}

