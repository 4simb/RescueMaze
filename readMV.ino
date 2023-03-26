int countCan = 0;
void readMV() {  
  if (Serial2.available()) {
    openMVRead = Serial2.read();
    
    if (ignoreWords && canChangeMVLeft && openMVRead == '1') countCan++;
    else countCan = 0;
    if (countCan > 190) {
      ignoreWords = false;
      canChangeMVLeft = false;
      countCan = 0;
    }
    
    if (!ignoreWords && openMVRead == 'H') countH++;
    else countH = max(0, countH - 1);
    if (!ignoreWords && openMVRead == 'S') countS++;
    else countS = max(0, countS - 1);
    if (!ignoreWords && openMVRead == 'R') countRed++;
    else countRed = max(0, countRed - 1);
    if (!ignoreWords && openMVRead == 'Y') countYellow++;
    else countYellow = max(0, countYellow - 1);

    if (countH > 6 || countS > 6 || countRed > 6 || countYellow > 6) {
      state = 0;
      isMVLeft = true;
      ignoreWords = true;
      canChangeMVLeft = false;
      zeroYaw = higherYaw(normalize(yaw - 90));
      rememberEnc = (left - l0)/2 + (right - l0)/2;
      countH = 0;
      countS = 0;
      countRed = 0;
      countYellow = 0;
    }
  }
}
