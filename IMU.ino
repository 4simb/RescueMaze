void getAngle() {
  //Serial.print("true ");
  if (Serial1.available()) {
    //Serial.print("true ");
    n = map((float)Serial1.read(), 0, 255, 0, 360);

    if (isYaw) {
      getY = n;
      yawFunc(getY);
      //Serial.print("GetY: " + String(getY) + " ");
    }
    else {
      getP = n;
      pitchFunc(getP);
      //Serial.print("GetP: " + String(getP) + " ");
    }

    isYaw = !isYaw;
  }
}

void yawFunc(float now) {
  if (yOld > 350 && now < 10) k++;
  else if (!firstY && now > 350 && yOld < 10) k--;

  yaw = 360 * (float)k + now - y0;

  if (yaw > 360) k--;
  else if (yaw < 0) k++;
  yaw = 360 * (float)k + getY - y0;
  yaw = 360 - yaw;

  yOld = now;
  firstY = false;
}

void pitchFunc(float now) {
  if (pOld > 350 && now < 10) kPitch++;
  else if (!firstP && now > 350 && pOld < 10) kPitch--;
  pitch = 360 * (float)kPitch + now - p0;

  if (pitch > 360) kPitch--;
  else if (pitch < 0) kPitch++;
  pitch = 360 * (float)kPitch + now - p0;

  pOld = now;
  firstP = false;
}

int normalize(int y) {
  if (y < 0) y += 360;
  else if (y > 360) y -= 360;
  return y;
}

short int signYaw(double y1, double y2) {
  if (y1 - y2 == 0) return 0;
  else if (abs(y1 - y2) < 180) {
    if (y2 > y1) return -1;
    else return 1;
  } else {
    if (y2 > y1) return 1;
    else return -1;
  }
}

double differenceYaw(double y1, double y2) {
  if (abs(y1 - y2) <= 180) return abs(y1 - y2);
  else if (y2 > 180 && y1 < 180) {
    return y1 + 360 - y2;
  } else {
    return y2 + 360 - y1;
  }
}

double higherYaw(double y) {
  float mini = min(min(differenceYaw(y, 0), differenceYaw(y, 90)), min(differenceYaw(y, 180), differenceYaw(y, 270)));
  if (mini == differenceYaw(y, 0)) return 0;
  else if (mini == differenceYaw(y, 90)) return 90;
  else if (mini == differenceYaw(y, 180)) return 180;
  else return 270;
}
