void readMVLeft() {
  if (Serial2.available()) {
    Serial.print("left ");
    openMVReadLeft = Serial2.read();
    ignoreWordsLeft = blinkOut;

    if (leftVLX < 190) {
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
           || countULeft > thresholdMVLeft || countGreenLeft > thresholdMVLeft)
          && state != 0 && state != 1 && state != 6 && leftVLX < 190) {
        isMVLeft = true;
        stateOld = state;
        state = 6;
        ignoreWordsLeft = true;
        blinkIn = true;
        blinkOut = true;
        timer = millis();
        MVSetZero();
      }
    }
  }
}

void readMVRight() {
  if (Serial3.available()) {
    Serial.print("right ");
    openMVReadRight = Serial3.read();
    ignoreWordsRight = blinkOut;

    //Serial.print("right ");
    if (rightVLX < 190) {
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
           || countURight > thresholdMVRight || countGreenRight > thresholdMVRight)
          && state != 0 && state != 1 && state != 6 && rightVLX < 190) {
        isMVRight = true;
        stateOld = state;
        state = 6;
        ignoreWordsRight = true;
        //zeroYaw = higherYaw(normalize(yaw - 90));
        //rememberEnc = (left - l0) / 2 + (right - l0) / 2;
        //if (countHRight > thresholdMVLeft || countSLeft > thresholdMVLeft)
        blinkIn = true;
        MVSetZero();
      }
    }
  }
}

void MVSetZero() {
  countHLeft = 0;
  countSLeft = 0;
  countULeft = 0;
  countRedLeft = 0;
  countGreenLeft = 0;
  countYellowLeft = 0;
  countHRight = 0;
  countSRight = 0;
  countURight = 0;
  countRedRight = 0;
  countGreenRight = 0;
  countYellowRight = 0;
}
