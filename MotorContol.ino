void AccForward(short int vv, float yy) {
  u = 6 * differenceYaw(yy, yaw) * (double)signYaw(yaw, yy); 
  leftMotorValue = vv + u;
  rightMotorValue = vv - u;
}

void VLXForward(short int vv) {
  if (abs(rightVLX - leftVLX) < 40 && leftVLX < 150 && rightVLX < 150) u = 2.5 * (float)(rightVLX - leftVLX);
  else if (rightVLX > leftVLX && leftVLX < 180) u = 2 * (float)(130 - leftVLX);
  else if (leftVLX > rightVLX && rightVLX < 180) u = -2 * (float)(130 - rightVLX); 
  else u = 0;
  
  leftMotorValue = vv - u;
  rightMotorValue = vv + u;
}

void VLXandIMU(short int vv, float yy) {
  uIMU = -6.5 * differenceYaw(yy, yaw) * (float)signYaw(yaw, yy); 
  
  if (abs(rightVLX - leftVLX) < 50 && leftVLX < 160 && rightVLX < 160) uVLX = 3 * (float)(rightVLX - leftVLX);
  else if (rightVLX > leftVLX && leftVLX < 160) uVLX = 2.5 * (float)(135 - leftVLX);
  else if (leftVLX > rightVLX && rightVLX < 160) uVLX = -2.5 * (float)(135 - rightVLX); 
  else uVLX = 0;

  if (uVLX == 0) u = uIMU;
  else u = uVLX * 0.6 + uIMU * 0.4;
  leftMotorValue = vv - u;
  rightMotorValue = vv + u;
}

void Turns() {
  err = differenceYaw(zeroYaw, yaw) * signYaw(zeroYaw, yaw);
  u = err * 2.25;
  if (abs(u) < 70) u = 70 * signYaw(zeroYaw, yaw);
  leftMotorValue = -u;
  rightMotorValue = u;
}

void TurnsWithEnc() {
  uEnc = -3 * ((left - l0) - (right - r0));
  err = differenceYaw(zeroYaw, yaw) * signYaw(zeroYaw, yaw);
  uIMU = err * 2.4;
  if (abs(uIMU) < 80) uIMU = 80 * signYaw(zeroYaw, yaw);
  u = 0.85 * uIMU + 0.15 * uEnc;
  leftMotorValue = -u;
  rightMotorValue = u;
}

void setMotors(short int lmv, short int rmv) {
  lmv *= -1;
  rmv *= -1;
  if (lmv > 0) {
    digitalWrite(lPin2, HIGH);
    analogWrite(lPin, 255 - min(255, (short int)abs(lmv)));
  } else { 
    analogWrite(lPin2, 255 - min(255, (short int)abs(lmv)));
    digitalWrite(lPin, HIGH);
  }

  if (rmv > 0) {
    digitalWrite(rPin2, HIGH);
    analogWrite(rPin, 255 - min(255, (short int)abs(rmv)));
  } else {
    analogWrite(rPin2, 255 - min(255, (short int)abs(rmv)));
    digitalWrite(rPin, HIGH);
  }
}

void leftPlus() {
  left++;
}

void rightPlus() {
  right++;
}
