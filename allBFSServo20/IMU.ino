void IMUSetup() {
  int t0 = millis(), t;
  int n;

  int rFirst;
  do {
    getVLX();
    t = millis();

    if (Serial1.available() >= 4) {
      if (Serial1.read() == 255) {
        yFirst = map(Serial1.read(), 0, 254, 0, 360);
        Serial1.read();
        Serial1.read();
      }

      Serial.println(String(yFirst) + "   " + String(pFirst));
    }

    centralOld = centralVLX;
    backwardOld = backwardVLX;
  } while (t - t0 < IMUCalibration);
}

void getAngle() {
  //Serial.print("true ");
  int n, getR;
  if (Serial1.available() >= 4) {
    if (Serial1.read() == 255) {
      getY = map(Serial1.read(), 0, 254, 0, 360);
      getP = map(Serial1.read(), 0, 254, 0, 360);
      getR = map(Serial1.read(), 0, 254, 0, 360);
      //Serial.println(getP);
      yawFunc(getY);
      pitch = adduction(getP);
      roll = adduction(getR);
      //Serial << endl << "P/R " << pitch << " " << roll << endl;
    }
  }
}

void yawFunc(float now) {
  if (yOld > 350 && now < 10) k++;
  else if (!firstY && now > 350 && yOld < 10) k--;

  yaw = 360 * (float)k + now - yFirst;

  if (yaw > 360) k--;
  else if (yaw < 0) k++;
  yaw = 360 * (float)k + getY - yFirst;
  yaw = 360 - yaw;

  yOld = now;
  firstY = false;
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

float higherYaw(float y) {
  float mini = min(min(differenceYaw(y, 0), differenceYaw(y, 90)), min(differenceYaw(y, 180), differenceYaw(y, 270)));
  if (mini == differenceYaw(y, 0)) return 0;
  else if (mini == differenceYaw(y, 90)) return 90;
  else if (mini == differenceYaw(y, 180)) return 180;
  else return 270;
}
