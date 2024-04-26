int t = -1;
bool isFirstTimTurn = false;
int timTurn = 0;

#define USUAL_TURN 0
#define FAST_TURN 1

void AccForward(short int vv, float yy) {
  u = 13 * differenceYaw(yy, yaw) * (float)signYaw(yaw, yy);
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
  uIMU = -8 * differenceYaw(yy, yaw) * (float)signYaw(yaw, yy);
   
  //if (abs(differenceYaw(yy, yaw)) > 30) uIMU *= 2;

  if (abs(rightVLX - leftVLX) < 40 && leftVLX < 175 && rightVLX < 175) {
    uVLX = -12 * (float)(rightVLX - leftVLX); //-4.3
    remLeftVLX = leftVLX;
    remRightVLX = rightVLX;
    //Serial.print("    ");
    //Serial.print("VLX");
  } else if (rightVLX > leftVLX && leftVLX < 175) { //145
    uVLX = -4.1 * (float)(115 - leftVLX); //-3
    remLeftVLX = leftVLX;
  } else if (leftVLX > rightVLX && rightVLX < 175) { //145
    uVLX = 4.1 * (float)(115 - rightVLX); //3
    remRightVLX = rightVLX;
  } else uVLX = 0;

  uVLX *= 0.92;
  if (floors == CLIMB || floors == DESCENT) uVLX *= 0.5;
  /*if (uVLX == 0) {
    if (remLeftVLX != -1 && remRightVLX != -1) uVLX = -4.3 * (float)(remRightVLX - remLeftVLX);
    else if (remLeftVLX != -1) uVLX = -3 * (float)(115 - remLeftVLX);
    else if (remRightVLX != -1) uVLX = 3 * (float)(115 - remRightVLX);
  }*/

  uEnc = -((left - l0) - (right - r0)) * 3.5;  
  if (uVLX != 0) u = uVLX * 0.5 + uIMU * 0.35 + uEnc * 0.15; //0.6 0.4
  else u = uIMU * 0.7 + uEnc * 0.3; //0

  leftMotorValue = vv - u;
  rightMotorValue = vv + u;
}

void Turns(bool status) { //MAIN
  bool micric = checkMicroswitchs();
  err = differenceYaw(zeroYaw, yaw) * signYaw(zeroYaw, yaw);

  if (!micric) {
    p = err * 3.4;//4.1
    d = (err - errOld) * 2.3;
    u = p + d;
    if (abs(u) < 80) u = 80 * sign(u);
    
    if (status == FAST_TURN) u *= 2; 

    leftMotorValue = -u;
    rightMotorValue = u;

    //centralOld = centralVLX;
    //backwardOld = backwardVLX;
  } else timTurn = millis();

  errOld = err; 
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
  if (!isFirstTimTurn) timTurn = millis();
  isFirstTimTurn = true;

  Turns(USUAL_TURN);
  //if (millis() - timTurn < 4000) Turns(USUAL_TURN);
  //else Turns(FAST_TURN);

  //leftMotorValue *= 1.15;
  if (differenceYaw(zeroYaw, yaw) <= 1) {
    Serial.println("SU");
    action.pop();
    state = 4;
    setting = yaw;
    l0 = left;
    r0 = right;
    remLeftVLX = -1;
    remRightVLX = -1;

    robotDirection++;
    if (robotDirection > 3) robotDirection = 0;
  
    blinkOut = false;
    isMVLeft = false;
    isMVRight = false;

    timer = millis();
    isFirstTimTurn = false;
  }
}

void rightTurnSwitch() {
  //if (!isFirstTimTurn) timTurn = millis();
  //isFirstTimTurn = true;

  Turns(USUAL_TURN);
  //if (millis() - timTurn < 4000) Turns(USUAL_TURN);
  //else Turns(FAST_TURN);

  Serial.print("   ");
  Serial.print(zeroYaw);
  if (differenceYaw(zeroYaw, yaw) <= 1) { //1
    //if (!isMVRight && !ignoreWords) state = 4;
    //else if (!isMVRight) state = 3;
    action.pop();
    state = 4;
    setting = yaw;
    l0 = left;
    r0 = right;

    timer = millis();
    isMVLeftTurn = false;
    remLeftVLX = -1;
    remRightVLX = -1;
    //isMVLeftTurn = false;

    if (robotDirection == 0) robotDirection = 3;
    else robotDirection--;

    blinkOut = false;
    isMVLeft = false;
    isMVRight = false;
    //isFirstTimTurn = false;
  }
}

bool checkMicroswitchs() {
  if (!digitalRead(LBUTTON_UP) || !digitalRead(LBUTTON_LEFT) || !digitalRead(RBUTTON_UP) || !digitalRead(RBUTTON_RIGHT)) {
    leftMotorValue = -80; //-70
    rightMotorValue = -80; //-70
    //t = millis();
    return true;
  }

  if (t != -1 && millis() - t < 1) {
    leftMotorValue = -80;
    rightMotorValue = -80;
    return true;
  } else {
    t = -1;
    return false;
  }

  return false;
}
