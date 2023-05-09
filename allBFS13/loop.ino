bool state4First = false;
void loop() {
  getVLX();
  getAngle();
  readRGB();
  setRave();
  tumblerRead = digitalRead(31);
  
  readMVRight();
  readMVLeft();

  //printBase();

  if (!tumblerRead && tumblerReadOld) {
    state = 3;
    timer = millis();
    centralOld = centralVLX;
    backwardOld = backwardVLX;
    digitalWrite(LED_LEFT, LOW);
    digitalWrite(LED_RIGHT, LOW);
    smezh.clear();
    addCell(false, 0);
    bfs();
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
        if (state4First) {
          setting = higherYaw(yaw);
        }

        AccForward(0, setting);
        state4First = false;
        leftMotorValue = 0;
        rightMotorValue = 0;
        if (millis() - timer > 1500) {
          Serial << "(" << xRobot << ", " << yRobot << ")" << endl;
          state4First = true;
          state = 3;
        } 
        break;
      case 5: //alignment
        alignmentForw();
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
