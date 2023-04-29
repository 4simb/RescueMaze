void loop() {
  getVLX();
  getAngle();
  readRGB();
  setRave();
  tumblerRead = digitalRead(31);
  
  readMVRight();
  readMVLeft();

  if (state != 4) printBase();

  if (!tumblerRead && tumblerReadOld) {
    state = 3;
    timer = millis();
    centralOld = centralVLX;
    backwardOld = backwardVLX;
    digitalWrite(LED_LEFT, LOW);
    digitalWrite(LED_RIGHT, LOW);
  } else if (tumblerRead && !tumblerReadOld) {
    printCoords();
  }

  //setMotors(-90, -90);
  if (!tumblerRead) {
    switch (state) {
      case 0: //leftTurn
        leftTurnSwitch();
        break;
      case 1: //rightTurn
        rightTurnSwitch();
        break;
      case 2: //forward
        caseForward();
        break;
      case 3: //question
        question();
        break;
      case 4: //stop
        leftMotorValue = 0;
        rightMotorValue = 0;
        if (millis() - timer > 1500) state = 3;
        Serial << "(" << xRobot << ", " << yRobot << ")" << endl; 
        break;
      case 5: //alignment
        alignment();
        break;
      case 6: //throw off
        throwOffKits();
        break;
      case 7: //BLUE
        blueFun();
        break;
      case 8: //BLACK
        blackFun();
        break;
      case 9:
        someForw();
        break;
    }

    setMotors(leftMotorValue, rightMotorValue);

    if (state == 0 || state == 1 || state == 9) {
      centralOld = centralVLX;
      backwardOld = backwardVLX;
      if (state != 9) {
        l0 = left;
        r0 = right;
      }
    }
  } else setMotors(0, 0);

  tumblerReadOld = tumblerRead;
  Serial.println();
}
