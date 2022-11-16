#include "catapult.hpp"
#include "intake.hpp"
#include "main.h"
#include "pros/imu.h"
#include <cmath>

Imu imu(13);

void none(){}

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void tuning_constants() {
  chassis.set_slew_min_power(70, 70);
  chassis.set_slew_distance(10, 10);
  chassis.set_pid_constants(&chassis.headingPID, 0, 0, 0, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.24, 0.05, 0, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.24, 0.05, 0, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5.6, 0.002, 32, 0);
  chassis.set_pid_constants(&chassis.swingPID, 0, 0, 0, 0);
}

double conv(double i){
  // use conv whenever you're using drive PID
  return i * 3.8;
}

double sinSpeedL = 0;
double sinSpeedR = 0;
double sinConst = 2.5;
double LRoffset = M_PI/2;

void sinCalc(void*){
  double t = 0;
  while(true){
    t+=0.1;
    sinSpeedL = sin(sinConst*t-LRoffset);
    sinSpeedR = sin(sinConst*t+LRoffset);
    if(fabs(sinSpeedL < 0.2))sinSpeedL = 0.2;
    if(fabs(sinSpeedR < 0.2))sinSpeedR = 0.2;
    printf("sinSpeedL: %f \n", sinSpeedL);
    printf("sinSpeedR: %f \n", sinSpeedR);
    printf("t: %f \n", t);
    delay(10);
  }
}

void jiggle(double sec, double sinConstant){
  sinConst = sinConstant;
  double msec = sec*1000;
  double count = 0;
  printf("Msec: %f \n", msec);
  while(count < msec){
    chassis.left_motors[0].move_voltage(12000*sinSpeedL);
    chassis.left_motors[1].move_voltage(12000*sinSpeedL);
    chassis.left_motors[2].move_voltage(12000*sinSpeedL);
    chassis.right_motors[0].move_voltage(12000*sinSpeedR);
    chassis.right_motors[1].move_voltage(12000*sinSpeedR);
    chassis.right_motors[2].move_voltage(12000*sinSpeedR);
    count+=10;
    printf("Count: %f \n", count);
    delay(10);
  }
  chassis.left_motors[0].move_voltage(0);
  chassis.left_motors[1].move_voltage(0);
  chassis.left_motors[2].move_voltage(0);
  chassis.right_motors[0].move_voltage(0);
  chassis.right_motors[1].move_voltage(0);
  chassis.right_motors[2].move_voltage(0);
}

void testCode(){
  tuning_constants();
  // chassis.set_turn_pid(-32.5, 75);
  // chassis.wait_drive();
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.5, 0.1, 0, 5);
  chassis.set_drive_pid(conv(8), 100);
  chassis.wait_drive(); 
  setIntake(100);

  jiggle(3, 2);

}

void tune_PID() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches

  tuning_constants();

  chassis.set_turn_pid(90, 100);
  chassis.wait_drive();

  // chassis.set_drive_pid(conv(24), 80);
  // chassis.wait_drive();

  printf("done1: %d \n", true);

  // delay(2000);

  // chassis.set_drive_pid(conv(-24), 80);
  // chassis.wait_drive();

  // printf("done2: %d \n", true);
}

void winpoint(){}

void rightside(){}

void leftside(){}