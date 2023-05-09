void throwOffKits() {
  Serial << "LETTER: " << LETTER << " " << xRobot + fEditor.first << " " << yRobot + fEditor.second;
  Serial << robotDirection << " ";
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

    wasMV.push_back(CameraParams(xRobot + fEditor.first, yRobot + fEditor.second, floors, robotDirection, !isMVLeft, LETTER));
    if (stateOld == 2) isMVImpact = true;
    else isMVImpact = false;
    //  coordFuture(xRobot, yRobot, robotDirection, false);
    //  pair myPair = NNPair;
    //  wasMV.push_back(CameraParams(myPair.first, myPair.second, floors, robotDirection, !isMVLeft));
    //  
    //} else isMVImpact = false;

    Serial << "WAS_MV: " << endl;
    for (int i = 0; i < wasMV.size(); ++i) {
      Serial << wasMV[i].first << " " << wasMV[i].second << endl;
    }

    isMVLeft = false;
    isMVRight = false;
    state = stateOld;
    
    timer = millis();
    digitalWrite(LED_LEFT, LOW);
    digitalWrite(LED_RIGHT, LOW);
    blinkOut = true;
    MVSetZero();
    LETTER = '0';
    startUART();
  }
}
