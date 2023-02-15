//#include <Wire.h>

#define e1 5
#define m1 4

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(m1, OUTPUT);
  pinMode(e1, OUTPUT);
}


void loop() 
{
  forward();
  delay(2000);
  totalStop();
  delay(1000);
  backward();
  delay(2000);
  totalStop();
  delay(1000);
}


void forward()
{
  digitalWrite(m1, LOW);
  for (byte i = 0; i < 255; i++)
  {
    analogWrite(e1, i);
    delay(15);
  }
}
void backward()
{
  digitalWrite(m1, HIGH);
  for (byte i = 0; i < 255; i++)
  {
    analogWrite(e1, i);
    delay(15);
  }
}

void totalStop()
{
  analogWrite(e1, 0);
}
