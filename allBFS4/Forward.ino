bool goSlide = false;
bool goSlideOld = false;
bool byBack, byForw, byEnc, byBoth;
bool fromForward = false;
pair pitchThresholds = pair(7, 348);

int pitchCount = 0;
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

    if (backwardOld < 8000 && backwardOld < offerBackward[offerSize - 1] 
        && valueBackward(backwardOld) != 0 && !backRave) byBack = true;
    else if (centralOld < 8000 && centralOld < offerForward[offerSize - 1] 
        && valueForward(centralOld) != 0 && !forwRave) byForw = true;
    else byEnc = true;
  
    pitchCount = 0;
  }

  /*if (pitch >= pitchThresholds.first && pitch < 110) pitchCount += 1 + pitch - pitchThresholds.first;
  else if (pitch <= pitchThresholds.second && pitch > 180) pitchCount += 1 + pitchThresholds.second - pitch; 
  else pitchCount = 0;*/
  if (abs(pitch) >= 11) ++pitchCount;
  else pitchCount = 0;

  if (pitchCount > 17) {
    isGor = true;
    velPitch = 80;
    goSlide = true;
    Serial.print("      GO_SLIDE");
  } else {
    isGor = false;
    velPitch = 135;
    Serial.print("      GO_MIDDLE");
    goSlide = false;
  }

  Serial.print(String(byBack) + String(byForw) + String(byEnc));
  firstCase2Cycle = false;
  fromForward = false;
  if (byBack && (backwardVLX < valueBackward(backwardOld) && backwardVLX < 8000
      || (left - l0) / 2 + (right - r0) / 2 + rememberEnc < 1450) && centralVLX >= 41) {
    VLXandIMU(velPitch, setting);

    Serial.print(" BACK");
  } else if (byForw && (centralVLX > valueForward(centralOld)
      || (left - l0) / 2 + (right - r0) / 2 + rememberEnc < 1450) && centralVLX >= 41 && centralVLX < 8000) {
    VLXandIMU(velPitch, setting);
    Serial.print(" FORW");
  } else if (byEnc && ((left - l0) / 2 + (right - r0) / 2) + rememberEnc < 3050 && centralVLX >= 41) {
    VLXandIMU(velPitch, setting);

    Serial.print(" ENC");
  } else if (goSlide) {
    VLXandIMU(velPitch, setting);

    Serial.print(" SLIDE");
  } else fromForward = true;

  Serial << pitchCount;

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
    if (state != 9) state = 4;

    Serial << "END_F" << endl;
    action.pop();
    timer = millis();
    ignoreBlue = false;
    countFor = 0;
    blinkOut = false;
    firstCase2Cycle = true;

    isMVLeft = false;
    isMVRight = false;
    addCell(true);
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

  if ((left - l0) / 2 + (right - r0) / 2 > 750) { //850
    state = 4;
    timer = millis();
    someForwFirst = true;
  }
}
