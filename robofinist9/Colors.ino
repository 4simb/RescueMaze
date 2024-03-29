int countBlue = 0, countBlack = 0, countSilver = 0;
int redFrequency, red;
int greenFrequency, green;
int blueFrequency, blue;
bool firstBlack = false;
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
  green = map(greenFrequency, minGreen, maxGreen, 255, 0);  // redFrequency

  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  blue = map(blueFrequency, minBlue, maxBlue, 255, 0);

  Vec3b colorNow(red, green, blue);
  int clr = colorNow.getColor();

  //Serial << red << " " << green << " " << blue << " ";
  //Serial << "CLR:" << clr << " ";

  //Serial << colorNow.cosBetweenColors(Vec3b(-12000, -12000, -15000)) << " " << colorNow.cosBetweenColors(Vec3b(-3500, -2250, -1750)) << " ";

  if (clr != BLUE_COLOR && countBlue <= 150) countBlue++;
  else countBlue = 0;

  if (countBlue >= 150) ignoreBlue = false;

  if (state == 4 && clr == BLUE_COLOR && !ignoreBlue) {
    //afterBlue = true;
    state = 7;
  }

  if (clr == BLACK_COLOR) countBlack++;
  else countBlack = 0;

  if (state == 2 && countBlack > 1) {  //3
    state = 8;
    l0 = left;
    r0 = right;
    countBlack = 0;
  }

  if (clr == SILVER_COLOR) countSilver++;
  else countSilver = 0;

  if (countSilver > 5) {
    if (!tumblerRead && state == 3 && !maze[maze.size() - 1][0].absEqual(maze[indexCheckpoint][0])) {
      indexCheckpoint = maze.size() - 1;
      dirCheckpoint = robotDirection;
    }

    countSilver = 0;
  }
}

void blueFun() {
  leftMotorValue = 0;
  rightMotorValue = 0;
  if (millis() - timer > 5000) {
    state = 3;
    ignoreBlue = true;
  }
}

void blackFun() {
  if (!firstBlack) {
    l0 = left;
    r0 = right;
    firstBlack = true;
  }

  if (abs(left - l0) / 2 + abs(right - r0) / 2 < 750) {  //650
    leftMotorValue = -70;
    rightMotorValue = -70;
  } else {
    leftMotorValue = 0;
    rightMotorValue = 0;
    action.clear();
    pair p = coordFuture(xRobot, yRobot, robotDirection);
    deleteCell(p.first, p.second);

    bfs();
    firstBlack = false;
    firstCase2Cycle = true;
    state = 4;
    centralOld = centralVLX;
    backwardOld = backwardVLX;
    isMVImpact = false;
  }
}
