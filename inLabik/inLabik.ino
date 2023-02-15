#include "MPU9250.h"
#include <VL53L0X.h>
#include <Wire.h>

#define lPin 6
#define rPin 8
#define lEnc 5
#define rEnc 7
#define Sensor1_newAddress 41
#define Sensor2_newAddress 42
#define XSHUT_pin2 37
#define XSHUT_pin1 38
//41
//42

VL53L0X vlxF; // Sensor1; 
VL53L0X vlxL; //Sensor2;
MPU9250 mpu;

float y0 = 0, p0 = 0;
float yaw = 0, pitch = 0, roll = 0;
volatile int left = 0;
volatile int right = 0;
float err, errOld = 0, u, p, d;
short int leftMotorValue, rightMotorValue;
int timing;

void vlx_setup() {
  pinMode(XSHUT_pin1, OUTPUT);
  pinMode(XSHUT_pin2, OUTPUT);
  delay(10);
  vlxF.setAddress(Sensor1_newAddress);
  pinMode(XSHUT_pin2, INPUT);
  delay(10);
  vlxL.setAddress(Sensor2_newAddress);
  pinMode(XSHUT_pin1, INPUT);
  delay(10);
  Serial.println("Hello! It's me");
  vlxF.init();
  vlxL.init();
  Serial.println("Init end");
  delay(2000);
  vlxF.setTimeout(20);
  vlxL.setTimeout(20);
  vlxF.startContinuous();
  vlxL.startContinuous();
  //Sensor3.startContinuous();
  Serial.println("Setup end");
}

void setup() {
  //Serial.println("YES");
  Serial3.begin(115200);
  Serial.begin(115200);
  //Serial.println("YES");
  Wire.begin();
  Serial.println("YES");
  vlx_setup();
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
  
  if (mpu.update()) {
    y0 = 180 + mpu.getYaw();
    p0 = 180 + mpu.getPitch();
  }

  timing = millis();
}

void leftPlus() {
  left++;
  //if (digitalRead(lEnc)) left++;
  //else left--;
}

void rightPlus() {
  right++;
  //if (digitalRead(rEnc)) right++;
  //else right--;
}

void totalStop() {
  analogWrite(lEnc, LOW);
  analogWrite(rEnc, LOW);
  analogWrite(lPin, 0);
  analogWrite(rPin, 0);
}

float yOld = 0, pOld;
short int k = 0, kPitch = 0;
bool first = true;
void yawFunc() {
  if (mpu.update()) {
    if (yOld > 350 && 180 + mpu.getYaw() < 10) k++;
    else if (!first && 180 + mpu.getYaw() > 350 && yOld < 10) k--;

    if (pOld > 350 && 180 + mpu.getPitch() < 10) kPitch++;
    else if (!first && 180 + mpu.getPitch() > 350 && pOld < 10) kPitch--;

    yaw = 360 * (float)k + 180 + mpu.getYaw() - y0;
    pitch = 360 * (float)kPitch + 180 + mpu.getPitch() - p0;
    
    if (yaw > 360) k--;
    else if (yaw < 0) k++;
    yaw = 360 * (float)k + 180 + mpu.getYaw() - y0;

    if (pitch > 360) kPitch--;
    else if (pitch < 0) kPitch++;
    pitch = 360 * (float)kPitch + 180 + mpu.getPitch() - p0;

    yOld = 180 + mpu.getYaw();
    pOld = 180 + mpu.getPitch();
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
  //if (zeroYaw - 90 < 0 || zeroYaw < 0) zeroYaw += 360;
  Serial.println("zeroYaw: ");
  //Serial.println(zeroYaw);
  //delay(2500);
  leftMotorValue = 115;
  rightMotorValue = -115;

  while (true) {
    yawFunc();
    Serial.print(yaw);
    Serial.print(" ");
    Serial.println(zeroYaw);

    setMotors(leftMotorValue, rightMotorValue);
    //yawFunc();
    if (differenceYaw(zeroYaw, yaw) < 91 && differenceYaw(zeroYaw, yaw) > 89) break;
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
  //if (zeroYaw + 90 >= 360) zeroYaw -= 360;
  leftMotorValue = -115;
  rightMotorValue = 115;

  while (true) {
    yawFunc();
    Serial.print(yaw);
    Serial.print(" ");
    Serial.println(zeroYaw);

    setMotors(leftMotorValue, rightMotorValue);
    if (differenceYaw(zeroYaw, yaw) < 91 && differenceYaw(zeroYaw, yaw) > 89) break;
    //Serial3.available();
  }

  totalStop();
  Serial.println("RIGHT");
  delay(1000);
}

void AccForward(short int vv, float yy) {
  yawFunc();
  err = differenceYaw(yy, yaw) * (double)signYaw(yy, yaw);
  
  p = err * 5; //22
  d = (err - errOld) * 10;
  u = p + d;
  
  if (vv > 0) {
    leftMotorValue = -(vv - u); //vv + u
    rightMotorValue = -(vv + u); // vv - u
  } else {
    leftMotorValue = -vv + u; //vv + u
    rightMotorValue = -vv - u; // vv - u
  }

  errOld = err;
  setMotors(leftMotorValue, rightMotorValue);
}

short int signYaw(double y1, double y2) {
  if (y1 - y2 == 0) return 0;
  else if (abs(y1 - y2) < 180) {
    if (y2 > y1) return -1;
    else return 1;
  } else {
    if (y2 > y1) return 1;
    else return -1;
  }
}

double differenceYaw(double y1, double y2) {
  if (abs(y1 - y2) <= 180) return abs(y1 - y2);
  else if (y2 > 180 && y1 < 180) {
    return y1 + 360 - y2;
  } else {
    return y2 + 360 - y1;
  }
}

char openMVRead = '0';
byte countH = 0, countS = 0, countU = 0;
short int centralVLX, leftVLX;
bool ignoreWords = false;
byte ignoreCount = 0;
bool ff = true;
float fy;
int l0 = 0, r0 = 0;
int angleNow = 0;

void loop() {
  //yawFunc();
  centralVLX = vlxF.readRangeContinuousMillimeters();
  leftVLX = vlxL.readRangeContinuousMillimeters();
  yawFunc();

  if (left - l0 < 500) {
    AccForward(100, angleNow);
  } else {
    setMotors(0, 0);

    while (true) delay(100);
  }

  Serial.println(left);
}
