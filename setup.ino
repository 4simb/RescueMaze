void setup() {
  delay(50);
  Serial2.begin(115200);
  Serial1.begin(115200);
  Serial.begin(115200);
  //Serial.println("YES");
  Wire.begin();
  Serial.println("YES");
  vlx_setup();
  Serial.println("YES");
  pinMode(lPin, OUTPUT);
  pinMode(rPin, OUTPUT);
  pinMode(lPin2, OUTPUT);
  pinMode(rPin2, OUTPUT);
  attachInterrupt(0, leftPlus, RISING);
  attachInterrupt(1, rightPlus, RISING);
  int t0 = millis(), t;

  do {
    getVLX();
    t = millis();

    if (Serial1.available()) {
      n = map((float)Serial1.read(), 0, 255, 0, 360);

      if (isYaw) y0 = n;
      else p0 = n;

      Serial.println(String(y0) + "   " + String(p0));

      isYaw = !isYaw;
    }

    centralOld = centralVLX;
  } while (t - t0 < 13000);
  timer = millis();
}
