void throwOffKits() {
  leftMotorValue = 0;
  rightMotorValue = 0;
  
  if (isMVLeft) {
    digitalWrite(LED_LEFT, HIGH);
    digitalWrite(LED_RIGHT, LOW);
  }
  else if (isMVRight) {
    digitalWrite(LED_RIGHT, HIGH);
    digitalWrite(LED_LEFT, LOW);
  }

  if (blinkIn && millis() - timer > 6000) {
    blinkIn = false;

    wasMV.push_back(CameraParams(xRobot, yRobot, floors, robotDirection, !isMVLeft));
    if (stateOld == 2) {
      coordFuture(xRobot, yRobot, robotDirection);
      pair myPair = NNPair;
      wasMV.push_back(CameraParams(myPair.first, myPair.second, floors, robotDirection, !isMVLeft));
      isMVImpact = true;
    } else isMVImpact = false;

    isMVLeft = false;
    isMVRight = false;
    state = stateOld;
    
    timer = millis();
    digitalWrite(LED_LEFT, LOW);
    digitalWrite(LED_RIGHT, LOW);
    blinkOut = true;
    MVSetZero();
  }
}
