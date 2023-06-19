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

#define LBUTTON_UP 30
#define LBUTTON_LEFT 28
#define RBUTTON_UP 29
#define RBUTTON_RIGHT 27

#define SERVO_PIN 9 
#define SERVO_CENTER 97
#define SERVO_LEFT 30
#define SERVO_RIGHT 160

//LED_LEFT -- blue
//LED_RIGHT -- yellow

//rightMV -- Serial3
//leftMV -- Serial2
//servo -- D9

VL53L0X vlxF; // Sensor1;
VL53L0X vlxL; //Sensor2;
VL53L0X vlxR; //Sensor3;
VL53L0X vlxB; //Sensor4
Servo servo;

float yFirst = 0, pFirst = 0;
float yaw = 0, pitch = 0, roll = 0;
long int left = 0;
long int right = 0;
float err, errOld = 0, u, p, d, uVLX, uIMU, uEnc;
short int leftMotorValue, rightMotorValue;
short int centralVLX, leftVLX, rightVLX, backwardVLX, centralOld = 0, backwardOld = 0;
float zeroYaw;
long long int timer = 0;
float yOld = 0, pOld, getY = 0;
int getP = 0;
short int k = 0, kPitch = 0;
bool firstY = true, firstP = true;
float errAcc = 0;
int countAcc = 0;

char openMVReadLeft = '0';
int countHLeft = 0, countSLeft = 0, countULeft = 0, countGreenLeft = 0, countRedLeft = 0, countYellowLeft = 0;
bool ignoreWordsLeft = false;

char openMVReadRight = '0';
int countHRight = 0, countSRight = 0, countURight = 0, countGreenRight = 0, countRedRight = 0, countYellowRight = 0;
bool ignoreWordsRight = false;

bool isMVLeft = false, isMVRight = false;
int ignoreCount = 0;

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

int offerSize = 4;
int offerI;
//70 400 730 1010
//65 450 740 1100
//int offerBackward[] = {65, 350, 650, 1010}; //680
//int offerForward[] = {65, 455, 723, 1093}; //435

int offerBackward[] = {70, 395, 700, 1010}; //680
int offerForward[] = {55, 450, 740, 1100}; //435

int raznNN, pomIi;
bool isMVLeftTurn = false;  

int velPitch = 115;
//1 -- back
//2 -- left
//3 -- right
//4 -- forward

int colorBase = 0;
bool ignoreBlue = false;
bool tumblerRead = false, tumblerReadOld = false;
bool isGor = false, isGorOld = false;
int countFor = 0;
//bool byEnc = false;

bool blinkIn = false, blinkOut = false, blinkOutOld = false;
int stateOld = -1;

bool firstCase2Cycle = true;
bool isMVImpact = false;

int raveHistLength = 10, countBack = 0, countForw = 0;
bool backRave = false, forwRave = false;
Queue<int> queBack;
Queue<int> queForw;
bool goSlide = false;

Vector<Vector<Trio> > smezh;
int8_t robotDirection = 2; //УВАГА

int8_t xRobot = SIZE / 2, yRobot = SIZE / 2;
//LEFT BACK RIGHT FORW

//-> 0
//^ 1
//<- 2
//down 3

bool moveByWay = false;
Vector<CameraParams> wasMV;
pair NNPair, fEditor;

Queue<int8_t> action; //УВАГА

//Colors
//Vec3b whiteColor = {172, 195, 182};
//Vec3b blackColor = {55, 114, 73};
//Vec3b blueColor = {55, 120, 110};

int8_t floors;
char LETTER = '0';
bool afterAll = false;
bool afterBlue = false;

//H -- 3
//S -- 2
//U -- 0

//Y -- 1
//R -- 1
//G -- 0

bool toLeft = false;

int8_t indexCheckpoint = 0;
int8_t dirCheckpoint = robotDirection;
