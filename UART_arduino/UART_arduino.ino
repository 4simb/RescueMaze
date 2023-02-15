#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);
  Wire.begin();

  Serial.println("NN");
}

byte openMVRead;
int count = 0;
void loop() {
  if (Serial3.available()) {
     Serial.print("TRUE STORY ");
     Serial.print(count);
     Serial.print(" ");
     openMVRead = Serial3.read();
     Serial3.write(openMVRead);
     Serial.println((char)openMVRead);
     ++count;
  }
}
