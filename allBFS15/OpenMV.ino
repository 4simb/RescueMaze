void readMVLeft() {
  if (Serial2.available()) {
    openMVReadLeft = Serial2.read();
    ignoreWordsLeft = blinkOut;

    if (!goSlide && lNormal && state != 0 && state != 1 && state != 6) {
      Serial.print("left:");
      Serial << openMVReadLeft << " ";
      
      if (!ignoreWordsLeft && openMVReadLeft == 'H') countHLeft++;
      else countHLeft = 0;
      if (!ignoreWordsLeft && openMVReadLeft == 'S') countSLeft++;
      else countSLeft = 0;
      if (!ignoreWordsLeft && openMVReadLeft == 'U') countULeft++;
      else countULeft = 0;
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
          stopUART();
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
    if (!goSlide && rNormal && state != 0 && state != 1 && state != 6) {
      Serial.print("right:");
      Serial << openMVReadRight << " "; 
      if (!ignoreWordsRight && openMVReadRight == 'H') countHRight++;
      else countHRight = 0;
      if (!ignoreWordsRight && openMVReadRight == 'S') countSRight++;
      else countSRight = 0;
      if (!ignoreWordsRight && openMVReadRight == 'U') countURight++;
      else countURight = 0;
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
          stopUART();
        } else {
          Serial << "MVInUsedCells" << endl;
          MVSetZeroRight();
        }
      }
    } else MVSetZeroRight();
  }
}

void stopUART() {
  Serial2.write('A');
  Serial3.write('A');
  //while (Serial2.available()) Serial2.read();
  //while (Serial3.available()) Serial3.read();
  //Serial2.flush();
  //Serial3.flush();
}

void startUART() {
  Serial2.write('B');
  Serial3.write('B');

  Serial2.write('B');
  Serial3.write('B');
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
