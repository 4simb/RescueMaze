int thr = 12;

void readRGB() {
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
  int green = map(redFrequency, minGreen, maxGreen, 255, 0);

  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  // Reading the output frequency
  int blueFrequency = pulseIn(sensorOut, LOW);
  int blue = map(blueFrequency, minBlue, maxBlue, 255, 0);
  Vec3b colorNow(red, green, blue);
  /*int clr = colorNow.getColor({172, 195, 182}, {55, 114, 73}, {55, 120, 110});

  if (clr == 2) {
    state = 7;
    colorBase = 1;
  }*/
}
/*
  double cosBetweenColors(Vec3b color1, Vec3b color2){
  return (color1.r * color2.r + color1.g * color2.g + color1.b * color2.b) / (module(color1) * module(color2));
  }

  double module(Vec3b color){
  //long sq1 = sqrt(color.r * color.r + color.g * color.g);
  return sqrt(color.r * color.r + color.g * color.g + color.b * color.b);
  }

  void printColor(int r, int g, int b){
  Vec3b color = {r, g, b};
  if(cosBetweenColors(whiteColor, color) > 0.99) Serial.println("WHITE");
  else if(cosBetweenColors(blackColor, color) > 0.99) Serial.println("BLACK");
  else if(cosBetweenColors(blueColor, color) < 0.99) Serial.println("BLUE");
  else Serial.println("NO COLOR");
  }

  void getColor(Vec3b color){
  if(cosBetweenColors(whiteColor, color) > 0.99) Serial.println("WHITE");
  else if(cosBetweenColors(blueColor, color) > 0.99) {
    Serial.println("BLUE");
    state = 7;
    colorBase = 1;
  } else if(cosBetweenColors(blackColor, color) > 0.99) {
    Serial.println("BLACK");
  }
  else Serial.println("NO COLOR");
  }
*/

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
    Vector<int> smezhNum;
    coordFuture(xRobot, yRobot, robotDirection);
    pair p = NNPair;

    for (int i = 0; i < smezh.size(); ++i) {
      if (smezh[i][0].first == p.first && smezh[i][0].second == p.second && smezh[i][0].floor == floors) {
        smezhNum.push_back(i);
        //break;
      }
    }

    for (int j = 0; j < smezhNum.size(); ++j) {
      Vector<pair> intermediate;

      int s = smezh[j].size() - 1;
      while (s > 1) {
        if (p.first == smezh[j][s].first && p.second == smezh[j][s].second) {
          smezh[j].pop_back();
          break;
        }
        else intermediate.push_back(pair(smezh[j][s].first, smezh[j][s].second));
        smezh[j].pop_back();
        s = smezh[j].size() - 1;
      }

      for (int i = 0; i < intermediate.size(); ++i) {
        smezh[j].push_back(Trio(intermediate[i].first, intermediate[i].second, floors));
      }
    }

    bfs();
    ignore_left = true;
  }
}
