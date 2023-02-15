#include "MPU9250.h"
#include <Wire.h>

#define lPin 8
#define rPin 6

#define lEnc 7
#define rEnc 5

MPU9250 mpu;
float y0 = 0;
float yaw = 0, pitch = 0, roll = 0;
volatile int left = 0;
volatile int right = 0;
float err, u;
short int leftMotorValue, rightMotorValue;

void setup() {
  //Serial.println("YES");
  Serial.begin(115200);
  //Serial.println("YES");
  Wire.begin();
  Serial.println("YES");
  //mpu.verbose(true);
  while (!mpu.setup(0x68));
  Serial.println("YES");
  mpu.calibrateGyro(3100);
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
  analogWrite(lEnc, LOW);
  analogWrite(rEnc, LOW);
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

void setMotors(short int lmv, short int rmv) {
  if (lmv > 0) {
    digitalWrite(lEnc, HIGH);
    analogWrite(lPin, 255 - min(255, (short int)abs(lmv)));
  } else {
    digitalWrite(lEnc, LOW);
    analogWrite(lPin, min(255, (short int)abs(lmv)));
  }
  
  if (rmv > 0) {
    digitalWrite(rEnc, HIGH);
    analogWrite(rPin, 255 - min(255, (short int)abs(rmv)));
  } else {
    digitalWrite(rEnc, LOW);
    analogWrite(rPin, min(255, (short int)abs(rmv)));
  }
}

void LeftTurn() {
  Serial.println("LEFT");
  yawFunc();
  float zeroYaw = yaw;
  if (zeroYaw - 90 < 0) zeroYaw += 360;
  leftMotorValue = 115;
  rightMotorValue = -115;

  while (true) {
    yawFunc();
    Serial.print(yaw);
    Serial.print(" ");
    Serial.println(zeroYaw);

    setMotors(leftMotorValue, rightMotorValue);
    if (abs(zeroYaw - yaw) < 90 && abs(zeroYaw - yaw) > 89) break;
  }
  
  totalStop();
  delay(500);
  Serial.println("LEFT");
}

void RightTurn() {
  Serial.println("RIGHT");
  yawFunc();
  float zeroYaw = yaw;
  if (zeroYaw + 90 >= 360) zeroYaw -= 360;
  leftMotorValue = -115;
  rightMotorValue = 115;

  while (true) {
    yawFunc();
    Serial.print(yaw);
    Serial.print(" ");
    Serial.println(zeroYaw);

    setMotors(leftMotorValue, rightMotorValue);
    if (abs(zeroYaw - yaw) < 90 && abs(zeroYaw - yaw) > 89) break;
  }
  
  totalStop();
  delay(500);
  Serial.println("RIGHT");
}

void AccForward(short int vv) {
  yawFunc();
  Serial.print("Y0: ");
  Serial.print(y0);
  Serial.print(" Yaw: ");
  Serial.print(yaw);
  
  err = 90 - yaw;
  u = err * 22;

  leftMotorValue = (vv + u);
  rightMotorValue = (vv - u);

  Serial.print(" ");
  Serial.print(leftMotorValue);
  Serial.print(" ");
  Serial.println(rightMotorValue);

  setMotors(leftMotorValue, rightMotorValue);
}

void loop() {
  LeftTurn();
  LeftTurn();
  LeftTurn();
  LeftTurn();
  RightTurn();
  RightTurn();
  RightTurn();
  RightTurn();
  //while (true) delay(1);
}
