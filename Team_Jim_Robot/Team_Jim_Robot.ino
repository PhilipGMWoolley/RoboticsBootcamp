#include <Adafruit_MotorShield.h>

int MIN_DIST_TO_WALL = 5;
int MAX_DIST_TO_WALL = 10;
int MAX_FRONT_DIST = 15;

const int FRONT_TRIG = 8;
const int FRONT_ECHO = 9;
const int LEFT_TRIG = 11;
const int LEFT_ECHO = 10;

int Wall_Distance;
int Front_Distance;
bool FIRST_OBSTACLE;

void FirstObstacleArch();
void SecondObstacleArch();

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *driveMotor = AFMS.getMotor(1);
Adafruit_DCMotor *turnMotor = AFMS.getMotor(2);

void setup() {
  Serial.begin(9600);
  pinMode(FRONT_TRIG, OUTPUT);
  pinMode(FRONT_ECHO, INPUT);
  pinMode(LEFT_TRIG, OUTPUT);
  pinMode(LEFT_ECHO, INPUT);

  AFMS.begin();

  driveMotor->setSpeed(150);
  turnMotor->setSpeed(150);
  FIRST_OBSTACLE = true;
}

void loop() {
  digitalWrite(LEFT_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(LEFT_TRIG, LOW);
  int wall_duration = pulseIn(LEFT_ECHO, HIGH);
  Wall_Distance = ((wall_duration/29)/2);
  
  digitalWrite(FRONT_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(FRONT_TRIG, LOW);
  int front_duration = pulseIn(FRONT_ECHO, HIGH);
  Front_Distance = ((front_duration/29)/2);

  Serial.print("FRONT DISTANCE: ");
  Serial.println(Front_Distance);
  Serial.print("WALL DISTANCE: ");
  Serial.println(Wall_Distance);

  //No Obstacles
  if(Front_Distance > MAX_FRONT_DIST){
    driveMotor->setSpeed(150);
    driveMotor->run(FORWARD);
  }

  //If wall is more than MAX_WALL_DISTANCE move closer to wall
  if (Wall_Distance > MAX_DIST_TO_WALL) {
    //turn left
    turnMotor->run(BACKWARD);
  }
  //Else if wall is less than MIN_WALL_DISTANCE move farther from wall
  else if (Wall_Distance < MIN_DIST_TO_WALL) {
    //turn right
    turnMotor->run(FORWARD);
  }
  //Else Release turn motor
  else{
    turnMotor->run(RELEASE);
  }

  //Getting close to an obstacle
  if(Front_Distance < MAX_FRONT_DIST){
    //SLOW DOWN and begin turning
    driveMotor->setSpeed(50);
    if(FIRST_OBSTACLE){
      FirstObstacleArch();
      FIRST_OBSTACLE = false;
    }else{
      SecondObstacleArch();
    }
  }
}

//Play with parameters of turning to determine best arches:
void FirstObstacleArch(){
  for(int i = 0; i < 10; i++){
      turnMotor->run(FORWARD);
      delay(20);
      turnMotor->run(RELEASE);
      delay(10);
    }
    turnMotor->run(RELEASE);
}

void SecondObstacleArch(){
  for(int i = 0; i < 50; i++){
      turnMotor->run(FORWARD);
      delay(20);
      turnMotor->run(RELEASE);
      delay(10);
    }
    turnMotor->run(RELEASE);
}

