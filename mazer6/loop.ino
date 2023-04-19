void loop() {
  getVLX();
  getAngle();
  readRGB();
  tumblerRead = digitalRead(31);

  readMVRight();
  readMVLeft();

  printAll();

  if (tumblerRead != tumblerReadOld) {
    state = 3;
    timer = millis();
    centralOld = centralVLX;
    backwardOld = backwardVLX;
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
    }

    setMotors(leftMotorValue, rightMotorValue);

    if (state == 0 || state == 1) {
      centralOld = centralVLX;
      backwardOld = backwardVLX;
      l0 = left;
      r0 = right;
    }
  } else setMotors(0, 0);

  tumblerReadOld = tumblerRead;
  Serial.println();
}
