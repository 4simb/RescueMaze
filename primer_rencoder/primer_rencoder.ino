 //#include <Wire.h>

#define e1 5
#define m1 4

int enc = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(m1, OUTPUT);
  pinMode(e1, OUTPUT);
  attachInterrupt(0, leftPlus, RISING);
}


void loop() {
  forward();
  if (enc >= 1720) //1730
  {
    totalStop();
    Serial.println(enc);
    enc = 0;
    delay(2000);
  }
}

void forward()
{
  digitalWrite(m1, HIGH);
  analogWrite(e1, 50);
}

void totalStop()
{
  analogWrite(e1, 0);
}

void leftPlus()
{
  enc++;
}
