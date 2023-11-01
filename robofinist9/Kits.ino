bool servoTurned = false;
long lastTurn = 0;
int throwCounter = -1;
long turnDelay = 0;
bool dontAsk = false;
bool endProcess = true, endTimeout = true, goNextIf = false; 
int timeFall = 1000;
float servoValue = 0;

bool startLastDelay = false;
int lastDelay;

void victims() {
  Serial << "LETTER: " << LETTER << " " << xRobot + fEditor.first << " " << yRobot + fEditor.second;
  Serial << robotDirection << " ";
  leftMotorValue = 0;
  rightMotorValue = 0;
  //setMotors(0, 0); //      ==================== CRINGE =====================

  if ((millis() - timer) / 300 % 2 == 0) { //300
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

  if (millis() - timer > 5100 && !dontAsk && throwOff(countLetters, isMVLeft)) dontAsk = true;
  //6300

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

    if (isMVLeft) while (Serial2.available()) Serial2.read();
    else if (isMVRight) while (Serial3.available()) Serial3.read();

    isMVLeft = false;
    isMVRight = false;
    state = stateOld;

    timer = millis();
    digitalWrite(LED_LEFT, LOW);
    digitalWrite(LED_RIGHT, LOW);
    blinkOut = false;
    MVSetZero();
    LETTER = '0';

    Serial.println("START_UART");
    startUART();
    dontAsk = false;
    timAl = millis();
  }
}

bool throwOff(int num, bool mv) {
  if (throwCounter == -1) {
    turnDelay = 550;  //2500 / num
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
      if (mv) servo.write(SERVO_CENTER);
      else servo.write(SERVO_CENTER - 15);

      servoTurned = false;
      throwCounter--; 
    }

    lastTurn = millis();
  }

  return false;
}