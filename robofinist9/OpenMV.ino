void readMVLeft() {
  if (Serial2.available()) {
    openMVReadLeft = Serial2.read();
    ignoreWordsLeft = blinkOut;

    Serial << "LEFT ";

    if (!goSlide && lNormal && state != 0 && state != 1 && state != 6 && state != 7 && !isMVImpact && abs(pitch) > 165) {
      Serial.print("left:");
      Serial << openMVReadLeft << " ";

      //if (!ignoreWordsLeft && openMVReadLeft == '0') minus(3, *countHLeft, *countSLeft, *countULeft);
      if (!ignoreWordsLeft && openMVReadLeft == 'H') minus(0, true);
      else if (!ignoreWordsLeft && openMVReadLeft == 'S') minus(1, true);
      else if (!ignoreWordsLeft && openMVReadLeft == 'U') minus(2, true);
      else minus(3, true);

      if (!ignoreWordsLeft && openMVReadLeft == 'G') countGreenLeft++;
      else countGreenLeft = 0;
      if (!ignoreWordsLeft && openMVReadLeft == 'R') countRedLeft++;
      else countRedLeft = 0;
      if (!ignoreWordsLeft && openMVReadLeft == 'Y') countYellowLeft++;
      else countYellowLeft = 0;

      if ((countHLeft > thresholdMVLeft || countSLeft > thresholdMVLeft
           || countRedLeft > thresholdMVLeft || countYellowLeft > thresholdMVLeft
           || countULeft > thresholdMVLeft || countGreenLeft > thresholdMVLeft)) {
        if (!mvInUsedCells(false)) {
          LETTER = openMVReadLeft;
          isMVLeft = true;
          isMVRight = false;
          stateOld = state;
          state = 6;
          ignoreWordsLeft = true;
          blinkIn = true;
          blinkOut = true;
          timer = millis();
          MVSetZero();
          //Serial2.write('A');
          leftMotorValue = 0;
          rightMotorValue = 0;
          stopUART();

          rememberEnc = (left - l0) / 2 + (right - r0) / 2;
        } else {
          Serial << "MVInUsedCells" << endl;
          MVSetZeroLeft();
        }
      }
    } else MVSetZeroLeft();
  }
}

void readMVRight() {
  if (Serial3.available()) {
    openMVReadRight = Serial3.read();
    ignoreWordsRight = blinkOut;

    Serial << "RIGHT ";
    //Serial.print("right ");
    if (!goSlide && rNormal && state != 0 && state != 1 && state != 6 && state != 7 && !isMVImpact && abs(pitch) > 165) {
      Serial.print("right:");
      Serial << openMVReadRight << " ";

      if (!ignoreWordsRight && openMVReadRight == 'H') minus(0, false);
      else if (!ignoreWordsRight && openMVReadRight == 'S') minus(1, false);
      else if (!ignoreWordsRight && openMVReadRight == 'U') minus(2, false);
      else minus(3, false);

      if (!ignoreWordsRight && openMVReadRight == 'G') countGreenRight++;
      else countGreenRight = 0;
      if (!ignoreWordsRight && openMVReadRight == 'R') countRedRight++;
      else countRedRight = 0;
      if (!ignoreWordsRight && openMVReadRight == 'Y') countYellowRight++;
      else countYellowRight = 0;

      if ((countHRight > thresholdMVRight || countSRight > thresholdMVRight
           || countRedRight > thresholdMVRight || countYellowRight > thresholdMVRight
           || countURight > thresholdMVRight || countGreenRight > thresholdMVRight)) {
        if (!mvInUsedCells(true)) {
          LETTER = openMVReadRight;
          isMVLeft = false;
          isMVRight = true;
          stateOld = state;
          state = 6;
          ignoreWordsRight = true;
          //zeroYaw = higherYaw(normalize(yaw - 90));
          //rememberEnc = (left - l0) / 2 + (right - l0) / 2;
          //if (countHRight > thresholdMVLeft || countSLeft > thresholdMVLeft)
          blinkIn = true;
          MVSetZero();
          leftMotorValue = 0;
          rightMotorValue = 0;
          stopUART();

          rememberEnc = (left - l0) / 2 + (right - r0) / 2;
          timer = millis(); 
        } else {
          Serial << "MVInUsedCells" << endl;
          MVSetZeroRight();
        }
      }
    } else MVSetZeroRight();
  }
}

void minus(int plus, bool mv) {
  if (mv) {
    if (plus == 3) {
      countHLeft = max(0, countHLeft - 1);
      countSLeft = max(0, countSLeft - 1);
      countULeft = max(0, countULeft - 1);
    } else if (plus == 2) {
      countHLeft = max(0, countHLeft - 1);
      countSLeft = max(0, countSLeft - 1);
      countULeft++;
    } else if (plus == 1) {
      countHLeft = max(0, countHLeft - 1);
      countSLeft++;
      countULeft = max(0, countULeft - 1);
    } else if (plus == 0) {
      countHLeft++;
      countSLeft = max(0, countSLeft - 1);
      countULeft = max(0, countULeft - 1);
    }
  } else {
    if (plus == 3) {
      countHRight = max(0, countHRight - 1);
      countSRight = max(0, countSRight - 1);
      countURight = max(0, countURight - 1);
    } else if (plus == 2) {
      countHRight = max(0, countHRight - 1);
      countSRight = max(0, countSRight - 1);
      countURight++;
    } else if (plus == 1) {
      countHRight = max(0, countHRight - 1);
      countSRight++;
      countURight = max(0, countURight - 1);
    } else if (plus == 0) {
      countHRight++;
      countSRight = max(0, countSRight - 1);
      countURight = max(0, countURight - 1);
    }
  }
}

void stopUART() {
  //while (Serial2.read() != 2) Serial2.write('A');
  //while (Serial3.read() != 2) Serial3.write('A');
}

void startUART() {
  //while (Serial2.read() != 255) Serial2.write('B');
  Serial.println("left_inited");
  //while (Serial3.read() != 255) Serial3.write('B');
  Serial.println("right_inited");
}

void MVSetZero() {
  MVSetZeroLeft();
  MVSetZeroRight();
}

void MVSetZeroLeft() {
  countHLeft = 0;
  countSLeft = 0;
  countULeft = 0;
  countRedLeft = 0;
  countGreenLeft = 0;
  countYellowLeft = 0;
}

void MVSetZeroRight() {
  countHRight = 0;
  countSRight = 0;
  countURight = 0;
  countRedRight = 0;
  countGreenRight = 0;
  countYellowRight = 0;
}
