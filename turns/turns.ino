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

void totalStop() {
  digitalWrite(lEnc, LOW);
  digitalWrite(rEnc, LOW);
  analogWrite(lPin, 0);
  analogWrite(rPin, 0);
}

void turnLeft() {
  int pomL = left;

  while (left - pomL < 1550) {
    digitalWrite(lEnc, HIGH);
    digitalWrite(rEnc, LOW);
    analogWrite(lPin, 100);
    analogWrite(rPin, 100);
  }

  totalStop();
  delay(500);
}

void turnRight() {
  int pomR = right;
  while (right - pomR < 1550) {
    digitalWrite(lEnc, LOW);
    digitalWrite(rEnc, HIGH);
    analogWrite(lPin, 100);
    analogWrite(rPin, 100);
  }

  totalStop();
  delay(500);
}

void forward() {
  int pomR = right;
  
  while (abs(right - pomR) < 1700) {
    digitalWrite(lEnc, LOW);
    digitalWrite(rEnc, LOW);
    analogWrite(lPin, 100);
    analogWrite(rPin, 100);
  }

  totalStop();
  delay(500);
}

int cc = 0;
void loop() {
  forward();
  turnLeft();
  turnRight();
  while (true) delay(10);
}
