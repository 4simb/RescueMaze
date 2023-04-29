void question() {
  if (centralVLX != -1 && centralVLX <= 120 && !alWas) {
    state = 5;
  } else {
    alWas = false;
    if (isWallLR(leftVLX) && !ignore_left) {
      state = 0;
      zeroYaw = higherYaw(normalize(yaw + 90)); //Left
    } else if (centralVLX != -1 && !isWallCB(centralVLX)) {
      state = 1;
      zeroYaw = higherYaw(normalize(yaw - 90)); //Right
    } else {
      state = 2;
      setting = higherYaw(yaw);
    }

    //if (!ignoreWordsLeft) rememberEnc = 0;
    isGorOld = false;
  }

  if (color == 1 && !ignoreBlue) {
    state = 7;
    timer = millis();
  }

  ignore_left = false;
  if (state != 2 && state != 4) isMVImpact = false;
}

void alignment() {
  if (firstAlignment) {
    firstAlignment = false;
    timerAlignment = millis();
  } else if (!secondAlignment) {
    if (millis() - timerAlignment < 600) {
      leftMotorValue = 55;
      rightMotorValue = 55;
    } else secondAlignment = true;
  } else {
    if (centralVLX < 0) { //40
      leftMotorValue = -80;
      rightMotorValue = -80;
    } else {
      state = 4;
      secondAlignment = false;
      firstAlignment = true;
      alWas = true;
    }
  }
}
