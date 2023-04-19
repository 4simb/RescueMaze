void vlx_setup() {
  pinMode(XSHUT_pinB, OUTPUT);
  pinMode(XSHUT_pinR, OUTPUT);
  pinMode(XSHUT_pinL, OUTPUT);
  pinMode(XSHUT_pinF, OUTPUT);
  
  digitalWrite(XSHUT_pinB, LOW);
  digitalWrite(XSHUT_pinR, LOW);
  digitalWrite(XSHUT_pinL, LOW);
  digitalWrite(XSHUT_pinF, LOW);
  delay(10);

  digitalWrite(XSHUT_pinB, HIGH);
  delay(100);
  vlxB.setAddress(SensorB_newAddress);
  Serial.println(vlxB.getAddress());
  vlxB.init();
  
  digitalWrite(XSHUT_pinL, HIGH);
  delay(100);
  vlxL.setAddress(SensorL_newAddress);
  Serial.println(vlxL.getAddress());
  vlxL.init();

  digitalWrite(XSHUT_pinR, HIGH);
  delay(100);
  vlxR.setAddress(SensorR_newAddress);
  Serial.println(vlxR.getAddress());
  vlxR.init();

  digitalWrite(XSHUT_pinF, HIGH);
  delay(100);
  vlxF.setAddress(SensorF_newAddress);
  Serial.println(vlxF.getAddress());
  vlxF.init();

  Serial.println("Hello! It's me");
  Serial.println("Init end");
  delay(2500);
  vlxB.setTimeout(50);
  vlxR.setTimeout(50);
  vlxL.setTimeout(50);
  vlxF.setTimeout(50);

  vlxB.startContinuous();
  vlxR.startContinuous();
  vlxL.startContinuous();
  vlxF.startContinuous();
  Serial.println("Setup end");
}

void getVLX() {
  backwardVLX = vlxB.readRangeContinuousMillimeters();
  rightVLX = vlxR.readRangeContinuousMillimeters();
  leftVLX = vlxL.readRangeContinuousMillimeters(); //Continuous
  centralVLX = vlxF.readRangeContinuousMillimeters();
}

int valueForward(int centr) {
  for (offerI = offerSize - 2; offerI >= 0; --offerI) {
    if (centr > offerForward[offerI] && centr - offerForward[offerI] > 50) {
      return offerForward[offerI];
    }
  }

  return 0;
}

int valueBackward(int centr) {
  for (offerI = 0; offerI < offerSize - 1; ++offerI) {
    if (centr < offerBackward[offerI] && offerBackward[offerI] - centr > 50) {
      return offerBackward[offerI];
    }
  }

  return 0;
}
