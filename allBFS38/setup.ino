void setup() {
  Serial3.begin(115200);
  Serial2.begin(115200);
  Serial1.begin(115200);
  Serial.begin(115200);
  
  Wire.begin();
  Serial.println("true");  
  
  pinMode(LED_LEFT, OUTPUT);
  pinMode(LED_RIGHT, OUTPUT);
  digitalWrite(LED_LEFT, HIGH);
  digitalWrite(LED_RIGHT, HIGH);
  
  vlx_setup();
  Serial.println("YES");
  pinMode(lPin, OUTPUT);
  pinMode(rPin, OUTPUT);
  pinMode(lPin2, OUTPUT);
  pinMode(rPin2, OUTPUT);
  pinMode(LBUTTON_UP, INPUT_PULLUP);
  pinMode(RBUTTON_UP, INPUT_PULLUP);
  pinMode(LBUTTON_LEFT, INPUT_PULLUP);
  pinMode(RBUTTON_RIGHT, INPUT_PULLUP);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  pinMode(sensorOut, INPUT);
  
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  attachInterrupt(0, leftPlus, RISING);
  attachInterrupt(1, rightPlus, RISING);
  pinMode(TUMBLER_PIN, INPUT_PULLUP);

  servo.attach(SERVO_PIN);
  servo.write(SERVO_CENTER);
  
  IMUSetup();
  digitalWrite(LED_LEFT, LOW);
  digitalWrite(LED_RIGHT, LOW);
  timer = millis();
  centralOld = centralVLX;
  backwardOld = backwardVLX;

  addCell(false, 0);
  bfs();
  Serial << "BFS really end" << endl;
  startUART();
  Serial << "UART Started" << endl;
  //while (true) Serial2.write('B');
}
