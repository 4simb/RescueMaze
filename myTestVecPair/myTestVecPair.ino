#include <Arduino.h>
#include <Streaming.h>
#include <Vector.h>
#include <Pair.h>


const long BAUD = 115200;

//const int ELEMENT_COUNT_MAX = 5;
//typedef Vector<Pair<int, int> > Elements;
//const size_t DELAY = 1500;

void setup()
{
  Serial.begin(BAUD);
  while (!Serial) {
  }
}

void loop()
{
  //int storage_array[ELEMENT_COUNT_MAX];
  //Elements vector;

  //vector.setStorage(storage_array);
  //vector.push_back(make_pair(0, 0));
  //vector.push_back(make_pair(1, 0));
 // vector.push_back(make_pair(2, 0));
  Serial << "vector.size(): " << vector.size() << Serial::endl;
  Serial << "vector:" << endl;
  Serial << vector << endl;
  vector.remove(0);
  Serial << "vector.remove(0):" << endl;
  Serial << vector << endl;
  vector.remove(1);
  Serial << "vector.remove(1):" << endl;
  Serial << vector << endl;
  delay(DELAY);
}
