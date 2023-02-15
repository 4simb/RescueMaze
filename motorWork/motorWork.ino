#include <Wire.h>

#define lPin 6
#define rPin 8
#define lEnc 5
#define rEnc 7

void setup() {
  // put your setup code here, to run once:
  pinMode(lPin, OUTPUT);
  pinMode(rPin, OUTPUT);
  pinMode(lEnc, OUTPUT);
  pinMode(rEnc, OUTPUT);
  //attachInterrupt(0, leftPlus, RISING);
  //attachInterrupt(1, rightPlus, RISING);
  digitalWrite(lEnc, HIGH);
  digitalWrite(rEnc, HIGH);
}

/*void leftPlus() {
  if (digitalRead(lEnc)) left++;
  else left--;
}

void rightPlus() {
  if (digitalRead(rEnc)) right++;
  else right--;
}*/


void loop() {
  analogWrite(rPin, 255);
  analogWrite(lPin, 255);
}
