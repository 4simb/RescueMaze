#include "MPU9250.h"
#include <Wire.h>

MPU9250 mpu;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  //mpu.verbose(true);
  while (!mpu.setup(0x68));
  mpu.calibrateGyro(4000);

  mpu.update();
}

bool count = false;
float yaw;
void loop() {
  // put your main code here, to run repeatedly:
  if (mpu.update()) {
    //Serial.print("A");
    yaw = mpu.getYaw();
    Serial.println(yaw);
  }

  //count = count;
}
