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

  if (abs(red - 127) < thr && abs(green - 165) < thr && abs(blue - 172) < thr) {
    Serial.print(" WHITE");
    color = 0;
  }
  else if (red > 150 && green > 150 && blue > 150) {
    Serial.print(" SILVER");
    color = 2;
  }
  else if (abs(red - 30) < 20 + thr && abs(green - 96) < 20 + thr && abs(blue - 87) < 20 + thr) {
    Serial.print(" BLACK");
    color = 3;
  } 
  else if (abs(red + 23) < thr + 25 && abs(green - 60) < 25 + thr && abs(blue - 89) < 25 + thr) {
    Serial.print(" BLUE");
    color = 1;
  }
  //Serial.println();
  //delay(100);
}
