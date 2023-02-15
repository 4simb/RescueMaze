/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// TCS230 or TCS3200 pins wiring to Arduino
#define S0 33
#define S1 32
#define S2 34
#define S3 35
#define sensorOut 36

#define minRed 10
#define maxRed 250
#define minGreen 10
#define maxGreen 350
#define minBlue 10
#define maxBlue 250

// Stores frequency read by the photodiodes
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

void setup() {
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
   // Begins serial communication 
  Serial.begin(115200);
}

int red, green, blue;
void loop() {
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  // Reading the output frequency
  redFrequency = pulseIn(sensorOut, LOW);
  red = map(redFrequency, minRed, maxRed, 255, 0);
  
   // Printing the RED (R) value
  Serial.print("R = ");
  Serial.print(red);
  //delay(100);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  greenFrequency = pulseIn(sensorOut, LOW);
  green = map(redFrequency, minGreen, maxGreen, 255, 0);
  
  // Printing the GREEN (G) value  
  Serial.print(" G = ");
  Serial.print(green);
  //delay(100);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  blue = map(blueFrequency, minBlue, maxBlue, 255, 0);
  
  // Printing the BLUE (B) value 
  Serial.print(" B = ");
  Serial.println(blue);
  delay(100);
}
