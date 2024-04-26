void vlx_setup() {
  pinMode(XSHUT_pinB, OUTPUT);
  pinMode(XSHUT_pinR, OUTPUT);
  pinMode(XSHUT_pinL, OUTPUT);
  pinMode(XSHUT_pinF, OUTPUT);
  
  digitalWrite(XSHUT_pinB, LOW);
  digitalWrite(XSHUT_pinR, LOW);
  digitalWrite(XSHUT_pinL, LOW);
  digitalWrite(XSHUT_pinF, LOW);
  delay(10);

  digitalWrite(XSHUT_pinB, HIGH);
  delay(100);
  vlxB.setAddress(SensorB_newAddress);
  Serial.println(vlxB.getAddress());
  vlxB.init();
  
  digitalWrite(XSHUT_pinL, HIGH);
  delay(100);
  vlxL.setAddress(SensorL_newAddress);
  Serial.println(vlxL.getAddress());
  vlxL.init();

  digitalWrite(XSHUT_pinR, HIGH);
  delay(100);
  vlxR.setAddress(SensorR_newAddress);
  Serial.println(vlxR.getAddress());
  vlxR.init();

  digitalWrite(XSHUT_pinF, HIGH);
  delay(100);
  vlxF.setAddress(SensorF_newAddress);
  Serial.println(vlxF.getAddress());
  vlxF.init();

  Serial.println("Hello! It's me");
  Serial.println("Init end");
  delay(2500);
  vlxB.setTimeout(50);
  vlxR.setTimeout(50);
  vlxL.setTimeout(50);
  vlxF.setTimeout(50);

  vlxB.startContinuous();
  vlxR.startContinuous();
  vlxL.startContinuous();
  vlxF.startContinuous();
  Serial.println("Setup end");
  tMVLeftOld = 0;
  tMVRightOld = 0;
}

void getVLX() {
  //Continuous
  backwardVLX = vlxB.readRangeContinuousMillimeters();
  rightVLX = (float)vlxR.readRangeContinuousMillimeters() / 1.2;
  leftVLX = vlxL.readRangeContinuousMillimeters();
  centralVLX = vlxF.readRangeContinuousMillimeters();

  if (leftVLX > 215) tMVLeftOld = millis(); //160
  if (rightVLX > 215) tMVRightOld = millis(); //160
  
  //1100
  if (millis() - tMVLeftOld >= 1200) lNormal = true;
  else lNormal = false;

  if (millis() - tMVRightOld >= 1200) rNormal = true;
  else rNormal = false;
}

int valueForward(int centr) {
  for (offerI = offerSize - 2; offerI >= 0; --offerI) {
    if (centr > offerForward[offerI] && centr - offerForward[offerI] > 105) { //105
      return offerForward[offerI];
    }
  }

  return 0;
}

int valueBackward(int centr) {
  for (offerI = 0; offerI < offerSize - 1; ++offerI) {
    if (centr < offerBackward[offerI] && offerBackward[offerI] - centr > 90) { //105
      return offerBackward[offerI];
    }
  }

  return 0;
}

void setRave() {
  if (isVLXBad(backwardVLX)) countBack++;
  if (isVLXBad(centralVLX)) countForw++;
  
  queBack.push(backwardVLX);
  queForw.push(centralVLX);

  //if (queBack.count() > raveHistLength2) {
  //  if (isVLXBad(queBack.peek())) countBackCell = max(0, countBack - 1);
  //}

  if (queBack.count() > raveHistLength) {
    if (isVLXBad(queBack.peek())) countBack = max(0, countBack - 1);
    queBack.pop();
  }
  
  if (queForw.count() > raveHistLength) {
    if (isVLXBad(queForw.peek())) countForw = max(0, countForw - 1);
    queForw.pop();
  }

  backRave = countBack > 0;
  forwRave = countForw > 0; 
}

bool raveBackPercent(float percent) {
  return countBack > (float)raveHistLength * (float)percent / 100;
}

bool raveForwardPercent(float percent) {
  return countForw > (float)raveHistLength * (float)percent / 100;
}

bool isVLXBad(int vlx) {
  return vlx > 900 || (floors == SECOND_FLOOR && vlx < 10); //6
}

bool isVLXGreat(int vlx) {
  return vlx > 900;
}

bool isWallCB(int vlx) {
  return vlx > 190;
}

bool isWallLR(int vlx) {
  return vlx > 230; //190
}

bool changeCell(int vlx, int vlxOld, bool isBack) {
   if (isBack) return abs(vlx - vlxOld) >= abs(valueBackward(vlxOld) - vlx) / 2;
   else return abs(vlx - vlxOld) >= abs(valueForward(vlxOld) - vlx) / 2;
}

bool vlxOKBack(int bvlx, int bvlxOld, int enc, int fvlx) {
  return (bvlx < valueBackward(bvlxOld) || (float) enc < (float)angleEnc * 0.5) && fvlx >= 55;
}

bool vlxOKForw(int fvlx, int fvlxOld, int enc) {
  return (fvlx > valueForward(fvlxOld) || (float) enc < (float)angleEnc * 0.5) && fvlx >= 55; //
}