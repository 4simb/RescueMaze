void leftPlus() {
  if (digitalRead(lEnc)) left++;
  else left--;
}

void rightPlus() {
  if (digitalRead(rEnc)) right++;
  else right--;
}


void totalStop() {
  digitalWrite(lEnc, LOW);
  digitalWrite(rEnc, LOW);
  analogWrite(lPin, 0);
  analogWrite(rPin, 0);
}

void turnLeftEnc() {
  int pomL = left;

  while (left - pomL < 1550) {
    digitalWrite(lEnc, HIGH);
    digitalWrite(rEnc, LOW);
    analogWrite(lPin, 100);
    analogWrite(rPin, 100);
  }

  totalStop();
  delay(500);
}

void turnRightEnc() {
  int pomR = right;
  while (right - pomR < 1550) {
    digitalWrite(lEnc, LOW);
    digitalWrite(rEnc, HIGH);
    analogWrite(lPin, 100);
    analogWrite(rPin, 100);
  }

  totalStop();
  delay(500);
}

void turnRightAcc() {
  getYawPitchRoll();
  byte pomY = yaw;
  byte yawOld = 0;
  bool first = false;
  while (abs(yaw - pomY) < 90) {
    getYawPitchRoll();
    //if (!first && yaw < 10 && yawOld > 350) yaw += 360;
    //else if (!first && yaw > 350 && yawOld < 10) 
    digitalWrite(lEnc, LOW);
    digitalWrite(rEnc, HIGH);
    analogWrite(lPin, 100);
    analogWrite(rPin, 100);
    yawOld = yaw;
    first = true;
  }

  totalStop();
  delay(500);
}

void forwardEnc() {
  int pomR = right;
  
  while (abs(right - pomR) < 1700) {
    digitalWrite(lEnc, LOW);
    digitalWrite(rEnc, LOW);
    analogWrite(lPin, 100);
    analogWrite(rPin, 100);
  }

  totalStop();
  delay(500);
}
