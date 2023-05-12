void AccForward(short int vv, float yy) {
  u = 13 * differenceYaw(yy, yaw) * (double)signYaw(yaw, yy);
  leftMotorValue = vv + u;
  rightMotorValue = vv - u;
}

void VLXForward(short int vv) {
  if (abs(rightVLX - leftVLX) < 50 && leftVLX < 160 && rightVLX < 160) u = 3.5 * (float)(rightVLX - leftVLX);
  else if (rightVLX > leftVLX && leftVLX < 160) u = 2 * (float)(130 - leftVLX);
  else if (leftVLX > rightVLX && rightVLX < 160) u = -2 * (float)(130 - rightVLX);
  else u = 0;

  leftMotorValue = vv - u;
  rightMotorValue = vv + u;
}

void VLXandIMU(short int vv, float yy) {
  uIMU = -7 * differenceYaw(yy, yaw) * (float)signYaw(yaw, yy);
  
  if (abs(rightVLX - leftVLX) < 50 && leftVLX < 150 && rightVLX < 150) {
    uVLX = -4.1 * (float)(rightVLX - leftVLX);
    //Serial.print("    ");
    //Serial.print("VLX");
  }
  else if (rightVLX > leftVLX && leftVLX < 150) uVLX = -3.2 * (float)(115 - leftVLX);
  else if (leftVLX > rightVLX && rightVLX < 150) uVLX = 3.2 * (float)(115 - rightVLX);
  else uVLX = 0;
  //uVLX *= -1;

  if (uVLX == 0) u = uIMU;
  //else u = uVLX;
  else u = uVLX * 0.53 + uIMU * 0.47; //0.58 0.42
  leftMotorValue = vv - u;
  rightMotorValue = vv + u;
}

void Turns() { //85
  err = differenceYaw(zeroYaw, yaw) * signYaw(zeroYaw, yaw);
  p = err * 2.8;
  d = (err - errOld) * 2;
  u = p + d;
  if (abs(u) < 50) u = 50 * sign(u);
  leftMotorValue = -u;
  rightMotorValue = u;
  errOld = err;
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
  //leftMotorValue *= 1.15;
  if (differenceYaw(zeroYaw, yaw) <= 1) {
    Serial.println("SU");
    action.pop();
    state = 4;
    setting = yaw;
    l0 = left;
    r0 = right;

    robotDirection++;
    if (robotDirection > 3) robotDirection = 0;
  
    blinkOut = false;
    isMVLeft = false;
    isMVRight = false;

    timer = millis();
  }
}

void rightTurnSwitch() {
  Turns();
  //rightMotorValue *= 1.15;
  Serial.print("   ");
  Serial.print(zeroYaw);
  if (differenceYaw(zeroYaw, yaw) <= 1) { //1
    //if (!isMVRight && !ignoreWords) state = 4;
    //else if (!isMVRight) state = 3;
    action.pop();
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
