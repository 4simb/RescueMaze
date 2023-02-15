#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
Adafruit_VL53L0X left = Adafruit_VL53L0X();

void setup() {
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin(0x3A)) {
    Serial.println(F("Failed to boot VL53L0X  30"));
    while(1);
  }

  lox.setAddress(0x3A);

  //for (int i = 49; i < 100; ++i) {
    if (!left.begin(0x30)) {
      //Serial.println(i);
      //while(1);
      //break;
      Serial.println(F("Failed to boot VL53L0X  29"));
      while(1);
    }

    left.setAddress(0x2B);
  //}
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
}


void loop() {
  VL53L0X_RangingMeasurementData_t measure;
  VL53L0X_RangingMeasurementData_t measure2;
    
  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
  left.rangingTest(&measure2, false);
  
  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); Serial.print(measure.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
  }

  if (measure2.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print(" Distance (mm): "); Serial.println(measure2.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
  }
    
  delay(10);
}
