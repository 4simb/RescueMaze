bool byBack, byForw, byEnc;
bool fromForward = false;
void caseForward() {
  if (firstCase2Cycle) {
    //initialization
    byBack = false;
    byForw = false;
    byEnc = false;

    if (!isMVImpact && stateOld != 2) {
      centralOld = centralVLX;
      backwardOld = backwardVLX;
      l0 = left;
      r0 = right;
    } else {
      isMVImpact = false;
      stateOld = -1;
    }

    if (backwardOld < offerBackward[offerSize - 1] && valueBackward(backwardOld) != 0) byBack = true;
    else if (centralOld < offerForward[offerSize - 1] && valueForward(centralOld) != 0) byForw = true;
    else byEnc = true;
  }

  Serial.print(String(byBack) + String(byForw) + String(byEnc));
  firstCase2Cycle = false;
  fromForward = false;
  if (byBack && backwardVLX < valueBackward(backwardOld) && centralVLX >= 41 && backwardVLX < 8000) {
    VLXandIMU(velPitch, setting);

    Serial.print(" BACK");
  } else if (byForw && centralVLX > valueForward(centralOld) && centralVLX >= 41 && centralVLX < 8000) {
    VLXandIMU(velPitch, setting);
    Serial.print(" FORW");
  } else if (byEnc && ((left - l0) / 2 + (right - r0) / 2) + rememberEnc < 4450) {
    VLXandIMU(velPitch, setting);

    Serial.print(" ENC");
  } else fromForward = true;


  if ((pitch > 25 && pitch < 100) || (pitch < 335 && pitch > 300)) {
    isGor = true;
    velPitch = 90;
  } else {
    isGor = false;
    velPitch = 135;
  }

  if (color == 3) {
    state = 8;
    l0 = left;
    r0 = right;
  }

  if (fromForward) {
    rememberEnc = 0;
    state = 4;
    timer = millis();
    ignoreBlue = false;
    countFor = 0;
    blinkOut = false;
    firstCase2Cycle = true;

    isMVLeft = false;
    isMVRight = false;
  }
}

void question() {
  if (centralVLX != -1 && centralVLX <= 150 && !alWas) {
    state = 5;
  } else {
    alWas = false;
    if (leftVLX >= 300 && !ignore_left) {
      state = 0;
      zeroYaw = higherYaw(normalize(yaw + 90)); //Left
    } else if (centralVLX != -1 && centralVLX <= 200) {
      state = 1;
      zeroYaw = higherYaw(normalize(yaw - 90)); //Right
    } else {
      state = 2;
      setting = higherYaw(yaw);
    }

    //if (!ignoreWordsLeft) rememberEnc = 0;
    isGorOld = false;
  }

  if (color == 1 && !ignoreBlue) {
    state = 7;
    timer = millis();
  }

  ignore_left = false;
  if (state != 2 && state != 4) isMVImpact = false;
}

void alignment() {
  if (firstAlignment) {
    firstAlignment = false;
    timerAlignment = millis();
  } else if (!secondAlignment) {
    if (millis() - timerAlignment < 600) {
      leftMotorValue = 55;
      rightMotorValue = 55;
    } else secondAlignment = true;
  } else {
    if (centralVLX < 0) { //40
      leftMotorValue = -80;
      rightMotorValue = -80;
    } else {
      state = 4;
      secondAlignment = false;
      firstAlignment = true;
      alWas = true;
    }
  }
}
