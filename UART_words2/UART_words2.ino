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
  Serial3.begin(115200);
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
    yaw = 360 * (float)k + 180 + mpu.getYaw() - y0;

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
  if (zeroYaw - 90 < 0 || zeroYaw < 0) zeroYaw += 360;
  Serial.println("zeroYaw: ");
  Serial.println(zeroYaw);
  delay(2500);
  leftMotorValue = 115;
  rightMotorValue = -115;

  while (true) {
    yawFunc();
    Serial.print(yaw);
    Serial.print(" ");
    Serial.println(zeroYaw);

    setMotors(leftMotorValue, rightMotorValue);
    yawFunc();
    if (abs(zeroYaw - yaw) < 91 && abs(zeroYaw - yaw) > 89) break;
    //Serial3.available();
  }

  totalStop();
  Serial.println("LEFT");
  delay(1000);
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
    //Serial3.available();
  }

  totalStop();
  Serial.println("RIGHT");
  delay(1000);
}

void AccForward(short int vv) {
  yawFunc();
  Serial.print("Y0: ");
  Serial.print(y0);
  Serial.print(" Yaw: ");
  Serial.print(yaw);

  err = 90 - yaw;
  u = err * 0.5; //22

  leftMotorValue = (vv + u);
  rightMotorValue = (vv - u);

  Serial.print(" ");
  Serial.print(leftMotorValue);
  Serial.print(" ");
  Serial.println(rightMotorValue);

  setMotors(leftMotorValue, rightMotorValue);
}

byte differenceYaw(double y1, double y2) {
  if (abs(y1 - y2) <= 180) return abs(y1 - y2);
  else if (y2 > 180 && y1 < 180) {
    return y1 + 360 - y2;
  } else {
    return y2 + 360 - y1;
  }
}

char openMVRead = '0';
byte countH = 0;
bool ignoreWords = false;
byte ignoreCount = 0;

void loop() {
  //AccForward(115);
  /*yawFunc();
  if (Serial3.available()) {
    openMVRead = Serial3.read();
    yawFunc();
    Serial3.write(openMVRead);
    yawFunc();

    if (ignoreWords) ignoreCount++;
    if (ignoreCount > 100) {
      ignoreWords = false;
      ignoreCount = 0;
    }
    
    if (!ignoreWords && openMVRead == 'H') {
      countH++;
    } else countH = 0;

    if (countH > 5) {
      LeftTurn();
      RightTurn();
      countH = 0;
      ignoreWords = true;
    }

    Serial.println(openMVRead);
    openMVRead = 0;
  }*/
  //yawFunc();
  //Serial.println(yaw);
  //LeftTurn();
  //RightTurn();
  yawFunc();
  float zeroYaw = yaw;
  while (true) {
    yawFunc();
    setMotors(115, -115);
    Serial.print(yaw);
    Serial.print(" ");
    Serial.print(zeroYaw);
    Serial.print(" ");
    Serial.println(differenceYaw(zeroYaw, yaw));

    if (differenceYaw(zeroYaw, yaw) >= 88 && differenceYaw(zeroYaw, yaw) <= 92) break;
  }

  Serial.println("THE END");
  for (byte i = 0; i < 100; ++i) {
    setMotors(0, 0);
    yawFunc();
  }
}
