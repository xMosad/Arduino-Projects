#define trig1_rfront  4  /// Trigger Pin 1st ultrasonic
#define echo1_rfront  7    /// Echo Pin 1st ultrasonic
#define trig2_lfront  8    /// Trigger Pin 2sec ultrasonic
#define echo2_lfront  9   /// Echo Pin 2sec ultrasonic
#define RIGHT_MOTOR1 6
#define RIGHT_MOTOR2 5
#define LEFT_MOTOR1 10
#define LEFT_MOTOR2 11
#define FRONT_IR A0
#define BACK_IR A2
#define RIGHT_IR A1
#define LEFT_IR A3

#define BLACK 1
#define WHITE 0
#define TARGET 50 //30

 int front_ir ;
 int back_ir ;
 int right_ir ;
 int left_ir ;

void forward (){
  digitalWrite(RIGHT_MOTOR2 , LOW);
  delay(1);
  digitalWrite(RIGHT_MOTOR1 , HIGH);
  
  digitalWrite(LEFT_MOTOR2 , LOW);
  delay(1);
  digitalWrite(LEFT_MOTOR1 , HIGH);
  }
 void backward (){
  digitalWrite(RIGHT_MOTOR1 , LOW);
  delay(1);
  digitalWrite(RIGHT_MOTOR2 , HIGH);
  
  digitalWrite(LEFT_MOTOR1 , LOW);
  delay(1);
  digitalWrite(LEFT_MOTOR2 , HIGH);
  }
void right(){
  //left forward
  digitalWrite(LEFT_MOTOR2 , LOW);
  delay(1);
  digitalWrite(LEFT_MOTOR1 , HIGH);
  //right backward
  digitalWrite(RIGHT_MOTOR1 , LOW);
  delay(1);
  digitalWrite(RIGHT_MOTOR2 , HIGH);
  }
void left(){
  //right forward
  digitalWrite(RIGHT_MOTOR2 , LOW);
  delay(1);
  digitalWrite(RIGHT_MOTOR1 , HIGH);

  //left backward
  digitalWrite(LEFT_MOTOR1 , LOW);
  delay(1);
  digitalWrite(LEFT_MOTOR2 , HIGH);
  }  
void rotate(){
   //left forward
  digitalWrite(LEFT_MOTOR2 , LOW);
  delay(1);
  digitalWrite(LEFT_MOTOR1 , HIGH);
  //right backward
  digitalWrite(RIGHT_MOTOR1 , LOW);
  delay(1);
  digitalWrite(RIGHT_MOTOR2 , HIGH);
  }
int front1_ultra(){
  int distance;       /// distance between the sensor and object
  unsigned long period; /// period used to calculate period
  
  digitalWrite(trig1_rfront, LOW);   /// set Trigger Pin to low
  delayMicroseconds(3);     /// make he pulse settle

  /// Transmit 10 us high level pulse to the trigger pin
  digitalWrite(trig1_rfront, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1_rfront, LOW);
  
  /// wait to cpature the rising edge 
  period = pulseIn (echo1_rfront, HIGH); 
  distance  = (float)period / 58.8;
  return distance;
}

int front2_ultra(){
  int distance;       /// distance between the sensor and object
  unsigned long period; /// period used to calculate period
  
  digitalWrite(trig2_lfront, LOW);   /// set Trigger Pin to low
  delayMicroseconds(3);     /// make he pulse settle

  /// Transmit 10 us high level pulse to the trigger pin
  digitalWrite(trig2_lfront, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2_lfront, LOW);
  
  /// wait to cpature the rising edge 
  period = pulseIn (echo2_lfront, HIGH); 
  distance  = (float)period / 58.8;
  return distance;
}

void take_action(int right_ultra , int left_ultra){
  if (( right_ultra < TARGET ) && (left_ultra < TARGET)){
    forward();
    }
   else if (( right_ultra < TARGET ) ){//&&left_ultra > TARGET 
      right();
      }
    else if (( left_ultra < TARGET ) ){//&&right_ultra > TARGET
      left();
      }
      else { rotate();}
  }
       
void setup() {
   // for trigs
  pinMode(trig1_rfront, OUTPUT);
  pinMode(trig2_lfront, OUTPUT);
  // for echos
  pinMode(echo1_rfront, INPUT);
  pinMode(echo2_lfront, INPUT);

  //motors
  pinMode(RIGHT_MOTOR1 , OUTPUT);
  pinMode(RIGHT_MOTOR2 , OUTPUT);
  pinMode(LEFT_MOTOR1 , OUTPUT);
  pinMode(LEFT_MOTOR2 , OUTPUT);

  //IR
  pinMode(FRONT_IR , INPUT);
  pinMode(BACK_IR , INPUT);
  pinMode(RIGHT_IR , INPUT);
  pinMode(LEFT_IR , INPUT);

  delay(5000);
  forward();
 //Serial.begin(9600);
}

void loop() {
 front_ir = digitalRead(FRONT_IR);
 back_ir = digitalRead(BACK_IR);
 right_ir = digitalRead(RIGHT_IR);
 left_ir = digitalRead(LEFT_IR);
  
  int r_distanse = front1_ultra();
  int l_distanse = front2_ultra();
  if ((front_ir == BLACK ) && (back_ir == BLACK ) && (right_ir == BLACK ) && (left_ir == BLACK )   ){
   take_action(r_distanse , l_distanse );
   }
  else if (front_ir == WHITE){ backward();/*Serial.println("back escape");*/}
  else if (left_ir == WHITE){ right();/*Serial.println("right escape");*/}
  
  else if (back_ir == WHITE){ forward();/*Serial.println("front escape");*/}
  else if (right_ir == WHITE){ left();/*Serial.println("left escape");*/} 
      
}
