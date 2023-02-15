#include "MPU9250.h"
#include <Wire.h>

#define lPin 6
#define rPin 8
#define lEnc 5
#define rEnc 7

MPU9250 mpu;
float y0 = 0;
float yaw = 0, pitch = 0, roll = 0;
volatile int left = 0;
volatile int right = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  //mpu.verbose(true);
  while (!mpu.setup(0x68));
  mpu.calibrateGyro(3000);
  Serial.println("YES");
  pinMode(lPin, OUTPUT);
  pinMode(rPin, OUTPUT);
  pinMode(lEnc, OUTPUT);
  pinMode(rEnc, OUTPUT);
  attachInterrupt(0, leftPlus, RISING);
  attachInterrupt(1, rightPlus, RISING);
  //if (mpu.update()) y0 = 180 + mpu.getYaw();
}

void leftPlus() {
  if (digitalRead(lEnc)) left++;
  else left--;
}

void rightPlus() {
  if (digitalRead(rEnc)) right++;
  else right--;
}

void totalStop() {
  analogWrite(lPin, 0);
  analogWrite(rPin, 0);
}

/*float yOld = 0;
  float yawFunc() {
  if (mpu.update()) {
    float y = mpu.getYaw() - y0;
    if (abs(y - yOld) > 100) return 0;
    return y - yOld;

    yOld = y;
  } else return 0;
  }*/

int err, vv = 0;
int leftMotorValue, rightMotorValue;
float u;
void AccForward() {
  if (mpu.update()) {
    yaw = mpu.getYaw();
    Serial.print("Y0: ");
    Serial.print(y0);
    Serial.print(" Yaw: ");
    Serial.print(yaw);
    err = 180 - yaw;
    u = (float)err * 0.15;

    leftMotorValue = vv + u;
    rightMotorValue = vv - u;

    Serial.print(" ");
    Serial.print(leftMotorValue);
    Serial.print(" ");
    Serial.println(rightMotorValue);

    if (leftMotorValue > 0) digitalWrite(lEnc, HIGH);
    else digitalWrite(lEnc, LOW);

    if (rightMotorValue > 0) digitalWrite(rEnc, HIGH);
    else digitalWrite(rEnc, LOW);

    analogWrite(lPin, abs(leftMotorValue));
    analogWrite(rPin, abs(rightMotorValue));
  }
}

void loop() {
  AccForward();
}
