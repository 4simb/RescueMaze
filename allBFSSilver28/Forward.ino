bool goSlideOld = false;
bool byBack, byForw, byEnc, byBoth;
bool fromForward = false;

int pitchCount = 0, backCount = 0, forwCount = 0;
bool firstBackRave, firstForwRave;

void caseForward() {
  if (firstCase2Cycle) {
    //initialization
    byBack = false;
    byForw = false;
    byEnc = false;

    if (!isMVImpact) {
      Serial << "NO ";
      centralOld = centralVLX;
      backwardOld = backwardVLX;
      l0 = left;
      r0 = right;
      rememberEnc = 0;
    } else {
      Serial << "YES ";
    }

    //isMVImpact = false;
    //stateOld = -1;
    int slideDetect = checkSlide();

    Serial << "SLIDE_DETECT: " << slideDetect << endl;
    firstBackRave = backRave;
    firstForwRave = forwRave;
    if (backwardOld < 8000 && backwardOld < offerBackward[offerSize - 1]
        && valueBackward(backwardOld) != 0 && !firstBackRave && slideDetect != 1) byBack = true;
    else if (centralOld < 8000 && centralOld < offerForward[offerSize - 1]
             && valueForward(centralOld) != 0 && !firstForwRave && slideDetect != 2) byForw = true;
    else byEnc = true;

    pitchCount = 0;
    backCount = 0;
    forwCount = 0;

    fEditor = pair(0, 0);
  }

  if ((byBack && backwardVLX >= backwardOld + abs(valueBackward(backwardOld) - backwardOld) / 2)
      //|| (byForw && centralVLX <= centralOld + abs(valueBackward(centralOld) - centralOld) / 2)
      || (byForw && centralOld - centralVLX >= abs(valueBackward(centralOld) - centralOld) / 2)
      || (byEnc && (left - l0) / 2 + (right - r0) / 2 > 1000)) {
    Serial << "CHANGE";
    switch (robotDirection) {
      case 0: //->
        fEditor = pair(1, 0);
        break;
      case 1: //^
        fEditor = pair(0, -1);
        break;
      case 2: //<-
        fEditor = pair(-1, 0);
        break;
      case 3: //down
        fEditor = pair(0, 1);
        break;
    }
  }

  /*if (pitch >= pitchThresholds.first && pitch < 110) pitchCount += 1 + pitch - pitchThresholds.first;
    else if (pitch <= pitchThresholds.second && pitch > 180) pitchCount += 1 + pitchThresholds.second - pitch;
    else pitchCount = 0;*/
  if (abs(pitch) < 154) ++pitchCount;
  else pitchCount = 0;

  /*if (backwardOld < 600 && !firstBackRave && backwardVLX > 1050) backCount++;
    else backCount = 0;

    if (centralOld < 400 && !firstForwRave && centralVLX > 1050) forwCount++;
    else forwCount = 0;*/

  if (pitchCount > 20) {
    if (!goSlide) {
      if (pitch < 0) {
        addCell(true, 1);
        if (floors == 0) floors = 128;
        else floors = 0;
      }
      else {
        addCell(true, 2);
        if (floors == 0) floors = 128;
        else floors = 0;
      }
    }

    isGor = true;
    velPitch = 75;
    goSlide = true;
    Serial.print("      GO_SLIDE");
    fromForward = false;
  } else {
    isGor = false;
    velPitch = 135;
    Serial.print("      GO_MIDDLE");
    if (abs(pitch) >= 166) goSlide = false;
  }

  Serial.print(String(byBack) + String(byForw) + String(byEnc));
  firstCase2Cycle = false;
  fromForward = false;

  if (!digitalRead(LBUTTON_UP) && !digitalRead(RBUTTON_UP)) fromForward = true;
  else if ((byBack && (backwardVLX < valueBackward(backwardOld)
                       || (left - l0) / 2 + (right - r0) / 2 + rememberEnc < 1250)) && centralVLX >= 62) {
    VLXandIMU(velPitch, setting);

    Serial.print(" BACK");
  } else if ((byForw && (centralVLX > valueForward(centralOld)
                         || (left - l0) / 2 + (right - r0) / 2 + rememberEnc < 1250)) && centralVLX >= 62) {
    VLXandIMU(velPitch, setting);
    Serial.print(" FORW ");
    Serial << valueForward(centralOld) << " ";
  } else if (byEnc && ((left - l0) / 2 + (right - r0) / 2) + rememberEnc < 2320 && centralVLX >= 62) {
    VLXandIMU(velPitch, setting);

    Serial.print(" ENC");
  } else if (goSlide || abs(pitch) <= 164) { //158
    VLXandIMU(velPitch, setting);
    fromForward = false;

  } else fromForward = true;

  /*if (!digitalRead(LBUTTON_UP) && digitalRead(RBUTTON_UP) || digitalRead(LBUTTON_UP) && !digitalRead(RBUTTON_UP)
      || !digitalRead(LBUTTON_LEFT) || !digitalRead(RBUTTON_RIGHT)) {
  }*/
  if (!digitalRead(LBUTTON_LEFT)) {
    leftMotorValue *= 2.5;
    rightMotorValue *= 0.4;
  } else if (!digitalRead(RBUTTON_RIGHT)) {
    leftMotorValue *= 0.4;
    rightMotorValue *= 2.5;
  }

  Serial << " PC:" << pitchCount << " // " << backCount << " " << forwCount;

  if (goSlideOld && !goSlide) {
    state = 9;
    fromForward = true;
  }

  if (colorBase == 3) {
    state = 8;
    l0 = left;
    r0 = right;
  }

  goSlideOld = goSlide;
  if (fromForward) {
    rememberEnc = 0;
    fEditor = pair(0, 0);

    if (state != 9) {
      state = 4;
      Serial << "END_F" << endl;
      action.pop();
      addCell(true, floors);
    }

    if (afterBlue) {
      state = 7;
      afterBlue = false;
    }
    timer = millis();
    ignoreBlue = false;
    countFor = 0;
    blinkOut = false;
    firstCase2Cycle = true;
    isMVLeft = false;
    isMVRight = false;

    isMVImpact = false;
    stateOld = -1;
    fEditor = pair(0, 0);
  }
}

bool someForwFirst = true;
void someForw() {
  if (someForwFirst) {
    l0 = left;
    r0 = right;
    someForwFirst = false;
  }

  VLXandIMU(velPitch, setting);

  if ((left - l0) / 2 + (right - r0) / 2 > 660) { //850
    state = 4;
    timer = millis();
    someForwFirst = true;
    addCell(true, floors);
    fEditor = pair(0, 0);
    action.clear();

    isMVImpact = false;
    stateOld = -1;
  }
}
