enum back_microswitchs {
  MICROSWITCH_LEFT,
  MICROSWITCH_RIGHT
};

bool align = true;
void question() {
  if (!toLeft) {
    //alWas = true; //=============================FOR_DELETE===================================
    //if ((centralVLX != -1 && centralVLX <= 180 || backwardVLX != -1 && backwardVLX <= 200) && !alWas) {
    if (!alWas) {
      timAl = millis();
      if (!forwRave && centralVLX != -1 && centralVLX <= 180) state = 5;
      else if (!backRave && backwardVLX != -1 && backwardVLX <= 200) state = 12;
      else alWas = true;
      //timAl = -1;
    } else {
      timAl = -1;
      Serial.println("CHECK_");
      alWas = false;
      if (action.count() == 0 && !afterAll) bfs();
      else if (action.count() == 0 && afterAll) {
        digitalWrite(LED_LEFT, HIGH);
        digitalWrite(LED_RIGHT, HIGH);
        setMotors(0, 0);

        while (true) delay(10);
      }

      Serial.println("CHECK_");
      state = action.peek();
      Serial.println(state);
      Serial.println("CHECK_");

      Serial.println("CHECK_");
      if (state == 2 && centralVLX <= 160) {
        pair p = coordFuture(xRobot, yRobot, robotDirection);

        for (int i = 0; i < maze.size(); ++i) {
          if (xRobot == maze[i][0].first && yRobot == maze[i][0].second
              && maze[i][0].floor == floors) {
            deleteThisCell(p.first, p.second, i);
          }
        }

        Serial.println("CHECK_BFS");
        bfs();
      }

      Serial.println("CHECK_");
      if (state == 0) zeroYaw = higherYaw(normalize(yaw + 90));
      else if (state == 1) zeroYaw = higherYaw(normalize(yaw - 90));
      else setting = higherYaw(yaw);

      Serial.println("CHECK_");
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

void alignment(float napr) {
  int motorSpeed = 85;
  
  //if (millis() - timAl > 4100) {
  //  alWas = true;
  //  state = 3;
  //}
  
  if (napr == FORWARD) {
    if (digitalRead(LBUTTON_UP)) leftMotorValue = motorSpeed;
    else leftMotorValue = 0;
    if (digitalRead(RBUTTON_UP)) rightMotorValue = motorSpeed;
    else rightMotorValue = 0;

    if (!digitalRead(LBUTTON_UP) && !digitalRead(RBUTTON_UP) || centralVLX < 50) secondAlignment = true;  //55

    if (secondAlignment) {
      if (centralVLX < 70) {  //65
        leftMotorValue = -motorSpeed;
        rightMotorValue = -motorSpeed;
      } else {
        secondAlignment = false;
        alWas = true;
        state = 4;
        timAl = -1;

        yFirst -= yaw - higherYaw(yaw);
      }
    }
  } else if (napr == BACKWARD) {
    //motorSpeed -= 20;
    leftMotorValue = -motorSpeed - 10;
    rightMotorValue = -motorSpeed - 10;

    if (backwardVLX < 27 || (backMicrPushed(MICROSWITCH_RIGHT) && backMicrPushed(MICROSWITCH_LEFT))) secondAlignment = true;
    //                35
    //if (backwardVLX < 35) secondAlignment = true;

    if (secondAlignment) {
      if (backwardVLX < 70) {  //65
        leftMotorValue = motorSpeed;
        rightMotorValue = motorSpeed;
      } else {
        secondAlignment = false;
        alWas = true;
        state = 4;

        yFirst -= yaw - higherYaw(yaw);
      }
    }

    if (!digitalRead(LBUTTON_UP) || !digitalRead(RBUTTON_UP)) {
      secondAlignment = false;
      alWas = true;
      state = 4;
      timAl = -1;
    }
  } else {
    alWas = true;
    state = 4;
    timAl = -1;
  }
}

int c1 = 0, c2 = 0;
void detour(bool napr) {
  if (c1 < 3) {
    //setMotors(-100, -100);
    leftMotorValue = -100;
    rightMotorValue = -100;
    c1++;
  } else if (c2 < 6) {  //8
    if (!napr) {
      leftMotorValue = 100;
      rightMotorValue = -100;
    } else {
      leftMotorValue = -100;
      rightMotorValue = 100;
    }

    c2++;
  } else {
    c1 = 0;
    c2 = 0;
    //l0 = left;
    //r0 = right;
    state = 2;
    //rememberEnc = ;
  }

  Serial << "C1:" << c1 << " C2:" << c2 << "  ==========DETOUR=========== ";
}

bool backMicrPushed(int micric) {
  uint16_t a;
  if (micric == MICROSWITCH_LEFT) a = analogRead(MICR_BACK_LEFT);
  else if (micric == MICROSWITCH_RIGHT) a = analogRead(MICR_BACK_RIGHT);

  if (a > 512) return false;
  else return true;
}