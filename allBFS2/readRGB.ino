int thr = 12;
void readRGB() {
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  // Reading the output frequency
  redFrequency = pulseIn(sensorOut, LOW);
  red = map(redFrequency, minRed, maxRed, 255, 0);
  
   // Printing the RED (R) value
  //Serial.print("R = ");
  //Serial.print(red);
  //delay(100);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  greenFrequency = pulseIn(sensorOut, LOW);
  green = map(redFrequency, minGreen, maxGreen, 255, 0);
  
  // Printing the GREEN (G) value  
  //Serial.print(" G = ");
  //Serial.print(green);
  //delay(100);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  blue = map(blueFrequency, minBlue, maxBlue, 255, 0);
  
  // Printing the BLUE (B) value 
  //Serial.print(" B = ");
  //Serial.print(blue);

  if (abs(red - white.r) < thr && abs(green - white.g) < thr && abs(blue - white.b) < thr) {
    Serial.print(" WHITE");
    color = 0;
  }
  else if (red > silver.r && green > silver.g && blue > silver.b) {
    Serial.print(" SILVER");
    color = 2;
  }
  else if (abs(red - black.r) < 20 + thr && abs(green - black.g) < 20 + thr && abs(blue - black.b) < 20 + thr) {
    Serial.print(" BLACK");
    color = 3;
  } 
  else if (abs(red - blue.r) < thr + 25 && abs(green - blue.g) < 25 + thr && abs(blue - blue.b) < 25 + thr) {
    Serial.print(" BLUE");
    color = 1;
  }
  //Serial.println();
  //delay(100);
}
