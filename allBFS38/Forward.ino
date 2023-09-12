bool goSlideOld = false;
bool byBack, byForw, byEnc, byBoth;
bool exit_ = false;

int pitchCount = 0;
bool firstBackRave, firstForwRave;
int normalVel = 135;
int kMinus = 0;

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
    int8_t slideDetect = checkSlide();

    Serial << "SLIDE_DETECT: " << slideDetect << endl;
    firstBackRave = backRave;
    firstForwRave = forwRave;
    if (backwardOld < offerBackward[offerSize - 1]
        && valueBackward(backwardOld) != 0 && !firstBackRave && slideDetect != 1) byBack = true;
    else if (centralOld < offerForward[offerSize - 1]
             && valueForward(centralOld) != 0 && !firstForwRave && slideDetect != 2) byForw = true;
    else byEnc = true;
    //byEnc = true;

    pitchCount = 0;

    fEditor = pair(0, 0);
    firstCase2Cycle = false;
    kMinus = 0;
  }

  int enc = (left - l0) / 2 + (right - r0) / 2 + rememberEnc;
  
  changeCell(byBack, byForw, byEnc, backwardVLX, backwardOld, 
            centralVLX, centralOld, enc);

  if (abs(pitch) < 154) ++pitchCount;
  else pitchCount = 0;

  if (pitchCount > 20) {
    int encP = enc + rememberEnc - kMinus * angleEnc * 1.5f;
    if (encP > angleEnc * 1.5f) { //!goSlide
      kMinus++;
      if (pitch < 0) {
        addCell(true, CLIMB);
        Serial.println("####################_CLIMB_####################");
        if (floors == FIRST_FLOOR) floors = SECOND_FLOOR;
        else if (floors == SECOND_FLOOR) floors = FIRST_FLOOR;
      } else {
        addCell(true, DESCENT);
        Serial.println("####################_DESCENT_####################");
        if (floors == FIRST_FLOOR) floors = SECOND_FLOOR;
        else if (floors == SECOND_FLOOR) floors = FIRST_FLOOR;
      }
    }

    if (pitch < 0) velPitch = (float)normalVel * 1.6;
    else velPitch = (float)normalVel * 0.55;

    goSlide = true;
    exit_ = false;
    
    Serial.print("      GO_SLIDE");
  } else {
    velPitch = normalVel;
    if (abs(pitch) >= 166) goSlide = false;
    
    Serial.print("      GO_USUAL");
    kMinus = 0;
  }

  Serial.print(String(byBack) + String(byForw) + String(byEnc));
  exit_ = false;

  if (!digitalRead(LBUTTON_UP) && !digitalRead(RBUTTON_UP)) exit_ = true;
  else if (!digitalRead(LBUTTON_LEFT)) {
    leftMotorValue *= 2.5;
    rightMotorValue *= 0.4;
  } else if (!digitalRead(RBUTTON_RIGHT)) {
    leftMotorValue *= 0.4;
    rightMotorValue *= 2.5;
  }
  
  else if (byBack && vlxOKBack(backwardVLX, backwardOld, enc, centralVLX)) {
    VLXandIMU(velPitch, setting);

    Serial.print(" BACK");
  } else if (byForw && vlxOKForw(centralVLX, centralOld, enc)) {
    VLXandIMU(velPitch, setting);
    
    Serial.print(" FORW ");
  } else if (byEnc && enc + rememberEnc < angleEnc && centralVLX >= 65) {
    VLXandIMU(velPitch, setting);

    Serial.print(" ENC");
  } else if (goSlide || abs(pitch) <= 164) { //158
    VLXandIMU(velPitch, setting);
    exit_ = false;
  } else exit_ = true;

  if (goSlideOld && !goSlide) {
    state = 9;
    exit_ = true;
  }

  if (colorBase == BLACK_COLOR) {
    state = 8;
    l0 = left;
    r0 = right;
  }

  goSlideOld = goSlide;
  
  if (exit_) {
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
    //fEditor = pair(0, 0);
  }
}

bool afterSlideFirst = true;
void afterSlide() {
  if (afterSlideFirst) {
    l0 = left;
    r0 = right;
    afterSlideFirst = false;
  }

  VLXandIMU(velPitch, setting);

  if ((left - l0) / 2 + (right - r0) / 2 > 650) { //850
    state = 4;
    timer = millis();
    afterSlideFirst = true;
    addCell(true, floors);
    fEditor = pair(0, 0);
    action.clear();

    isMVImpact = false;
    stateOld = -1;
  }
}
