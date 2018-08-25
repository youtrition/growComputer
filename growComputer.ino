#include <Event.h>
#include <Timer.h>

Timer t;

//Variables Declaration
const int phUp = 1;
const int phDown = 2;
const int ecUp = 3;
const int ecDown = 4;
const int waterSensor = 5;
const int maxSensorPin = A0;
const int minSensorPin = A1;
const int PHMax = 6;
const int PHMin = 5.5;
const int ECMax = 2000;
const int ECMin = 1900;

const int waterSenseLimit = 10;
const int waterSenseSensibility = 100;

const int PHcheckInterval = 1000;
const int ECcheckInterval = 1000;
const int waterCheckInterval = 1000;

int senseMin = 0;
int senseMax = 0;

float ph = 0; //Range from 0-14 (theoretically)
int ec = 0; //Range from 0-4000
bool waterMax = true;
bool waterMin = true;
bool fillWater = false;

//Void Setup
void setup() {
  pinMode(phUp, OUTPUT);
  pinMode(phDown, OUTPUT);
  pinMode(ecUp, OUTPUT);
  pinMode(ecDown, OUTPUT);
  pinMode(waterSensor, OUTPUT);
  pinMode(waterMax, INPUT);
  pinMode(waterMin, INPUT);
  
  //Set Timers
  t.every(PHcheckInterval, getPH);
  t.every(ECcheckInterval, getEC);
  t.every(waterCheckInterval, senseMaxLevel);
  t.every(waterCheckInterval, senseMinLevel);
  t.every(PHcheckInterval, regulate);
}

//Void Loop
void loop() {
  t.update(); //Update Timer
}

void getEC() {

}

void getPH() {

}

void regulate() {
  if(ph > PHMax)PHDown();
  if(ph < PHMin)PHUp();
  if(ec > ECMax)ECDown();
  if(ec < ECMin)ECUp();
}
void PHDown() { //Use pH Down Agent for a specified amount of time
  
}
void PHUp() { //Use pH Up Agent for a specified amount of time
  
}
void ECDown() { //Fill Water until Max Level is reached, if still too high, trigger an alarm
  
}
void ECUp() { //Fill Urine unitl ecMin or maxLevel is reached
  
}
void checkWater() {
  if(waterMin == false) {
    if(bitRead(PORTD,ecDown)==0)digitalWrite(ecDown,HIGH);
  } else {
    if(bitRead(PORTD,ecDown)==1)digitalWrite(ecDown,LOW);
  }
}

void senseMaxLevel() {
  //Read Pin
  digitalWrite(waterSensor,HIGH); //Turn voltage on
  if (analogRead(maxSensorPin) < waterSenseSensibility) {
    senseMax+=1;
  }else{
    senseMax-=1;
  }
  //Check Borders
  senseMax = min(senseMax , waterSenseLimit);
  senseMax = max(senseMax , 0);
  
  digitalWrite(waterSensor,LOW); //Turn voltage off
  //Return Boolean
  if (senseMax >= waterSenseLimit) {
    waterMax = true;
  } else {
    waterMax = false;
  }
}
void senseMinLevel() {
  //Read Pin
  digitalWrite(waterSensor,HIGH); //Turn voltage on
  if (analogRead(maxSensorPin) < waterSenseSensibility) {
    senseMin+=1;
  }else{
    senseMin-=1;
  }
  //Check Borders
  senseMin = min(senseMin , waterSenseLimit);
  senseMin = max(senseMin , 0);
  
  digitalWrite(waterSensor,LOW); //Turn voltage off
  //Return Boolean
  if (senseMin >= waterSenseLimit) {
    waterMin = true;
      } else {
    waterMin = false;
  }
}

