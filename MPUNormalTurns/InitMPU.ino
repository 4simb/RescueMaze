void initMPU() {
// Set up the interrupt pin, its set as active high, push-p
  
  Serial.println("MPU9250");
//  display.setTextSize(1);
//  display.setCursor(0, 20);
  Serial.println("9-DOF 16-bit");
//  display.setCursor(0, 30); 
  Serial.println("motion sensor");
//  display.setCursor(20,40); 
  Serial.println("60 ug LSB");
//  display.display();
  delay(800);

  // Read the WHO_AM_I register, this is a good test of communication
  byte c = readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);  // Read WHO_AM_I register for MPU-9250
  Serial.print("MPU9250 "); Serial.print("I AM "); Serial.print(c, HEX); Serial.print(" I should be "); Serial.println(0x71, HEX);
  delay(800); 

  if (c == 0x71) // WHO_AM_I should always be 0x68
  {  
    Serial.println("MPU9250 is online...");
    
    MPU9250SelfTest(SelfTest); // Start by performing self test and reporting values
    Serial.print("x-axis self test: acceleration trim within : "); Serial.print(SelfTest[0],1); Serial.println("% of factory value");
    Serial.print("y-axis self test: acceleration trim within : "); Serial.print(SelfTest[1],1); Serial.println("% of factory value");
    Serial.print("z-axis self test: acceleration trim within : "); Serial.print(SelfTest[2],1); Serial.println("% of factory value");
    Serial.print("x-axis self test: gyration trim within : "); Serial.print(SelfTest[3],1); Serial.println("% of factory value");
    Serial.print("y-axis self test: gyration trim within : "); Serial.print(SelfTest[4],1); Serial.println("% of factory value");
    Serial.print("z-axis self test: gyration trim within : "); Serial.print(SelfTest[5],1); Serial.println("% of factory value");
 
    calibrateMPU9250(gyroBias, accelBias); // Calibrate gyro and accelerometers, load biases in bias registers

    Serial.println("MPU9250 bias");

    Serial.println(" x   y   z  ");


    Serial.print((int)(1000*accelBias[0])); 
    Serial.print((int)(1000*accelBias[1])); 
    Serial.print((int)(1000*accelBias[2])); 
    Serial.print("mg");

    Serial.print(gyroBias[0], 1); 
    Serial.print(gyroBias[1], 1); 
    Serial.print(gyroBias[2], 1); 
    Serial.println("o/s"); 
    delay(1000); 
  
    initMPU9250(); 
    Serial.println("MPU9250 initialized for active data mode...."); // Initialize device for active mode read of acclerometer, gyroscope, and temperature
  
    // Read the WHO_AM_I register of the magnetometer, this is a good test of communication
    byte d = readByte(AK8963_ADDRESS, WHO_AM_I_AK8963);  // Read WHO_AM_I register for AK8963
    Serial.print("AK8963 "); Serial.print("I AM "); Serial.print(d, HEX); Serial.print(" I should be "); Serial.println(0x48, HEX);

    delay(1000); 
  
    // Get magnetometer calibration from AK8963 ROM
    initAK8963(magCalibration); Serial.println("AK8963 initialized for active data mode...."); // Initialize device for active mode read of magnetometer
    getMres();
    magcalMPU9250(magBias,magScale); 

  
  if(SerialDebug) {
    //  Serial.println("Calibration values: ");
    Serial.print("X-Axis sensitivity adjustment value "); Serial.println(magCalibration[0], 2);
    Serial.print("Y-Axis sensitivity adjustment value "); Serial.println(magCalibration[1], 2);
    Serial.print("Z-Axis sensitivity adjustment value "); Serial.println(magCalibration[2], 2);
  }
  
//    display.clearDisplay();
//    display.setCursor(20,0); 
    Serial.println("AK8963");
//    display.setCursor(0,10);
    Serial.println("ASAX ");
//    display.setCursor(50,10);
    Serial.println(magCalibration[0], 2);
//    display.setCursor(0,20); 
    Serial.println("ASAY "); 
//    display.setCursor(50,20);
    Serial.println(magCalibration[1], 2);
//    display.setCursor(0,30);
    Serial.println("ASAZ ");
//    display.setCursor(50,30); 
    Serial.println(magCalibration[2], 2);
//    display.display();
    delay(1000);  
  }
  else
  {
    Serial.print("Could not connect to MPU9250: 0x");
    Serial.println(c, HEX);
    while(1) ; // Loop forever if communication doesn't happen
  }
}
