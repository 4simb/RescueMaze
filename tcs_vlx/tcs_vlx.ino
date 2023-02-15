#include "Adafruit_TCS34725.h"
#include <VL53L0X.h>

#define Sensor1_newAddress 47
#define Sensor2_newAddress 46
#define XSHUT_pin2 37
#define XSHUT_pin1 38

//VL53L0X vlxF; // Sensor1; 
//VL53L0X vlxL; //Sensor2;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);


/*void vlx_setup() {
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
}*/

void setup() {
  Serial.begin(115200);
  Serial.println("YES");
  delay(1000);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

   //vlx_setup();
  // Now we're ready to get readings!*/
}

short int centralVLX, leftVLX;
float r, g, b;
void loop() {
  //centralVLX = vlxF.readRangeContinuousMillimeters();
  //leftVLX = vlxL.readRangeContinuousMillimeters();

  tcs.getRGB(&r, &g, &b);
  Serial.print("R: "); Serial.print(r); Serial.print(" ");
  Serial.print("G: "); Serial.print(g); Serial.print(" ");
  Serial.print("B: "); Serial.print(b); Serial.print(" ");
  //Serial.print(centralVLX);
  //Serial.print(" ");
  //Serial.print(leftVLX);

  Serial.println();
  delay(10); 
}
