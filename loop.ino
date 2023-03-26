void loop() {
  getVLX();
  getAngle();
  readMV();

  Serial.print(state);
  Serial.print(" ");
  Serial.print(yaw);
  Serial.print(" ");
  Serial.print(pitch);
  Serial.print(" ");
  Serial.print(centralVLX);
  Serial.print(" ");
  Serial.print(leftVLX);
  Serial.print(" ");
  Serial.print(rightVLX);
  Serial.print(" ");
  Serial.print(setting);
  Serial.print(" ");
  Serial.print(millis());
  Serial.print(" ");
  Serial.print(openMVRead);
  Serial.print(" ");
  Serial.print(centralOld);
  Serial.println();

  //setMotors(-90, -90);
  switch (state) {
    case 0: //leftTurn
      TurnsWithEnc();
      if (differenceYaw(zeroYaw, yaw) <= 1) {
        Serial.println("SU");
        if (!isMVLeft) state = 2;
        else state = 6;
        setting = yaw;
        l0 = left;
        r0 = right;
      }
      break;
    case 1: //rightTurn
      TurnsWithEnc();
      if (differenceYaw(zeroYaw, yaw) <= 1) {
        if (!isMVRight && !ignoreWords) state = 4;
        else if (!isMVRight) state = 3;
        canChangeMVLeft = true;
        timer = millis();
      }
      break;
    case 2: //forward
      if ((centralOld >= 800 && ((left - l0) + (right - r0)) / 2 + rememberEnc < 1700)
          || (centralOld < 800 && (centralOld - centralVLX < 310 && centralVLX >= 21))) {
        VLXandIMU(95, setting);
      } else {
        rememberEnc = 0;
        state = 4;
        timer = millis();
      }
      break;
    case 3: //question
      if (centralVLX != -1 && centralVLX <= 200 && !alWas) {
        state = 5;
      } else {
        alWas = false;
        if (leftVLX >= 300) {
          state = 0;
          zeroYaw = higherYaw(normalize(yaw - 90)); //Left
        } else if (centralVLX != -1 && centralVLX <= 200) {
          state = 1;
          zeroYaw = higherYaw(normalize(yaw + 90)); //Right
        } else {
          state = 2;
          setting = higherYaw(yaw);
        }

        if (!ignoreWords) rememberEnc = 0;
      }
      break;
    case 4: //stop
      leftMotorValue = 0;
      rightMotorValue = 0;
      if (millis() - timer > 1500) state = 3;
      break;
    case 5: //alignment
      if (firstAlignment) {
        firstAlignment = false;
        timerAlignment = millis();
      } else if (!secondAlignment) {
        if (millis() - timerAlignment < 1300) {
          leftMotorValue = 65;
          rightMotorValue = 65;
        } else secondAlignment = true;
      } else {
        if (centralVLX < 35) {
          leftMotorValue = -80;
          rightMotorValue = -80;
        } else {
          state = 4;
          secondAlignment = false;
          firstAlignment = true;
          alWas = true;
        }
      }
      break;
    case 6: //throw off
      Serial.println("YUP");
      if (isMVLeft) {
        state = 1;
        zeroYaw = higherYaw(normalize(yaw + 90)); //Right
        isMVLeft = false;
      } else if (isMVRight) {
        state = 0;
        zeroYaw = higherYaw(normalize(yaw - 90)); //Left
        isMVRight = false;
      }
      break;
  }

  setMotors(leftMotorValue, rightMotorValue);
  if (state != 2) {
    centralOld = centralVLX;

    if (state != 0 && state != 1) {
      l0 = left;
      r0 = right;
    }
  }
}
