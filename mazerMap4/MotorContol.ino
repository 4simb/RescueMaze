void AccForward(short int vv, float yy) {
  u = 6 * differenceYaw(yy, yaw) * (double)signYaw(yaw, yy);
  leftMotorValue = vv + u;
  rightMotorValue = vv - u;
}

void VLXForward(short int vv) {
  if (abs(rightVLX - leftVLX) < 50 && leftVLX < 180 && rightVLX < 180) u = 3.5 * (float)(rightVLX - leftVLX);
  else if (rightVLX > leftVLX && leftVLX < 180) u = 2 * (float)(130 - leftVLX);
  else if (leftVLX > rightVLX && rightVLX < 180) u = -2 * (float)(130 - rightVLX);
  else u = 0;

  leftMotorValue = vv - u;
  rightMotorValue = vv + u;
}

void VLXandIMU(short int vv, float yy) {
  uIMU = -6 * differenceYaw(yy, yaw) * (float)signYaw(yaw, yy);

  if (abs(rightVLX - leftVLX) < 50 && leftVLX < 165 && rightVLX < 165) {
    uVLX = -4.1 * (float)(rightVLX - leftVLX);
    //Serial.print("    ");
    //Serial.print("VLX");
  }
  else if (rightVLX > leftVLX && leftVLX < 165) uVLX = -3.2 * (float)(105 - leftVLX);
  else if (leftVLX > rightVLX && rightVLX < 165) uVLX = 3.2 * (float)(105 - rightVLX);
  else uVLX = 0;
  //uVLX *= -1;

  if (uVLX == 0) u = uIMU;
  //else u = uVLX;
  else u = uVLX * 0.58 + uIMU * 0.42; //0.5 0.5
  leftMotorValue = vv - u;
  rightMotorValue = vv + u;
}

void Turns() { //85
  err = differenceYaw(zeroYaw, yaw) * signYaw(zeroYaw, yaw);
  u = err * 3.2;
  if (abs(u) < 70) u = 70 * signYaw(zeroYaw, yaw);
  leftMotorValue = -u;
  rightMotorValue = u;
}

void TurnsWithEnc() {
  uEnc = -0.2 * (abs(left - l0) - abs(right - r0));
  if (abs(uEnc) > 90) uEnc = 90 * sign(uEnc);
  err = -differenceYaw(zeroYaw, yaw) * signYaw(zeroYaw, yaw);
  uIMU = err * 3;//6
  if (abs(uIMU) < 90) uIMU = 90 * sign(uIMU);
  u = 0.92 * uIMU + 0.08 * uEnc;
  leftMotorValue = u;
  rightMotorValue = -u;
}

int sign(float u) {
  if (u > 0) return 1;
  else if (u == 0) return 0;
  else return -1;
}

void setMotors(short int lmv, short int rmv) {
  //lmv *= -1;
  if (lmv > 0) {
    digitalWrite(lPin2, HIGH);
    digitalWrite(lPin, HIGH);
    analogWrite(lPin, max(255 - lmv, 0));
  } else {
    //yes
    lmv *= -1;
    digitalWrite(lPin2, LOW);
    digitalWrite(lPin, LOW);
    analogWrite(lPin, min(lmv, 255));
  }

  if (rmv > 0) {
    digitalWrite(rPin2, HIGH);
    digitalWrite(rPin, HIGH);
    analogWrite(rPin, max(255 - rmv, 0));
  } else {
    rmv *= -1;
    digitalWrite(rPin2, LOW);
    digitalWrite(rPin, LOW);
    analogWrite(rPin, min(rmv, 255));
  }
}

void leftPlus() {
  left++;
}

void rightPlus() {
  right++;
}

void leftTurnSwitch() {
  Turns();
  if (differenceYaw(zeroYaw, yaw) <= 1) {
    Serial.println("SU");
    state = 2;
    isGorOld = false;
    isMVLeftTurn = false;
    setting = yaw;
    l0 = left;
    r0 = right;

    robotDirection++;
    if (robotDirection > 3) robotDirection = 0;
  
    blinkOut = false;
    isMVLeft = false;
    isMVRight = false;
  }
}

void rightTurnSwitch() {
  Turns();
  Serial.print("   ");
  Serial.print(zeroYaw);
  if (differenceYaw(zeroYaw, yaw) <= 1) { //1
    //if (!isMVRight && !ignoreWords) state = 4;
    //else if (!isMVRight) state = 3;
    state = 4;

    timer = millis();
    isMVLeftTurn = false;
    //isMVLeftTurn = false;

    if (robotDirection == 0) robotDirection = 3;
    else robotDirection--;

    blinkOut = false;
    isMVLeft = false;
    isMVRight = false;
  }
}
