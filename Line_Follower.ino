/*
    * Information : A simple  line follower using five ir sensors algrothim to make the robot stay on the track .
    *               the pins from 13 to 2 is used to control the four motors through H-bridge ,ir sensors from A0 to A4 
    *               (left to right)
    * Author      : Blue Team : Abdelrhman mosad , mohamed bassem
    * File name   : line_follower_v2
    * Date        : 27/8/2019
*/
#define BLACK 0 
#define WHITE 1
#define INTIAL_SPEED 160
#define MAX_SPEED 225
#define MINI_SPEED 100
#define MID_SPEED 120
int flag;
int flag_right,flag_left ;
int check;
int irSensors[] = {A0, A1, A2, A3, A4}; //IR sensor pins
int irReadings[5];
//motor1
int motor_right1 = 13;
int motor_right2 = 12;
int motor_right1_pwm = 11 ;
//motor2
int motor_right3 = 7 ;
int motor_right4 = 6;
int motor_right2_pwm = 5 ;
//motor3
int motor_left1 = 8;
int motor_left2 = 9;
int motor_left1_pwm = 10 ;
//motor4
int motor_left3 = 4;
int motor_left4 = 2;
int motor_left2_pwm = 3 ;

int counter_of_points = 0 ;

void readIRSensors() {
  //Read the IR sensors and put the readings in irReadings array
  for (int pin = 0; pin < 5; pin++) {
    int pinNum = irSensors[pin];
    irReadings[pin] = digitalRead(pinNum);
    
  }
}
void move_left(){
  digitalWrite(motor_right1, HIGH);
  digitalWrite(motor_right2, LOW);
  digitalWrite(motor_right3, HIGH);
  digitalWrite(motor_right4, LOW);
  
  digitalWrite(motor_left1, LOW);
  digitalWrite(motor_left2, HIGH);
  digitalWrite(motor_left3, LOW);
  digitalWrite(motor_left4, HIGH);
  }
void move_right(){
  digitalWrite(motor_right1, LOW);
  digitalWrite(motor_right2, HIGH);
  digitalWrite(motor_right3, LOW);
  digitalWrite(motor_right4, HIGH);
  
  digitalWrite(motor_left1, HIGH);
  digitalWrite(motor_left2, LOW);
  digitalWrite(motor_left3, HIGH);
  digitalWrite(motor_left4, LOW);
  }
void move_forward(){
  digitalWrite(motor_right1, HIGH);
  digitalWrite(motor_right2, LOW);
  digitalWrite(motor_right3, HIGH);
  digitalWrite(motor_right4, LOW);

  
  digitalWrite(motor_left1, HIGH);
  digitalWrite(motor_left2, LOW);
  digitalWrite(motor_left3, HIGH);
  digitalWrite(motor_left4, LOW);
  }
void move_back(){
  digitalWrite(motor_right1, LOW);
  digitalWrite(motor_right2, HIGH);
  digitalWrite(motor_right3, LOW);
  digitalWrite(motor_right4, HIGH);
 
  digitalWrite(motor_left1, LOW);
  digitalWrite(motor_left2, HIGH);
  digitalWrite(motor_left3, LOW);
  digitalWrite(motor_left4, HIGH);
  }
void stop_moving(){
  digitalWrite(motor_right1, LOW);
  digitalWrite(motor_right2, LOW);
  digitalWrite(motor_right3, LOW);
  digitalWrite(motor_right4, LOW);
  
  digitalWrite(motor_left1, LOW);
  digitalWrite(motor_left2, LOW);
  digitalWrite(motor_left3, LOW);
  digitalWrite(motor_left4, LOW);
  } 
void change_speed(int Speed){
  analogWrite(motor_right1_pwm , Speed);
  analogWrite(motor_right2_pwm , Speed);
  analogWrite(motor_left1_pwm , Speed);
  analogWrite(motor_left2_pwm , Speed);
  }

