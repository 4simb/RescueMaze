void question() {
  if (backwardVLX != -1 && backwardVLX <= 130 && !alWas) {
    state = 10;
  } if (centralVLX != -1 && centralVLX <= 130 && !alWas) {
    state = 5;
  } else {
    alWas = false;
    if (action.count() == 0) bfs();
    state = action.peek();

    if (state == 0) zeroYaw = higherYaw(normalize(yaw + 90));
    else if (state == 1) zeroYaw = higherYaw(normalize(yaw - 90));
    else setting = higherYaw(yaw);

    isGorOld = false;
  }

  if (color == 1 && !ignoreBlue) {
    state = 7;
    timer = millis();
  }

  ignore_left = false;
  if (state != 2 && state != 4) isMVImpact = false;
}

void alignmentForw() {
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

void alignmentBack() {
  if (firstAlignment) {
    firstAlignment = false;
    timerAlignment = millis();
  } else if (!secondAlignment) {
    if (millis() - timerAlignment < 800) {
      leftMotorValue = -55;
      rightMotorValue = -55;
    } else secondAlignment = true;
  } else {
    if (backwardVLX < 70) { //40
      leftMotorValue = 60;
      rightMotorValue = 60;
    } else {
      state = 4;
      secondAlignment = false;
      firstAlignment = true;
      alWas = true;
    }
  }
}
