void throwOffKits() {
  leftMotorValue = 0;
  rightMotorValue = 0;
  if (isMVLeft) {
    digitalWrite(LED_LEFT, HIGH);
    digitalWrite(LED_RIGHT, LOW);
  }
  else if (isMVRight) {
    digitalWrite(LED_RIGHT, HIGH);
    digitalWrite(LED_LEFT, LOW);
  }

  if (blinkIn && millis() - timer > 6000) {
    mvCell.push_back(Vector<pair>());
    blinkIn = false;
    if (isMVLeft && !isMVRight) mvNums.push_back(0);
    else if (!isMVLeft && isMVRight) mvNums.push_back(1);
    
    if (stateOld == 2) {
      mvCell.push_back(Vector<pair>());
      mvCell[mvCell.size() - 1].push_back(pair(xRobot, yRobot));
      coordFuture();
      mvCell[mvCell.size() - 1].push_back(NNPair);
      isMVImpact = true;
    } else {
      mvCell.push_back(Vector<pair>());
      mvCell[mvCell.size() - 1].push_back(pair(xRobot, yRobot));
      isMVImpact = false;
    }

    isMVLeft = false;
    isMVRight = false;
    state = stateOld;
    isMVLeftTurn = true;
    //isMVImpact = true;
    timer = millis();
    digitalWrite(LED_LEFT, LOW);
    digitalWrite(LED_RIGHT, LOW);
    blinkOut = true;
    MVSetZero();
  }
}