void setup() {
  //Declare all IR sensors as inputs
  for (int pin = 0; pin < 5; pin++) {
    int pinNum = irSensors[pin];
    pinMode(pinNum, INPUT);
  }
  
  pinMode(motor_right1, OUTPUT);
  pinMode(motor_right2, OUTPUT);
  pinMode(motor_right1_pwm , OUTPUT);  
  
  pinMode(motor_right3, OUTPUT);
  pinMode(motor_right4, OUTPUT);
  pinMode(motor_right2_pwm , OUTPUT);
  
  pinMode(motor_left1, OUTPUT);
  pinMode(motor_left2, OUTPUT);
  pinMode(motor_left1_pwm , OUTPUT);
  
  pinMode(motor_left3, OUTPUT);
  pinMode(motor_left4, OUTPUT);
  pinMode(motor_left2_pwm , OUTPUT);
  
  change_speed(INTIAL_SPEED);
}

void loop() {
   readIRSensors();
  // The idael case 
  if((irReadings[0] == WHITE) && (irReadings[1] == WHITE)&&(irReadings[2] == BLACK)&& (irReadings[4] == WHITE)&&(irReadings[3] == WHITE)){
      change_speed(INTIAL_SPEED);
      move_forward();
      check = 0 ;
      flag_left = 0 ;
      flag_right = 0;}
 
  // has gone right    
  else if((irReadings[0] == WHITE) && (irReadings[1] == BLACK)&&(irReadings[2] == WHITE)&& (irReadings[4] == WHITE)&&(irReadings[3] == WHITE)){ 
      change_speed(INTIAL_SPEED); move_left();}
      
  else if((irReadings[0] == BLACK) && (irReadings[1] == WHITE)&&(irReadings[2] == WHITE)&& (irReadings[4] == WHITE)&&(irReadings[3] == WHITE)){ 
     change_speed(MID_SPEED); move_left(); flag_left = 1;} 
  
  // has gone left    
  else if((irReadings[0] == WHITE) && (irReadings[1] == WHITE)&&(irReadings[2] == WHITE)&& (irReadings[4] == BLACK)&&(irReadings[3] == WHITE)){ 
      change_speed(INTIAL_SPEED); move_right();} 

  else if((irReadings[0] == WHITE) && (irReadings[1] == WHITE)&&(irReadings[2] == WHITE)&& (irReadings[4] == WHITE)&&(irReadings[3] == BLACK)){ 
      change_speed(MID_SPEED); move_right(); flag_right = 1;} 
  
  //sharp angel
  else if((irReadings[0] == WHITE) && (irReadings[1] == WHITE)&&(irReadings[2] == BLACK)&& (irReadings[4] == WHITE)&&(irReadings[3] == BLACK)){ 
      change_speed(MINI_SPEED); check = 1 ; } 
      
  else if((irReadings[0] == WHITE) && (irReadings[1] == WHITE)&&(irReadings[2] == BLACK)&& (irReadings[4] == BLACK)&&(irReadings[3] == WHITE)){ 
       if( (check == 1 ) && (counter_of_points == 4) ) {move_right();} 
       }

  // 90 angel 
  else if((irReadings[0] == WHITE) && (irReadings[1] == WHITE)&&(irReadings[2] == BLACK)&& (irReadings[4] == BLACK)&&(irReadings[3] == BLACK)){ 
      change_speed(MAX_SPEED); move_right(); }
                           
  else if((irReadings[0] == BLACK) && (irReadings[1] == BLACK)&&(irReadings[2] == BLACK)&& (irReadings[4] == WHITE)&&(irReadings[3] == WHITE)){ 
      change_speed(MAX_SPEED); move_left(); }

  //all white 
  else if((irReadings[0] == WHITE) && (irReadings[1] == WHITE)&&(irReadings[2] == WHITE)&& (irReadings[4] == WHITE)&&(irReadings[3] == WHITE)){ 
      if(flag_right == 1){change_speed(MAX_SPEED); move_right();}
      else if (flag_left == 1){change_speed(MAX_SPEED); move_left();} 
      else {change_speed(MINI_SPEED); move_forward();} }

  // all black        
  else if((irReadings[0] == BLACK) && (irReadings[1] == BLACK)&&(irReadings[2] == BLACK)&& (irReadings[4] == BLACK)&&(irReadings[3] == BLACK)){ 
      counter_of_points++;
      delay(2000);  ///////////////////////////////////////
      change_speed(INTIAL_SPEED); 
      move_forward();}
      
}


 


