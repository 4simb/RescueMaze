void question() {
  if (!toLeft) {
    if ((centralVLX != -1 && centralVLX <= 180 || backwardVLX != -1 && backwardVLX <= 200) && !alWas) {
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
        pair p = coordFuture(xRobot, yRobot, robotDirection);

        for (int i = 0; i < maze.size(); ++i) {
          if (xRobot == maze[i][0].first && yRobot == maze[i][0].second
              && maze[i][0].floor == floors) {
            deleteThisCell(p.first, p.second, i);
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
        zeroYaw = higherYaw(normalize(yaw + 90));  //Left
      } else if (centralVLX != -1 && !isWallCB(centralVLX)) {
        state = 1;
        zeroYaw = higherYaw(normalize(yaw - 90));  //Right
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

void alignment() {
  if (centralVLX < backwardVLX && !forwRave) {
    if (digitalRead(LBUTTON_UP)) leftMotorValue = 75;
    else leftMotorValue = 0;
    if (digitalRead(RBUTTON_UP)) rightMotorValue = 75;
    else rightMotorValue = 0;

    if (!digitalRead(LBUTTON_UP) && !digitalRead(RBUTTON_UP) || centralVLX < 55) secondAlignment = true;

    if (secondAlignment) {
      if (centralVLX < 70) {  //65
        leftMotorValue = -60;
        rightMotorValue = -60;
      } else {
        secondAlignment = false;
        alWas = true;
        state = 4;
      }
    }
  } else if (!backRave) {
    leftMotorValue = -85;
    rightMotorValue = -85;

    if (backwardVLX < 32) secondAlignment = true;

    if (secondAlignment) {
      if (backwardVLX < 70) {  //65
        leftMotorValue = 60;
        rightMotorValue = 60;
      } else {
        secondAlignment = false;
        alWas = true;
        state = 4;
      }
    }
  } else {
    alWas = true;
    state = 4;
  }

  //Serial << "DIGITAL: " << digitalRead(BUTTON_LEFT) << digitalRead(BUTTON_RIGHT) << " " ;
}
