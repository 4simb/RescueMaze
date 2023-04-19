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
    blinkIn = false;
    isMVLeft = false;
    isMVRight = false;
    if (stateOld == 2) isMVImpact = true;
    else isMVImpact = false;
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
