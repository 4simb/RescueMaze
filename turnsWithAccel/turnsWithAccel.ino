#include <Wire.h>
#include <MPU9250_asukiaaa.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_MLX90614.h>

Adafruit_BMP280 bme; // I2C
MPU9250_asukiaaa mpu;

#define lPin 6
#define rPin 8
#define lEnc 5
#define rEnc 7

volatile int left = 0;
volatile int right = 0;
float gX, gY, gZ;
float yaw = 0, pitch = 0, roll = 0;
float t;
//MPU9250 mpu;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

#ifdef _ESP32_HAL_I2C_H_ // For ESP32
  Wire.begin(SDA_PIN, SCL_PIN);
  mpu.setWire(&Wire);
#else
  Wire.begin();
  mpu.setWire(&Wire);
#endif

  bme.begin();
  mpu.beginGyro();
  pinMode(lPin, OUTPUT);
  pinMode(rPin, OUTPUT);
  pinMode(lEnc, INPUT);
  pinMode(rEnc, INPUT);
  attachInterrupt(0, leftPlus, FALLING);
  attachInterrupt(1, rightPlus, FALLING);
}

void leftPlus() {
  if (digitalRead(lEnc)) left++;
  else left--;
}

void rightPlus() {
  if (digitalRead(rEnc)) right++;
  else right--;
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

void getGyro() {
  static int t = millis();
  if (mpu.gyroUpdate() == 0) {
    gX = mpu.gyroX();
    if(abs(gX) >= 0 && abs(gX) < 200) yaw += gX * (millis() - t) * 0.001;
    gY = mpu.gyroY();
    if(abs(gY) >= 0 && abs(gY) < 200) pitch += gY * (millis() - t) * 0.001;
    gZ = mpu.gyroZ();
    if(abs(gZ) >= 0 && abs(gZ) < 200) roll += gZ * (millis() - t) * 0.001;
    t = millis();

    if (roll > 360) roll = 0;
    else if (roll < -360) roll = 0;

    Serial.println(roll);
  }
}

void turnLeftGyro() {
  int pomRoll = roll;

  while (abs(pomRoll - roll) < 90) {
    getGyro();
    digitalWrite(lEnc, HIGH);
    digitalWrite(rEnc, LOW);
    analogWrite(lPin, 110);
    analogWrite(rPin, -110);
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
  turnLeftGyro();
}
