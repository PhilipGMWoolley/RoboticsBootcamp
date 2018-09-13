int MIN_DIST_TO_WALL = 5;
int MAX_DIST_TO_WALL = 10;

const int FRONT_TRIG = 4;
const int FRONT_ECHO = 5;
const int LEFT_TRIG = 6;
const int LEFT_ECHO = 7;

int Wall_Distance;
int Front_Distance;

void FirstObstacleArch();
void SecondObstacleArch();

void setup() {
  Serial.begin(9600);
  pinMode(FRONT_TRIG, OUTPUT);
  pinMode(FRONT_ECHO, INPUT);
  pinMode(LEFT_TRIG, OUTPUT);
  pinMode(LEFT_ECHO, INPUT);
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

  //If wall is more than MAX_WALL_DISTANCE move closer to wall
  //Else if wall si less than MIN_WALL_DISTANCE move farther from wall

  //If obstacle is approaching
    //If First Obstacle do FirstObstacleArch
    //Else do SecondObstacleArch  
  
}

void FirstObstacleArch(){
  
}

void SecondObstacleArch(){
  
}

