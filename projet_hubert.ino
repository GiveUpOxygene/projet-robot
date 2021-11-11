//    The direction of the car's movement
//  ENA   ENB   IN1   IN2   IN3   IN4   Description
//  HIGH  HIGH  HIGH  LOW   LOW   HIGH  Car is runing forward
//  HIGH  HIGH  LOW   HIGH  HIGH  LOW   Car is runing back
//  HIGH  HIGH  LOW   HIGH  LOW   HIGH  Car is turning left
//  HIGH  HIGH  HIGH  LOW   HIGH  LOW   Car is turning right
//  HIGH  HIGH  LOW   LOW   LOW   LOW   Car is stoped
//  HIGH  HIGH  HIGH  HIGH  HIGH  HIGH  Car is stoped
//  LOW   LOW   N/A   N/A   N/A   N/A   Car is stoped

#include "useful.h"
#include "useful_robot.h"
#include <Servo.h>

/*
void obstacles_avoidance_mode() {
  if(func_mode == ObstaclesAvoidance){
    servo.write(90);
    delays(500);
    middleDistance = getDistance();
    if(middleDistance <= 40) {
      stop();
      delays(500);
      servo.write(10);
      delays(1000);
      rightDistance = getDistance();

      delays(500);
      servo.write(90);
      delays(1000);
      servo.write(170);
      delays(1000);
      leftDistance = getDistance();

      delays(500);
      servo.write(90);
      delays(1000);
      if(rightDistance > leftDistance) {
        right();
        delays(360);
      } else if(rightDistance < leftDistance) {
        left();
        delays(360);
      } else if((rightDistance <= 40) || (leftDistance <= 40)) {
        back();
        delays(180);
      } else {
        forward();
      }
    } else {
        forward();
    }
  }
}

*/



void setup() {
  myservo.attach(3); // attach servo on pin 3 to servo object
  Serial.begin(9600);//open serial and set the baudrate
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(IN1,OUTPUT);//before using io pin, pin mode must be set first
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT); //acceleration
  pinMode(ENB,OUTPUT);
  stop();
  myservo.write(180);
}

void loop() {

}
