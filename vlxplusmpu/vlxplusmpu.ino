#include "MPU9250.h"
#include <Wire.h>
#include <EEPROM.h>
#include <VL53L0X.h>

#define Sensor1_newAddress 41
#define Sensor2_newAddress 42
#define XSHUT_pin2 37
#define XSHUT_pin1 38

VL53L0X vlxF; // Sensor1; 
VL53L0X vlxL; //Sensor2;
MPU9250 mpu;
float yaw;
int central, left;

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
  delay(200);
  vlxF.setTimeout(20);
  vlxL.setTimeout(20);
  vlxF.startContinuous();
  vlxL.startContinuous();
  //Sensor3.startContinuous();
  Serial.println("Setup end");
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  vlx_setup();
  while (!mpu.setup(0x68));
  mpu.calibrateGyro(4000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (mpu.update()) {
    //Serial.print("A");
    Serial.print(" YAW: ");
    yaw = mpu.getYaw();
    Serial.print(yaw);
  }

  left = vlxL.readRangeContinuousMillimeters();
  central = vlxF.readRangeContinuousMillimeters();
  Serial.print(" Central: ");
  Serial.print(central);
  Serial.print(" Left: ");
  Serial.println(left);
  delay(50);
  //count = count;
}
