int thr = 12;
void readRGB() {
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  // Reading the output frequency
  int redFrequency = pulseIn(sensorOut, LOW);
  int red = map(redFrequency, minRed, maxRed, 255, 0);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  int greenFrequency = pulseIn(sensorOut, LOW);
  int green = map(redFrequency, minGreen, maxGreen, 255, 0);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  int blueFrequency = pulseIn(sensorOut, LOW);
  int blue = map(blueFrequency, minBlue, maxBlue, 255, 0);
  Vec3b colorNow(red, green, blue);

  if (colorNow.isThisColor(whiteCell)) {
    Serial.print(" WHITE");
    color = 0;
  }
  else if (red > silverCell.r && green > silverCell.g && blue > silverCell.b) {
    Serial.print(" SILVER");
    color = 2;
  }
  else if (colorNow.isThisColor(blackCell)) {
    Serial.print(" BLACK");
    color = 3;
  } 
  else if (colorNow.isThisColor(blueCell)) {
    Serial.print(" BLUE");
    color = 1;
  }
}

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
