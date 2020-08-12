/*
    * Information : code for robot with three servo motors and and bluetooth module to control the servo motors therefor
    *               controling the movement of the arm servo on pins (A0 -> A2) the bluetooth is connected to A4 , A5 
    *               4 motors are used to move the base of the robot and takes the pins (2 -> 13) an app was designed to
    *               control the arm visit https://drive.google.com/file/d/1MUVOKkNVJ1QfSKml49ArNwGIav-VxVDv/view?usp=sharing
    *               to download the application
    * Author      : Blue Team : Abdelrhman mosad , mohamed bassem
    * File name   : arm
    * Date        : 27/8/2019
*/
#include <SoftwareSerial.h>
#include <Servo.h>
#define INTIAL_SPEED 155

Servo servo01; // waist
Servo servo02; // grip 
Servo servo03;//elbow
//motor1 right
int motor_right1 = 13;
int motor_right2 = 12;
int motor_right1_pwm = 11 ;
//motor2 right 
int motor_right3 = 7 ;
int motor_right4 = 6;
int motor_right2_pwm = 5 ;
// motor3 left
int motor_left1 = 8;
int motor_left2 = 9;
int motor_left1_pwm = 10 ;
//motor4 left
int motor_left3 = 4;
int motor_left4 = 2;
int motor_left2_pwm = 3 ;

SoftwareSerial Bluetooth(A4, A5); // Arduino(RX, TX) - HC-05 Bluetooth (TX, RX)
int servo1Pos, servo2Pos , servo3Pos; // current position
int servo1PPos, servo2PPos , servo3PPos; // previous position
int speedDelay = 20;

String dataIn = "";
void setup() {
  // for robot
  pinMode(motor_right1, OUTPUT);
  pinMode(motor_right2, OUTPUT);
  pinMode(motor_right1_pwm , OUTPUT);
  analogWrite(motor_right1_pwm , INTIAL_SPEED);
  
  pinMode(motor_right3, OUTPUT);
  pinMode(motor_right4, OUTPUT);
  pinMode(motor_right2_pwm , OUTPUT);
  analogWrite(motor_right2_pwm , INTIAL_SPEED);
  
  pinMode(motor_left1, OUTPUT);
  pinMode(motor_left2, OUTPUT);
  pinMode(motor_left1_pwm , OUTPUT);
  analogWrite(motor_left1_pwm , INTIAL_SPEED);
  
  pinMode(motor_left3, OUTPUT);
  pinMode(motor_left4, OUTPUT);
  pinMode(motor_left2_pwm , OUTPUT);
  analogWrite(motor_left2_pwm , INTIAL_SPEED);
  
  // for arm 
  servo01.attach(A0);
  servo02.attach(A1);
  servo03.attach(A2);
  Bluetooth.begin(9600); // Default baud rate of the Bluetooth module
  Bluetooth.setTimeout(2);
  delay(20);
  // Robot arm initial position
  servo1PPos = 90;
  servo01.write(servo1PPos);
  servo2PPos = 45;
  servo02.write(servo2PPos);
  servo3PPos = 35;
  servo03.write(servo3PPos);
}
void loop() {
  // Check for incoming data
  if (Bluetooth.available() > 0) {
    dataIn = Bluetooth.readString();  // Read the data as string
    
    // If "Waist" slider has changed value - Move Servo 1 to position
    if (dataIn.startsWith("s1")) {
      String dataInS = dataIn.substring(2, dataIn.length()); // Extract only the number. E.g. from "s1120" to "120"
      servo1Pos = dataInS.toInt();  // Convert the string into integer
      // We use for loops so we can control the speed of the servo
      // If previous position is bigger then current position
      if (servo1PPos > servo1Pos) {
        for ( int j = servo1PPos; j >= servo1Pos; j--) {   // Run servo down
          servo01.write(j);
          delay(20);    // defines the speed at which the servo rotates
        }
      }
      // If previous position is smaller then current position
      if (servo1PPos < servo1Pos) {
        for ( int j = servo1PPos; j <= servo1Pos; j++) {   // Run servo up
          servo01.write(j);
          delay(20);
        }
      }
      servo1PPos = servo1Pos;   // set current position as previous position
    }
    
    // Move Servo 2
    if (dataIn.startsWith("s2")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo2Pos = dataInS.toInt();
      if (servo2PPos > servo2Pos) {
        for ( int j = servo2PPos; j >= servo2Pos; j--) {
          servo02.write(j);
          delay(50);
        }
      }
      if (servo2PPos < servo2Pos) {
        for ( int j = servo2PPos; j <= servo2Pos; j++) {
          servo02.write(j);
          delay(50);
        }
      }
      servo2PPos = servo2Pos;
    }
 // Move Servo 3
    if (dataIn.startsWith("s3")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo3Pos = dataInS.toInt();
      if (servo3PPos > servo3Pos) {
        for ( int j = servo3PPos; j >= servo3Pos; j--) {
          servo03.write(j);
          delay(30);
        }
      }
      if (servo3PPos < servo3Pos) {
        for ( int j = servo3PPos; j <= servo3Pos; j++) {
          servo03.write(j);
          delay(30);
        }
      }
      servo3PPos = servo3Pos;
    }    
   /******** moving the robot  ***********/
   if (dataIn == "left"){move_left(); }
   else if (dataIn == "right"){move_right(); }
   else if (dataIn == "forward"){move_forward(); }
   else if (dataIn == "back"){move_back(); }
   else if (dataIn == "stop"){stop_moving(); }
   
}
}
void move_left(){
  stop_moving();
  delay(20);
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
  stop_moving();
  delay(20);
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
  stop_moving();
  delay(20);
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
  stop_moving();
  delay(20);
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
  
    
