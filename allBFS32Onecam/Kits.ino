bool servoTurned = false;
long lastTurn = 0;
int throwCounter = -1;
long turnDelay = 0;
bool dontAsk = false;

void victims() {
  Serial << "LETTER: " << LETTER << " " << xRobot + fEditor.first << " " << yRobot + fEditor.second;
  Serial << robotDirection << " ";
  leftMotorValue = 0;
  rightMotorValue = 0;
  //setMotors(0, 0); //      ==================== CRINGE =====================

  if ((millis() - timer) / 300 % 2 == 0) {
    if (isMVLeft) {
      digitalWrite(LED_LEFT, HIGH);
      //digitalWrite(LED_RIGHT, LOW);
    }
    else if (isMVRight) {
      digitalWrite(LED_RIGHT, HIGH);
      //digitalWrite(LED_LEFT, LOW);
    }
  } else {
    digitalWrite(LED_RIGHT, LOW);
    digitalWrite(LED_LEFT, LOW);
  }

  int countLetters = 0;
  if (LETTER == 'H') countLetters = 3;
  else if (LETTER == 'S') countLetters = 2;
  else if (LETTER == 'Y' || LETTER == 'R') countLetters = 1;
  else if (LETTER == 'U' || LETTER == 'G') countLetters = 0;

  if (millis() - timer > 6300 && !dontAsk && throwOff(countLetters, isMVLeft)) dontAsk = true;

  if (blinkIn && dontAsk) {
    blinkIn = false;

    wasMV.push_back(CameraParams(xRobot + fEditor.first, yRobot + fEditor.second, floors, robotDirection, !isMVLeft));
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
    blinkOut = false;
    MVSetZero();
    LETTER = '0';

    startUART();
    dontAsk = false;
  }
}

bool throwOff(int num, bool mv) {
  if (throwCounter == -1) {
    turnDelay = 500;//2500 / num
    throwCounter = num;
  }

  if (throwCounter == 0 || num == 0) {
    throwCounter = -1;
    return true;
  }

  if (millis() - lastTurn > turnDelay) {
    if (!servoTurned) {
      if (mv) servo.write(SERVO_LEFT);
      else servo.write(SERVO_RIGHT);
      servoTurned = true;
    } else {
      servo.write(SERVO_CENTER);
      servoTurned = false;
      throwCounter--;
    }
    lastTurn = millis();
  }
  return false;
}
