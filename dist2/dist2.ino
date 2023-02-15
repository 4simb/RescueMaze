#include <Wire.h>
#include <VL53L0X.h>

VL53L0X vlxF;
VL53L0X vlxL;

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  vlxF.setTimeout(500);
  vlxL.setTimeout(500);
  
  if (!vlxF.init(0x41))
  {
    Serial.println("Failed to detect and initialize sensor! 29");
    while (1) {}
  }

  if (!vlxL.init(0x42))
  {
    Serial.println("Failed to detect and initialize sensor! 30");
    while (1) {}
  }

  vlxF.startContinuous();
  vlxL.startContinuous();
}

void loop()
{
  Serial.print("FORWARD: ");
  Serial.print(vlxF.readRangeContinuousMillimeters());
  if (vlxF.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  Serial.print(" LEFT: ");
  Serial.print(vlxL.readRangeContinuousMillimeters());
  if (vlxL.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  Serial.println();
}
