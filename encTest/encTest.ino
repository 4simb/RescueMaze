#define lPin 6
#define rPin 8
#define lEnc 5
#define rEnc 7

volatile int left = 0;
volatile int right = 0;

void leftPlus() {
  if (digitalRead(lEnc)) left++;
  else left--;
}

void rightPlus() {
  if (digitalRead(rEnc)) right++;
  else right--;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(lPin, OUTPUT);
  pinMode(rPin, OUTPUT);
  pinMode(lEnc, INPUT);
  pinMode(rEnc, INPUT);
  attachInterrupt(0, leftPlus, FALLING);
  attachInterrupt(1, rightPlus, FALLING);
}

int cc = 0;
void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(left);
  Serial.print(" ");
  Serial.println(right);

  if (cc < 200) {
    digitalWrite(lEnc, HIGH);
    digitalWrite(rEnc, HIGH);
  }
  else if (cc < 400) {
    digitalWrite(lEnc, LOW);
    digitalWrite(rEnc, LOW);
  }
  else cc = 0;
  
  analogWrite(lPin, -150);
  analogWrite(rPin, -150);
  delay(1);

  ++cc;
}
