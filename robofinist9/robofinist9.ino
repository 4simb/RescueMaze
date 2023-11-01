#include <Streaming.h>
#include <VL53L0X.h>
#include <Servo.h>
#include <Wire.h>
#include "Queue.h"
#include "Structs.h"

#define SIZE 100

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
//16500
#define IMUCalibration 20000

#define S0 32
#define S1 33
#define S2 34
#define S3 35
#define sensorOut 36

#define TUMBLER_PIN 31

#define minRed 10
#define maxRed 250
#define minGreen 10
#define maxGreen 350
#define minBlue 10
#define maxBlue 250

//7 7
#define thresholdMVLeft 7
#define thresholdMVRight 7

#define pitchThresoldDown 13
#define pitchThresoldUp -13

#define LED_LEFT 12
#define LED_RIGHT 4

#define LBUTTON_UP 30
#define LBUTTON_LEFT 28
#define RBUTTON_UP 29
#define RBUTTON_RIGHT 27
#define MICR_BACK_RIGHT A10
#define MICR_BACK_LEFT A12

#define SERVO_PIN 9 
#define SERVO_RIGHT_PIN 13
#define SERVO_LEFT_PIN 11

//94
#define SERVO_CENTER 90
#define SERVO_LEFT 18
#define SERVO_RIGHT 152

#define S_FROM_RIGHT 0
#define S_TO_RIGHT 15

#define S_FROM_LEFT 115
#define S_TO_LEFT 95


#define angleEnc 2420
//2380

#define raveHistLength 14
//20
//#define raveHistLength2 10 

#define CLIMB 1
#define DESCENT 2
#define FIRST_FLOOR 0
#define SECOND_FLOOR 64

#define WHITE_COLOR 1
#define BLUE_COLOR 2
#define BLACK_COLOR 3
#define SILVER_COLOR 4

#define BACKWARD 0
#define FORWARD 1

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
long long int timer = 0;
float yOld = 0, getY = 0;
int getP = 0;
short int k = 0;
bool firstY = true;
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

int offerBackward[] = {70, 330, 635, 1010}; //655
int offerForward[] = {60, 455, 830, 1050}; //435

int raznNN, pomIi;
bool isMVLeftTurn = false;  

int velPitch = 150; //115
//1 -- back
//2 -- left
//3 -- right
//4 -- forward

int colorBase = 0;
bool ignoreBlue = false;
bool tumblerRead = false, tumblerReadOld = false;

int countFor = 0;

bool blinkIn = false, blinkOut = false, blinkOutOld = false;
int stateOld = -1;

bool firstCase2Cycle = true;
bool isMVImpact = false;

int countBack = 0, countForw = 0;
bool backRave = false, forwRave = false;
Queue<int> queBack;
Queue<int> queForw;
bool goSlide = false;

Vector<Vector<Trio> > maze;
int8_t robotDirection = 1; //УВАГА

int8_t xRobot = SIZE / 2, yRobot = SIZE / 2;

//-> 0
//up 1
//<- 2
//down 3

bool moveByWay = false;
Vector<CameraParams> wasMV;
//H -- 3
//S -- 2
//U -- 0
pair fEditor;

Queue<int8_t> action; //УВАГА

int floors;
char LETTER = '0';
bool afterAll = false;
bool afterBlue = false;


//Y -- 1
//R -- 1
//G -- 0

bool toLeft = false;

int8_t indexCheckpoint = 0;
int8_t dirCheckpoint = robotDirection;
int remLeftVLX = -1, remRightVLX = -1;
int timAl = -1;
