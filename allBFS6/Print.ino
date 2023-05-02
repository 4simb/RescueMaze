void printBase() {
  Serial.print(pitch);
  Serial.print(" ");
  Serial.print(roll);
  Serial.print(" ");
  Serial.print(state);
  Serial.print(" ");
  Serial.print(stateOld);
  Serial.print(" ");
  /*Serial.print(left);
    Serial.print(" ");
    Serial.print(right);
    Serial.print(" ");
    Serial.print(yaw);
    Serial.print(" ");*/
  Serial.print(centralVLX);
  Serial.print(" "); //25 380 680
  Serial.print(backwardVLX);
  Serial.print(" "); //50 370 680
  Serial.print(leftVLX);
  Serial.print(" ");
  Serial.print(rightVLX);
  Serial.print(" ");
  /*Serial.print(openMVReadLeft);
    Serial.print(" ");
    Serial.print(centralOld);
    Serial.print(" ");
    Serial.print(ignoreWordsLeft);
    Serial.print(" ");*/
  Serial.print(leftMotorValue);
  Serial.print(" ");
  Serial.print(rightMotorValue);
  Serial.print(" ");
  Serial.print(centralOld);
  Serial.print(" ");
  Serial.print(backwardOld);
}

void printCoords() {
  Serial.println();
  for (int i = 0; i < smezh.size(); ++i) {
    for (int j = 0; j < smezh[i].size(); ++j) {
       Serial << "(" << smezh[i][j].first << "; " << smezh[i][j].second << ")";

       if (j == 0) Serial << ": ";
       else if (j != smezh[i].size() - 1) Serial << ",";  
    }

    Serial.println();
  }
}
