#include <VL53L0X.h>
#include <Wire.h>
#define lPin 6
#define rPin 8
#define lPin2 5
#define rPin2 7
#define Sensor1_newAddress 41
#define Sensor2_newAddress 42
#define Sensor3_newAddress 43
#define XSHUT_pin3 24
#define XSHUT_pin2 23
#define XSHUT_pin1 22

VL53L0X vlxF; // Sensor1;
VL53L0X vlxL; //Sensor2;
VL53L0X vlxR; //Sensor3;

float y0 = 0, p0 = 0;
float yaw = 0, pitch = 0, roll = 0;
volatile int left = 0;
volatile int right = 0;
float err, errOld = 0, u, p, d, uVLX, uIMU, uEnc;
short int leftMotorValue, rightMotorValue;
short int centralVLX, leftVLX, rightVLX, centralOld = 0;
bool isYaw = true;
float zeroYaw;
float n;
long int timer = 0;
float yOld = 0, pOld, getY = 0, getP = 0;
short int k = 0, kPitch = 0;
bool firstY = true, firstP = true;
float errAcc = 0;
int countAcc = 0;
char openMVRead = '0';
byte countH = 0, countS = 0, countRed = 0, countYellow = 0;
bool ignoreWords = false, canChangeMVLeft = true, isMVLeft = false, isMVRight = false;
byte ignoreCount = 0;
float fy, setting = 0;
int l0 = 0, r0 = 0, time0 = 0;
bool firstAlignment = true, secondAlignment = false;
bool alWas = false;//, ignoreWords = false;
long int timerAlignment, timeMVLeft;
long int rememberEnc = 0;
bool forwardByVLX = true;


int state = 3; //УВАГА
