void setup() {
  Serial3.begin(115200);
  Serial2.begin(115200);
  Serial1.begin(115200);
  Serial.begin(115200);
  Wire.begin();
  Serial.println("YES");
  pinMode(LED_VICTIM, OUTPUT);
  pinMode(LED_IMU, OUTPUT);
  digitalWrite(LED_IMU, HIGH);
  digitalWrite(LED_VICTIM, HIGH);
  vlx_setup();
  Serial.println("YES");
  pinMode(lPin, OUTPUT);
  pinMode(rPin, OUTPUT);
  pinMode(lPin2, OUTPUT);
  pinMode(rPin2, OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  pinMode(sensorOut, INPUT);
  
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  attachInterrupt(0, leftPlus, RISING);
  attachInterrupt(1, rightPlus, RISING);
  pinMode(31, INPUT_PULLUP);
  //pinMode(LED_BUILTIN, OUTPUT);
  leftServo.attach(9);
  rightServo.attach(11);
  leftServo.write(270);
  rightServo.write(270);
  //digitalWrite(4, HIGH);
  
  IMUSetup();
  digitalWrite(LED_IMU, LOW);
  digitalWrite(LED_VICTIM, LOW);
  timer = millis();
  centralOld = centralVLX;
  backwardOld = backwardVLX;
}
