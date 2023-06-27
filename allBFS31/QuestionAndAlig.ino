void question() {
  if (!toLeft) {
    if (centralVLX != -1 && centralVLX <= 170 && !alWas) {
      state = 5;
    } else {
      alWas = false;
      if (action.count() == 0 && !afterAll) bfs();
      else if (action.count() == 0 && afterAll) {
        digitalWrite(LED_LEFT, HIGH);
        digitalWrite(LED_RIGHT, HIGH);
        setMotors(0, 0);

        while (true) delay(10);
      }

      state = action.peek();

      if (state == 2 && centralVLX <= 160) {
        coordFuture(xRobot, yRobot, robotDirection);

        for (int i = 0; i < smezh.size(); ++i) {
          if (xRobot == smezh[i][0].first && yRobot == smezh[i][0].second
              && smezh[i][0].floor == floors) {
            deleteThisCell(NNPair.first, NNPair.second, i);
          }
        }

        bfs();
      }

      if (state == 0) zeroYaw = higherYaw(normalize(yaw + 90));
      else if (state == 1) zeroYaw = higherYaw(normalize(yaw - 90));
      else setting = higherYaw(yaw);
    }
  } else {
    if (centralVLX != -1 && centralVLX <= 120 && !alWas) {
      state = 5;
    } else {
      alWas = false;
      if (isWallLR(leftVLX)) {
        state = 0;
        zeroYaw = higherYaw(normalize(yaw + 90)); //Left
      } else if (centralVLX != -1 && !isWallCB(centralVLX)) {
        state = 1;
        zeroYaw = higherYaw(normalize(yaw - 90)); //Right
      } else {
        state = 2;
        setting = higherYaw(yaw);
      }
    }
  }

  if (colorBase == 1 && !ignoreBlue) {
    state = 7;
    timer = millis();
  }

  if (state != 2 && state != 4) isMVImpact = false;
}

void alignmentForw() {
  if (digitalRead(LBUTTON_UP)) leftMotorValue = 75;
  else leftMotorValue = 0;
  if (digitalRead(RBUTTON_UP)) rightMotorValue = 75;
  else rightMotorValue = 0;

  if (!digitalRead(LBUTTON_UP) && !digitalRead(RBUTTON_UP)) {
    //state = 4;
    //alWas = true;
    secondAlignment = true;
  }

  if (secondAlignment) {
    if (centralVLX < 63) { //65
      leftMotorValue = -60;
      rightMotorValue = -60;
    } else {
      secondAlignment = false;
      alWas = true;
      state = 4;
    }
  }

  //Serial << "DIGITAL: " << digitalRead(BUTTON_LEFT) << digitalRead(BUTTON_RIGHT) << " " ;
}