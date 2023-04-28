void blueFun() {
  leftMotorValue = 0;
  rightMotorValue = 0;
  if (millis() - timer > 6000) {
    state = 3;
    ignoreBlue = true;
  }
}

void blackFun() {
  if  ((left - l0 + right - r0) / 2 < 900) {
    leftMotorValue = -70;
    rightMotorValue = -70;
  } else {
    if (rightVLX > 140) {
      state = 1;
      zeroYaw = higherYaw(normalize(yaw - 90));
    } else {
      state = 0;
      zeroYaw = higherYaw(normalize(yaw + 90));
    }

    ignore_left = true;
  }
}
