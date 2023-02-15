#include <Wire.h>
#include "MPU9250.h"
#include <Adafruit_MLX90614.h>

//Adafruit_MLX90614 mlxleft = Adafruit_MLX90614();
MPU9250 mpu;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  //mlxleft.begin(0x5B);

  if (!mpu.setup(0x68)) {  // change to your own address
        while (true) {
            Serial.println("MPU connection failed. Please check your connection with `connection_check` example.");
            delay(5000);
        }
    }
}

void loop() {
  if (mpu.update()) {
        static uint32_t prev_ms = millis();
        if (millis() > prev_ms + 100) {
            Serial.print("Yaw: ");
            Serial.print(mpu.getYaw(), 2);
            Serial.print(", Pitch: ");
            Serial.print(mpu.getPitch(), 2);
            Serial.print(", Roll: ");
            Serial.print(mpu.getRoll(), 2);  
            //Serial.print(" TC: ");
            //Serial.println(mlxleft.readObjectTempC());
  
            prev_ms = millis();
        }
  }
  //delay(1000);
}
