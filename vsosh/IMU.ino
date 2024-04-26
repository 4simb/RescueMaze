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
        pFirst = map(Serial1.read(), 0, 254, 0, 360);
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
  byte crc;
  if (Serial1.available() >= 4) {
    if (Serial1.read() == 255) {
      getY = Serial1.read();
      getP = Serial1.read();
      crc = Serial1.read();
      //Serial << "CRC" << endl;
      if (crc == crc8(getY, getP)) {
        getY = map(getY, 0, 254, 0, 360);
        getP = map(getP, 0, 254, 0, 360);
        
        yawFunc(getY);
        pitch = adduction(getP);
      }  
    }
  }
}

byte crc8(int y, int p) {
  int data[2] = {y, p};
  int crc = 0xFF;
  for (byte i = 0; i < 2; ++i) {
    crc = crc ^ data[i];
    for (byte j = 0; j < 8; ++j) {
      if (crc & 0x80) crc = (crc << 1) ^ 0x31;
      else crc = crc << 1;
    }
  }

  return crc;
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
