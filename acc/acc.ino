//#include "MPURegisterMap.h"
#include "MPU9250.h"
//#include "QuaternionFilter.h"
MPU9250 mpu;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  //mlxleft.begin(0x5B);

  if (!mpu.setup(0x68)) {  // change to your own address
        while (true) {
            Serial.println("MPU connection failed. Please check your connection with `connection_check` example.");
            delay(5000);
        }
    }
}

float y;
void loop() {
  if (mpu.update()) {
  mpu.quat_filter;
  y = atan2(2.0f * (mpu.q[1] * mpu.q[2] + mpu.q[0] * mpu.q[3]), mpu.q[0] * mpu.q[0] + mpu.q[1] * mpu.q[1] + (mpu.q[2] * mpu.q[2]) + (mpu.q[3] * mpu.q[3]));
  //y *= 180.0f / PI;
  //y += 1.34;
  //y += 180;

  Serial.println(y);
  }
  delay(50);
  // put your main code here, to run repeatedly:

}
