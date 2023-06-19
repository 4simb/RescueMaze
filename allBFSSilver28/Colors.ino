int countBlue = 0, countBlack = 0, countSilver = 0;
int redFrequency, red;
int greenFrequency, green;
int blueFrequency, blue;
void readRGB() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  // Reading the output frequency
  redFrequency = pulseIn(sensorOut, LOW);
  red = map(redFrequency, minRed, maxRed, 255, 0);

  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);

  // Reading the output frequency
  greenFrequency = pulseIn(sensorOut, LOW);
  green = map(greenFrequency, minGreen, maxGreen, 255, 0); // redFrequency

  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  blue = map(blueFrequency, minBlue, maxBlue, 255, 0);
  
  Vec3b colorNow(red, green, blue);
  int clr = colorNow.getColor();
  
  Serial << red << " " << green << " " << blue << " ";
  Serial << "CLR:" << clr << " ";
  
  Serial << colorNow.cosBetweenColors(Vec3b(-12000, -12000, -15000)) << " " << colorNow.cosBetweenColors(Vec3b(-3500, -2250, -1750)) << " ";

  if (clr != 2 && countBlue <= 150) countBlue++;
  else countBlue = 0;

  if (countBlue >= 150) ignoreBlue = false;
  
  if (state == 4 && clr == 2 && !ignoreBlue) {
    //afterBlue = true;
    state = 7;
  } 

  if (clr == 3) countBlack++;
  else countBlack = 0;
  
  if (state == 2 && countBlack > 3) {
    state = 8;
    l0 = left;
    r0 = right;
    countBlack = 0;
  }

  if (clr == 4) countSilver++;
  else countSilver = 0;

  if (clr == 4 && state == 4 && countSilver > 5) {
    indexCheckpoint = smezh.size() - 1;
    dirCheckpoint = robotDirection;
    countSilver = 0;
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
  if  (abs(left - l0) / 2 + abs(right - r0) / 2 < 500) {
    leftMotorValue = -70;
    rightMotorValue = -70;
  } else {
    leftMotorValue = 0;
    rightMotorValue = 0;
    action.clear();
    
    coordFuture(xRobot, yRobot, robotDirection);
    //Serial << NNPair.first << " " << NNPair.second;
    
    deleteCell(NNPair.first, NNPair.second);
    bfs();
    state = 4;
  }
}
