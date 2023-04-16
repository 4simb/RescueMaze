void loop() {
  getVLX();
  getAngle();
  readRGB();
  tumblerRead = digitalRead(31);
  
  readMVRight();
  readMVLeft();

  Serial.print(state);
  Serial.print(" ");
  Serial.print(stateOld);
  Serial.print(" ");
  Serial.print(left);
  Serial.print(" ");
  Serial.print(right);
  Serial.print(" ");
  Serial.print(yaw);
  Serial.print(" ");
  Serial.print(centralVLX);
  Serial.print(" "); //25 380 680
  Serial.print(backwardVLX);
  Serial.print(" "); //50 370 680
  Serial.print(leftVLX);
  Serial.print(" ");
  Serial.print(rightVLX);
  Serial.print(" ");
  Serial.print(openMVReadLeft);
  Serial.print(" ");
  Serial.print(centralOld);
  Serial.print(" ");
  Serial.print(ignoreWordsLeft);
  Serial.print(" ");
  Serial.print(leftMotorValue);
  Serial.print(" ");
  Serial.print(rightMotorValue);

  if (tumblerRead != tumblerReadOld) {
    state = 3;
    timer = millis();
    centralOld = centralVLX;
    backwardOld = backwardVLX;
  }

  //setMotors(-90, -90);
  if (!tumblerRead) {
    switch (state) {
      case 0: //leftTurn
        Turns();
        if (differenceYaw(zeroYaw, yaw) <= 1) {
          Serial.println("SU");
          if (!isMVLeft) state = 2;
          else state = 6;
          isGorOld = false;
          isMVLeftTurn = false;
          setting = yaw;
          l0 = left;
          r0 = right;

          /*if (!isMVLeft && ignoreWordsLeft && nextState == 0) {
            ignoreWordsLeft = false;
            nextState = -1;
            isMVLeftTurn = false;
            }*/
        }
        break;
      case 1: //rightTurn
        Turns();
        Serial.print("   ");
        Serial.print(zeroYaw);
        if (differenceYaw(zeroYaw, yaw) <= 1) { //1
          //if (!isMVRight && !ignoreWords) state = 4;
          //else if (!isMVRight) state = 3;
          state = 4;

          /*if (!isMVLeft && ignoreWordsLeft && nextState == 1) {
            ignoreWordsLeft = false;
            nextState = -1;
            isMVLeftTurn = false;
          }*/
          timer = millis();
          isMVLeftTurn = false;
          //isMVLeftTurn = false;
        }
        break;
      case 2: //forward
        if (((byEnc || (backwardOld >= offerBackward[offerSize - 1] && centralOld >= offerForward[offerSize - 1]))
             && ((left - l0) / 2 + (right - r0) / 2) + rememberEnc < 4750) //2750
            || (backwardOld >= offerBackward[offerSize - 1] && centralOld < offerForward[offerSize - 1]
                && centralVLX > valueForward(centralOld) && centralVLX >= 41 && centralVLX < 8000)
            || (backwardOld < offerBackward[offerSize - 1] && centralOld >= offerForward[offerSize - 1]
                && backwardVLX < valueBackward(backwardOld) && centralVLX >= 41 && backwardVLX < 8000)
            || (backwardOld < offerBackward[offerSize - 1] && centralOld < offerForward[offerSize - 1]
                && backwardVLX < valueBackward(backwardOld) && centralVLX >= 41 && backwardVLX < 8000)) { //660
          if (backwardOld < offerBackward[offerSize - 1] && centralOld >= offerForward[offerSize - 1]
                && backwardVLX < valueBackward(backwardOld) && centralVLX >= 41 && backwardVLX < 8000) Serial.print(" BACK");
                
          if (backwardOld >= offerBackward[offerSize - 1] && centralOld < offerForward[offerSize - 1]
                && centralVLX > valueForward(centralOld) && centralVLX >= 41 && centralVLX < 8000) {
            Serial.print(" FORW ");
            Serial.print(valueForward(centralOld));
          }
          if (backwardOld < offerBackward[offerSize - 1] && centralOld < offerForward[offerSize - 1]
                && backwardVLX < valueBackward(backwardOld) && centralVLX >= 41 && backwardVLX < 8000)
            Serial.print(" F_and_B");

          if ((backwardOld >= offerBackward[offerSize - 1] && centralOld >= offerForward[offerSize - 1]
             && ((left - l0) / 2 + (right - r0) / 2) + rememberEnc < 2750)) {
             Serial.print("  ENC");
          }
          if ((pitch > 25 && pitch < 100) || (pitch < 335 && pitch > 300)) {
            isGor = true;
            //isGorOld = isGor;
            velPitch = 90;
          }
          else {
            isGor = false;
            velPitch = 135;
          }

          //if (isGorOld && (pitch < 5 || pitch > 355)) state = 5;
          VLXandIMU(velPitch, setting);
          if (((left - l0) / 2 + (right - r0) / 2) + rememberEnc > 1550) byEnc = false;

          /*if (!isMVLeft && ignoreWordsLeft && nextState == 2 && ((left - l0) / 2 + (right - r0)) / 2 > 700) {
            ignoreWordsLeft = false;
            nextState = -1;
            }*/
          if (color == 3) {
            state = 8;
            l0 = left;
            r0 = right;
            //zeroYaw = higherYaw(normalize(yaw + 180));
          }
          countFor++;

          //if (abs(leftMotorValue) < 20 && abs(rightMotorValue) < 20) byEnc = true;
          //isGorOld = isGor;
        } else {
          if (countFor != 0) {
            rememberEnc = 0;
            state = 4;
            timer = millis();
            ignoreBlue = false;
            countFor = 0;
            byEnc = false;
            blinkOut = false;
          } else {
            byEnc = true;
            l0 = left;
            r0 = right;
            rememberEnc = 0;
          }
        }
        break;
      case 3: //question
        if (centralVLX != -1 && centralVLX <= 150 && !alWas) {
          state = 5;
        } else {
          alWas = false;
          if (leftVLX >= 300 && !ignore_left) {
            state = 0;
            zeroYaw = higherYaw(normalize(yaw + 90)); //Left
          } else if (centralVLX != -1 && centralVLX <= 200) {
            state = 1;
            zeroYaw = higherYaw(normalize(yaw - 90)); //Right
          } else {
            state = 2;
            setting = higherYaw(yaw);
          }

          //if (!ignoreWordsLeft) rememberEnc = 0;
          isGorOld = false;
        }

        if (color == 1 && !ignoreBlue) {
          state = 7;
          timer = millis();
        }

        ignore_left = false;
        //if (!isMVLeft && ignoreWordsLeft) nextState = state;
        break;
      case 4: //stop
        leftMotorValue = 0;
        rightMotorValue = 0;
        if (millis() - timer > 1500) state = 3;
        break;
      case 5: //alignment
        if (firstAlignment) {
          firstAlignment = false;
          timerAlignment = millis();
        } else if (!secondAlignment) {
          if (millis() - timerAlignment < 600) {
            leftMotorValue = 55;
            rightMotorValue = 55;
          } else secondAlignment = true;
        } else {
          if (centralVLX < 0) { //40
            leftMotorValue = -80;
            rightMotorValue = -80;
          } else {
            state = 4;
            secondAlignment = false;
            firstAlignment = true;
            alWas = true;
          }
        }
        break;
      case 6: //throw off
        //Serial.println("YUP");
        leftMotorValue = 0;
        rightMotorValue = 0;
        digitalWrite(LED_VICTIM, HIGH);
        
        if (blinkIn && millis() - timer > 6000) {
          servoNowLeft -= kL * 35;
          servoNowRight -= kR * 35;
          blinkIn = false;
          isMVLeft = false;
          //centralOld = centralVLX;
          //backwardOld = backwardVLX;
          /*if (stateOld == 0) {
            state = 2;
            isMVLeftTurn = true;
          }
          else state = 3;*/
          state = stateOld;
          isMVLeftTurn = true;
          timer = millis();
          digitalWrite(LED_VICTIM, LOW);
          blinkOut = true;
          MVSetZero();
         }
        break;
      case 7: //BLUE
        leftMotorValue = 0;
        rightMotorValue = 0;
        if (millis() - timer > 6000) {
          state = 3;
          ignoreBlue = true;
        }
        break;
      case 8: //BLACK
        if  ((left - l0 + right - r0) / 2 < 900) {
          leftMotorValue = -70;
          rightMotorValue = -70;
        } else {
          if (rightVLX > 140) {
            state = 1;
            zeroYaw = higherYaw(normalize(yaw - 90));
          } else {
            state = 0;
            zeroYaw = higherYaw(normalize(yaw + 90));
          }

          ignore_left = true;
        }
        break;
    }

    setMotors(leftMotorValue, rightMotorValue);

    if (state != 2 && state != 6) {
      if (!isMVLeft && !isMVLeftTurn) {
        centralOld = centralVLX;
        backwardOld = backwardVLX;
      }

      if (state != 0 && state != 1 && state != 8) {
        l0 = left;
        r0 = right;
      }
    }
  } else setMotors(0, 0); 

  tumblerReadOld = tumblerRead;
  //+setMotors(0, 0);
  Serial.println();
}
