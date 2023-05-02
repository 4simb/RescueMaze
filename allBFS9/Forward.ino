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

    if (!isMVImpact && stateOld != 2) {
      centralOld = centralVLX;
      backwardOld = backwardVLX;
      l0 = left;
      r0 = right;
    } else {
      isMVImpact = false;
      stateOld = -1;
    }

    firstBackRave = backRave;
    firstForwRave = forwRave;
    if (backwardOld < 8000 && backwardOld < offerBackward[offerSize - 1]
        && valueBackward(backwardOld) != 0 && !firstBackRave) byBack = true;
    else if (centralOld < 8000 && centralOld < offerForward[offerSize - 1]
             && valueForward(centralOld) != 0 && !firstForwRave) byForw = true;
    else byEnc = true;

    pitchCount = 0;
    backCount = 0;
    forwCount = 0;
  }

  /*if (pitch >= pitchThresholds.first && pitch < 110) pitchCount += 1 + pitch - pitchThresholds.first;
    else if (pitch <= pitchThresholds.second && pitch > 180) pitchCount += 1 + pitchThresholds.second - pitch;
    else pitchCount = 0;*/
  if (!(pitch > pitchThresoldUp && pitch < pitchThresoldDown)) ++pitchCount;
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
    if (abs(pitch) < 8) goSlide = false;
  }

  Serial.print(String(byBack) + String(byForw) + String(byEnc));
  firstCase2Cycle = false;
  fromForward = false;
  if ((byBack && (backwardVLX < valueBackward(backwardOld)
                  || (left - l0) / 2 + (right - r0) / 2 + rememberEnc < 1850)) && centralVLX >= 41) {
    VLXandIMU(velPitch, setting);

    //Serial.print(" BACK");
  } else if ((byForw && (centralVLX > valueForward(centralOld)
                         || (left - l0) / 2 + (right - r0) / 2 + rememberEnc < 1850)) && centralVLX >= 41) {
    VLXandIMU(velPitch, setting);
    //Serial.print(" FORW");
  } else if (byEnc && ((left - l0) / 2 + (right - r0) / 2) + rememberEnc < 3050 && centralVLX >= 41) {
    VLXandIMU(velPitch, setting);

    //Serial.print(" ENC");
  } else if (goSlide || !(pitch > pitchThresoldUp && pitch < pitchThresoldDown)) {
    VLXandIMU(velPitch, setting);

    //Serial.print(" SLIDE");
  } else fromForward = true;

  Serial << " PC:" << pitchCount << " // " << backCount << " " << forwCount;

  if (goSlideOld && !goSlide) {
    state = 9;
    fromForward = true;
  }

  if (color == 3) {
    state = 8;
    l0 = left;
    r0 = right;
  }

  goSlideOld = goSlide;
  if (fromForward) {
    rememberEnc = 0;
    if (state != 9) {
      state = 4;
      Serial << "END_F" << endl;
      action.pop();
      addCell(true, floors);
    }
    
    timer = millis();
    ignoreBlue = false;
    countFor = 0;
    blinkOut = false;
    firstCase2Cycle = true;

    isMVLeft = false;
    isMVRight = false;
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

  if ((left - l0) / 2 + (right - r0) / 2 > 600) { //850
    state = 4;
    timer = millis();
    someForwFirst = true;
    addCell(true, floors);
    action.clear();
  }
}
