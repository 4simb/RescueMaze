void printBase() {
  Serial << backwardVLX << " " << centralVLX << endl;
  //Serial << "PITCH: " << pitch << " YAW: " << yaw << endl;
  //Serial << lNormal << rNormal << " ";
  /*Serial.print(pitch);
  Serial.print(" ");
  Serial.print(yaw);
  Serial.print(" ");
  Serial.print(state);
  Serial.print(" ");
  Serial.print(stateOld);
  Serial.print(" ");*/
  /*Serial.print(left);
    Serial.print(" ");
    Serial.print(right);
    Serial.print(" ");
    Serial.print(yaw);
    Serial.print(" ");*/
  /*Serial.print(centralVLX);
  Serial.print(" "); //25 380 680
  Serial.print(backwardVLX);
  Serial.print(" "); //50 370 680
  Serial.print(leftVLX);
  Serial.print(" ");
  Serial.print(rightVLX);
  Serial.print(" ");*/
  /*Serial.print(openMVReadLeft);
    Serial.print(" ");
    Serial.print(centralOld);
    Serial.print(" ");
    Serial.print(ignoreWordsLeft);
    Serial.print(" ");*/
  /*Serial.print(leftMotorValue);
  Serial.print(" ");
  Serial.print(rightMotorValue);
  Serial.print(" ");
  Serial.print(centralOld);
  Serial.print(" ");
  Serial.print(backwardOld);*/
}

void printCoords() {
  Serial.println();
  for (int i = 0; i < maze.size(); ++i) {
    for (int j = 0; j < maze[i].size(); ++j) {
       Serial << "(" << maze[i][j].first << "; " << maze[i][j].second << "; " << maze[i][j].floor << ")";

       if (j == 0) Serial << ": ";
       else if (j != maze[i].size() - 1) Serial << ",";  
    }

    Serial.println();
  }
}
