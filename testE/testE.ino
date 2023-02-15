//#include <Wire.h>

#define e1 5
#define m1 4 

int enc = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(m1, OUTPUT);
  pinMode(e1, OUTPUT);
 // attachInterrupt(0, leftPlus, FALLING);
}

void leftPlus() {
  enc++;
  Serial.println(enc);
  //if (digitalRead(lEnc)) left++;
  //else left++;
}

void forward() {
  int pomL = enc;
  digitalWrite(m1, LOW);
  //while (abs(enc - pomL) < 360) {
    analogWrite(e1, 50);
  //}

  totalStop();
  delay(500);
}

void totalStop() {
  //digitalWrite(lEnc, LOW);
  analogWrite(e1, 0);
}

void loop() {
  forward();
  if (enc >= 1408) {
    totalStop();
    enc = 0;
    delay(2000);
  }
}
