#include "MPU9250.h"
#include <Wire.h>
//#include <EEPROM.h>

MPU9250 mpu;
float yaw;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  //mpu.verbose(true);
  while (!mpu.setup(0x68));
  mpu.calibrateGyro(4000);

  /*mpu.setXOffset(-0.10);
  mpu.setYOffset(-0.02);
  mpu.setZOffset(-0.04);

  Serial.println(mpu.getXOffset());
  Serial.println(mpu.getYOffset());
  Serial.println(mpu.getZOffset());
  
  for (byte i = 0; i < 500; i++) {
    if (mpu.update()) yaw = mpu.getYaw();
    //delay(1);
  }

  Serial.println("YES");
  delay(1000);*/
  /*mpu.calibrateGyro(4000);
  Serial.println(mpu.getXOffset());
  Serial.println(mpu.getYOffset());
  Serial.println(mpu.getZOffset());*/
}

void loop() {
  // put your main code here, to run repeatedly:
  if (mpu.update()) {
    //Serial.print("A");
    yaw = mpu.getYaw();
    Serial.println(yaw);
  }

  //count = count;
}
