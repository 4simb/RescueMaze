#include "MPU9250.h"
#include <Wire.h>

#define lPin 6
#define rPin 8
#define lEnc 5
#define rEnc 7

float y0 = 0;
float yaw = 0, pitch = 0, roll = 0;
volatile int left = 0;
volatile int right = 0;
float err, u;
short int leftMotorValue, rightMotorValue;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();

  pinMode(lPin, OUTPUT);
   pinMode(lEnc, OUTPUT);
  pinMode(rPin, OUTPUT);
  pinMode(rEnc, OUTPUT);

  attachInterrupt(0, leftPlus, RISING);
  attachInterrupt(1, rightPlus, RISING);
}

void leftPlus() {
  if (digitalRead(lEnc)) left++;
  else left--;
}

void rightPlus() {
  if (digitalRead(rEnc)) right++;
  else right--;
}

void setMotors(short int lmv, short int rmv) {
  if (lmv > 0) {
    digitalWrite(lPin, HIGH);
    analogWrite(lEnc, 255 - min(255, (short int)abs(lmv)));
  } else {
    digitalWrite(lPin, LOW);
    analogWrite(lEnc, min(255, (short int)abs(lmv)));
  }

  if (rmv > 0) {
    digitalWrite(rPin, HIGH);
    analogWrite(rEnc, 255 - min(255, (short int)abs(rmv)));
  } else {
    digitalWrite(rPin, LOW);
    analogWrite(rEnc, min(255, (short int)abs(rmv)));
  }
}

void loop() {
  while (abs(left) < 1000) {
    Serial.println(left);
    setMotors(110, 0);
  }

  setMotors(0, 0);
  while (true) delay(1);
}
