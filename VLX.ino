void vlx_setup() {
  pinMode(XSHUT_pin1, OUTPUT);
  pinMode(XSHUT_pin2, OUTPUT);
  pinMode(XSHUT_pin3, OUTPUT);
  digitalWrite(XSHUT_pin1, LOW);
  digitalWrite(XSHUT_pin2, LOW);
  digitalWrite(XSHUT_pin3, LOW);
  delay(10);
  digitalWrite(XSHUT_pin1, HIGH);
  vlxR.setAddress(Sensor1_newAddress);
  //pinMode(XSHUT_pin2, INPUT);
  delay(10);
  digitalWrite(XSHUT_pin2, HIGH);
  vlxF.setAddress(Sensor2_newAddress);
  //pinMode(XSHUT_pin1, INPUT);
  delay(10);
  
  digitalWrite(XSHUT_pin3, HIGH);
  vlxL.setAddress(Sensor3_newAddress);
  //pinMode(XSHUT_pin1, INPUT);
  delay(10);

  Serial.println("Hello! It's me");
  Serial.println("Init end");
  delay(2000);
  vlxF.setTimeout(50);
  vlxL.setTimeout(50);
  vlxR.setTimeout(50);
  
  vlxF.init();
  vlxL.init();
  vlxR.init();

  vlxF.startContinuous();
  vlxL.startContinuous();
  vlxR.startContinuous();
  //vlxF.setMeasurementTimingBudget(20000);
  // vlxL.setMeasurementTimingBudget(20000);
  //Sensor3.startContinuous();
  Serial.println("Setup end");
}

void getVLX() {
  leftVLX = vlxL.readRangeContinuousMillimeters(); //Continuous
  centralVLX = vlxF.readRangeContinuousMillimeters();
  rightVLX = vlxR.readRangeContinuousMillimeters();
}
