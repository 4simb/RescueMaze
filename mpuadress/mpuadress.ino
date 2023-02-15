#include <Wire.h>
#include "MPU9250.h"

MPU9250 mpu;
MPU9250 matrix2;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  mpu.setup(0x73);
  matrix2.setup(0x71);
}

void loop() {
  
}
