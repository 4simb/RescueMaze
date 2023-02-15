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
float mpuGetYawOld;

void setup() {
  Serial.println("YES");
  Serial.begin(115200);
  Serial.println("YES");
  Wire.begin();
  Serial.println("YES");
  //mpu.verbose(true);
  while (!mpu.setup(0x68));
  Serial.println("YES");
  mpu.calibrateGyro(3000);
  Serial.println("YES");
  pinMode(lPin, OUTPUT);
  pinMode(rPin, OUTPUT);
  pinMode(lEnc, INPUT);
  pinMode(rEnc, INPUT);
  attachInterrupt(0, leftPlus, RISING);
  attachInterrupt(1, rightPlus, RISING);
  if (mpu.update()) y0 = 180 + mpu.getYaw();
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

float yOld = 0;
short int k = 0;
bool first = true;
void yawFunc() {
  if (mpu.update()) {
    if (yOld > 350 && 180 + mpu.getYaw() < 10) k++;
    else if (!first && 180 + mpu.getYaw() > 350 && yOld < 10) k--;

    yaw = 360 * (float)k + 180 + mpu.getYaw() - y0;
    if (yaw > 360) k--;
    else if (yaw < 0) k++;
    
    yOld = 180 + mpu.getYaw();
    first = false;
  }
}

float err, vv = 0;
short int leftMotorValue, rightMotorValue;
float u;
void AccForward() {
  yawFunc();
  Serial.print("Y0: ");
  Serial.print(y0);
  Serial.print(" Yaw: ");
  Serial.print(yaw);
  
  if (yaw < 180) err = 0 - yaw;
  else err = 360 - yaw;
  
  u = err * 0.25;

  leftMotorValue = (vv + u);
  rightMotorValue = (vv - u);

  Serial.print(" ");
  Serial.print(leftMotorValue);
  Serial.print(" ");
  Serial.println(rightMotorValue);

  if (leftMotorValue > 0) digitalWrite(lEnc, HIGH);
  else digitalWrite(lEnc, LOW);
  //digitalWrite(lEnc, LOW);
  
  if (rightMotorValue > 0) digitalWrite(rEnc, HIGH);
  else digitalWrite(rEnc, LOW);
  //digitalWrite(rEnc, LOW);
  
  analogWrite(lPin, (short int)leftMotorValue);
  analogWrite(rPin, (short int)rightMotorValue);
}

void loop() {
  AccForward();
  delay(1);
}
