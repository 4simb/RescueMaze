bool state4First = false;
long lastCycle = 0;
void loop() {
  getVLX();
  getAngle();
  readRGB();
  //Serial << millis() - lastCycle << "  ";
  //lastCycle = millis();
  setRave();
  tumblerRead = digitalRead(TUMBLER_PIN);

  readMVRight();
  readMVLeft();

  printBase();

  if (!tumblerRead && tumblerReadOld) {
    state = 3;
    timer = millis();
    centralOld = centralVLX;
    backwardOld = backwardVLX;
    digitalWrite(LED_LEFT, LOW);
    digitalWrite(LED_RIGHT, LOW);
    action.clear();
    if (maze.size() != 1) deleteThisCell(xRobot, yRobot, maze.size() - 1);
    //maze.clear();

    robotDirection = dirCheckpoint;
    Trio pointNow = maze[indexCheckpoint][0];
    xRobot = pointNow.first;
    yRobot = pointNow.second;
    floors = pointNow.floor;
    
    //addCell(false, 0);

    bfs(true, pointNow);
    MVSetZero();
    tMVLeftOld = millis();
    tMVRightOld = millis();
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
        state4First = false;
        leftMotorValue = 0;
        rightMotorValue = 0;
        if (millis() - timer > 950) { //900
          Serial << "(" << xRobot << ", " << yRobot << ")" << endl;
          state4First = true;
          state = 3;
        }
        break;
      case 5: //alignment
        alignment(FORWARD);
        break;
      case 6: //victims
        victims();
        break;
      case 7: //BLUE
        blueFun();
        break;
      case 8: //BLACK
        blackFun();
        break;
      case 9: //AFTER-SLIDE FORWARD
        afterSlide();
        break;
      case 10: //IF LEFT MICRIC
        detour(false);
        break;
      case 11: //IF RIGHT MICRIC
        detour(true);
        break;
      case 12: //alignment
        alignment(BACKWARD);
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
