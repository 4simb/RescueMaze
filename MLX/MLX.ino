#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlxleft = Adafruit_MLX90614();
//Adafruit_MLX90614 mlxright = Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);
  mlxleft.begin();
  //mlxright.begin();
}

void loop() {
  Serial.println(mlxleft.readObjectTempC());
  //Serial.println(mlxright.readObjectTempC());
  delay(100);
}
