#include <Streaming.h>
#include <VL53L0X.h>
#include <Servo.h>
#include <Wire.h>
#include "Queue.h"
#include "Structs.h"

#define SIZE 50

#define lPin 8
#define rPin 6
#define lPin2 7
#define rPin2 5

#define SensorB_newAddress 37
#define SensorR_newAddress 38
#define SensorL_newAddress 39
#define SensorF_newAddress 40
//42 43 44 45

#define XSHUT_pinB 22
#define XSHUT_pinR 23
#define XSHUT_pinL 25
#define XSHUT_pinF 24

//15000
#define IMUCalibration 15000

#define S0 32
#define S1 33
#define S2 34
#define S3 35
#define sensorOut 36

#define minRed 10
#define maxRed 250
#define minGreen 10
#define maxGreen 350
#define minBlue 10
#define maxBlue 250

#define thresholdMVLeft 10
#define thresholdMVRight 10

#define pitchThresoldDown 13
#define pitchThresoldUp -13

#define LED_LEFT 4
#define LED_RIGHT 12

#define BUTTON_LEFT 30
#define BUTTON_RIGHT 29

//LED_LEFT -- blue
//LED_RIGHT -- yellow

//rightMV -- Serial3
//leftMV -- Serial2
//leftServo -- servo6 -- D9
//right -- servo5 -- D11

VL53L0X vlxF; // Sensor1;
VL53L0X vlxL; //Sensor2;
VL53L0X vlxR; //Sensor3;
VL53L0X vlxB; //Sensor4

Servo leftServo;
Servo rightServo;

float yFirst = 0, pFirst = 0;
float yaw = 0, pitch = 0, roll = 0;
long int left = 0;
long int right = 0;
float err, errOld = 0, u, p, d, uVLX, uIMU, uEnc;
short int leftMotorValue, rightMotorValue;
short int centralVLX, leftVLX, rightVLX, backwardVLX, centralOld = 0, backwardOld = 0;
float zeroYaw;
long int timer = 0;
float yOld = 0, pOld, getY = 0;
int getP = 0;
short int k = 0, kPitch = 0;
bool firstY = true, firstP = true;
float errAcc = 0;
int countAcc = 0;

char openMVReadLeft = '0';
byte countHLeft = 0, countSLeft = 0, countULeft = 0, countGreenLeft = 0, countRedLeft = 0, countYellowLeft = 0;
bool ignoreWordsLeft = false;

char openMVReadRight = '0';
byte countHRight = 0, countSRight = 0, countURight = 0, countGreenRight = 0, countRedRight = 0, countYellowRight = 0;
bool ignoreWordsRight = false;

bool isMVLeft = false, isMVRight = false;
byte ignoreCount = 0;

long long int tMVLeftOld, tMVRightOld;
bool lNormal = false, rNormal = false; 

float fy, setting = 0;
long int l0 = 0, r0 = 0, time0 = 0;
bool firstAlignment = true, secondAlignment = false;
bool alWas = false;//, ignoreWords = false;
long int timerAlignment, timeMVLeft;
long int rememberEnc = 0;
bool forwardByVLX = true;

int state = 3; //УВАГА
int nextState = -1;

byte offerSize = 4;
byte offerI;
int offerBackward[] = {65, 350, 680, 1010};
int offerForward[] = {65, 395, 723, 1093};
int raznNN, pomIi;
bool isMVLeftTurn = false;  

int velPitch = 115;
//1 -- back
//2 -- left
//3 -- right
//4 -- forward

byte color = 0;
bool ignoreBlue = false;
bool tumblerRead = false, tumblerReadOld = false;
bool isGor = false, isGorOld = false;
int countFor = 0;
//bool byEnc = false;

bool blinkIn = false, blinkOut = false;
int servoNowLeft = 270, servoNowRight = 270;
int kL = 0, kR = 0;
int stateOld = -1;

bool ignore_left = false;

bool firstCase2Cycle = true;
bool isMVImpact = false;

int raveHistLength = 10, countBack = 0, countForw = 0;
bool backRave = false, forwRave = false;
Queue<int> queBack;
Queue<int> queForw;
bool goSlide = false;

Vector<Vector<Trio> > smezh;
short int robotDirection = 2; //УВАГА

int xRobot = SIZE / 2, yRobot = SIZE / 2;
//LEFT BACK RIGHT FORW

//-> 0
//^ 1
//<- 2
//down 3

bool moveByWay = false;
Vector<CameraParams> wasMV;
pair NNPair, fEditor;

Queue<int> action; //УВАГА

//Colors
Vec3b blackCell(30, 96, 87);
Vec3b blueCell(-23, 60, 89);
Vec3b whiteCell(127, 165, 172);
Vec3b silverCell(150, 150, 150);

int floors;
