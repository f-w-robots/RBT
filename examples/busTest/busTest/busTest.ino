#define ID '2'

char id = '0';

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    char c = Serial.read();
    digitalWrite(13, HIGH);
    delay(250);
    digitalWrite(13, LOW);
    if (id == '0') {
      id = c;
      return;
    }
    if (id != ID) {
      id = '0';
      return;
    }
    id = '0';
    if (c == '0') {
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
    }
    if (c == '3') {
      digitalWrite(3, HIGH);
      Serial.println("Set 3 x");
    }
    if (c == '4') {
      digitalWrite(4, HIGH);
      Serial.println("Set 4 x");
    }
    if (c == '5') {
      digitalWrite(5, HIGH);
      Serial.println("Set 5 x");
    }
  }
  // put your main code here, to run repeatedly:

}
