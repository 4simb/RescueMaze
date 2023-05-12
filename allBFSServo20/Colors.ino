int countBlue = 0;
void readRGB() {
  // w
  // r -1500
  // g -800
  // b -1000

  //blue
  // r -2200 -5000
  // g -1500 -3000
  // b -1000 -2500

  // black 
  // r -15000 -12000
  // g -15000 -12000
  // b -15000 -20000
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  // Reading the output frequency
  int redFrequency = pulseIn(sensorOut, LOW);
  int red = map(redFrequency, minRed, maxRed, 255, 0);

  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);

  // Reading the output frequency
  int greenFrequency = pulseIn(sensorOut, LOW);
  int green = map(greenFrequency, minGreen, maxGreen, 255, 0); // redFrequency

  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  // Reading the output frequency
  int blueFrequency = pulseIn(sensorOut, LOW);
  int blue = map(blueFrequency, minBlue, maxBlue, 255, 0);
  
  Vec3b colorNow(red, green, blue);
  int clr = colorNow.getColor();

  Serial << red << " " << green << " " << blue << " ";
  Serial << "CLR:" << clr << " ";
  
  Serial << colorNow.cosBetweenColors(Vec3b(-12000, -12000, -15000)) << " " << colorNow.cosBetweenColors(Vec3b(-3500, -2250, -1750)) << " ";
  
  if (clr != 2 && countBlue <= 49) countBlue++;
  else countBlue = 0;

  if (countBlue >= 50) ignoreBlue = false;

  if (clr == 2 && !ignoreBlue) {
    state = 7;
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
  if  ((left - l0 + right - r0) / 2 < 900) {
    leftMotorValue = -70;
    rightMotorValue = -70;
  } else {
    action.clear();
    
    coordFuture(xRobot, yRobot, robotDirection);
    deleteCell(NNPair.first, NNPair.second);
    bfs();
  }
}
