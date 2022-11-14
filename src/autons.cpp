#include "flywheel.hpp"
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
    chassis.right_motors[0].move_voltage(12000*sinSpeedR);
    chassis.right_motors[1].move_voltage(12000*sinSpeedR);
    count+=10;
    printf("Count: %f \n", count);
    delay(10);
  }
  chassis.left_motors[0].move_voltage(0);
  chassis.left_motors[1].move_voltage(0);
  chassis.right_motors[0].move_voltage(0);
  chassis.right_motors[1].move_voltage(0);
}

void tripleAuto(){       // shoot 3 in auton
  for (int i = 0; i < 3; i++){
    while(!canFire()){
      delay(10);
    } 
    if(canFire()) fireOneDisc();
  }
}

void doubleAuto(){       // shoot 2 in auton
  for (int i = 0; i < 2; i++){
    while(!canFire()){
      delay(10);
    } 
    if(canFire()) fireOneDisc();
  }
}
void singleAuto(){       // shoot 1 in auton
  for (int i = 0; i < 1; i++){
    while(!canFire()){
      delay(10);
    } 
    if(canFire()) fireOneDisc();
  }
}

void testCode(){
  tuning_constants();
  // setFlyAuto(85);
  // chassis.set_turn_pid(-32.5, 75);
  // chassis.wait_drive();
  // tripleAuto();
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.5, 0.1, 0, 5);
  chassis.set_drive_pid(conv(8), 100);
  chassis.wait_drive(); 
  setIntake(100);

  jiggle(3, 2);

  // tripleAuto();
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

void winpoint(){ // both colour wheels; shoot 2
  tuning_constants();
  setFlyAuto(82);

  chassis.set_drive_pid(conv(2.5), 50);
  chassis.wait_drive(); 

  setIntake(-100); // turn colour wheel
  delay(150);
  setIntake(0);

  // drive backwards so turn doesnt collide with the wall
  chassis.set_drive_pid(conv(-6), 80);
  chassis.wait_drive(); 

  // turn to goal
  chassis.set_turn_pid(167.6, 75);
  chassis.wait_drive();

  delay(1200);

  // shoot 1st disc
  tripleIndexer.set_value(false);
  fireOneDisc();
  tripleIndexer.set_value(false);
  setFlyAuto(79.5);

  delay(1100); // wait for flywheel to get up to speed again
  // shoot 2nd disc
  fireOneDisc();
  setFlyAuto(30);

  chassis.set_turn_pid(270, 70);
  chassis.wait_drive();

  setIntake(100);

  chassis.set_drive_pid(conv(34), 110, false, true);
  chassis.wait_drive();

  chassis.set_turn_pid(195, 50);
  chassis.wait_drive();

  chassis.set_drive_pid(conv(46.5), 100, false, true);
  chassis.wait_drive();

  chassis.set_turn_pid(228, 50);
  chassis.wait_drive();

  chassis.set_drive_pid(conv(68), 110, false, true);
  chassis.wait_drive();
  
  chassis.set_turn_pid(282, 50);
  chassis.wait_drive();

  setIntake(0);
  
  // drive into colour wheel
  setIntake(-100);
  chassis.set_drive_pid(conv(11), 70);
  chassis.wait_drive();

  // spin colour wheel
  delay(400);
  setIntake(0);
  chassis.set_drive_pid(conv(-4), 70);
}

void halfWPright(){ // right colour wheel; shoot 5
  tuning_constants();

  setFlyAuto(80); // spin up flywheel instantly

  setIntake(100);
  chassis.set_drive_pid(conv(30), 90); // drive closer to the centre line to shoot
  chassis.wait_drive();

  chassis.set_turn_pid(22.3, 65); // turn to be parallel with the centre line
  chassis.wait_drive();

  delay(800);

  setIntake(100);
  tripleIndexer.set_value(false);
  // shoot first
  fireOneDisc();
  tripleIndexer.set_value(false);
  delay(850); // wait for flywheel to get up to speed

  // shoot 2nd disc
  fireOneDisc();
  delay(850); // wait for flywheel to get up to speed

  // shoot 3nd disc
  fireOneDisc();
  setFlyAuto(30); //idle flywheel; easier to ramp up speed for next shot
  setIntake(100);

  chassis.set_turn_pid(-46, 85); // turn to be parallel with the centre line
  chassis.wait_drive();

  setFlyAuto(77.5);

  chassis.set_pid_constants(&chassis.forward_drivePID, 0.22, 0.02, 0, 0);
  chassis.set_drive_pid(conv(39.3), 105);
  chassis.wait_drive();
  tuning_constants();

  chassis.set_turn_pid(47, 80); // turn to goal
  chassis.wait_drive();

  // shoot 4th disc
  fireOneDisc();
  delay(1100); // wait for flywheel to get up to speed

  // shoot 5th disc
  fireOneDisc();
  setFlyAuto(30); //idle flywheel; easier to ramp up speed for next shot
  setIntake(0);

  chassis.set_turn_pid(135, 90); // turn to be parallel with the centre line
  chassis.wait_drive();

  chassis.set_drive_pid(conv(72), 127);
  chassis.wait_drive();

  chassis.set_turn_pid(180, 100); // turn to be perpendicular with the colour wheel
  chassis.wait_drive();

  setIntake(-100);
  chassis.set_drive_pid(conv(27), 127); // drive into colour wheel
  chassis.wait_drive();

  
  delay(550);
  setIntake(0);

  chassis.set_drive_pid(conv(-3), 70); // drive out of colour wheel
  chassis.wait_drive();
}

void halfWPleft(){ // left colour wheel; shoot 5
  tuning_constants();
  setFlyAuto(80.7);

  chassis.set_drive_pid(conv(2.5), 50);
  chassis.wait_drive(); 

  setIntake(-100); // turn colour wheel
  delay(130);
  setIntake(0);

  // drive backwards so turn doesnt collide with the wall
  chassis.set_drive_pid(conv(-6), 80);
  chassis.wait_drive(); 


  // turn to goal
  chassis.set_turn_pid(167.8, 75);
  chassis.wait_drive();

  delay(1200);

  // shoot 1st disc
  fireOneDisc();

  delay(1100); // wait for flywheel to get up to speed again
  // shoot 2nd disc
  fireOneDisc();
  setFlyAuto(30);

  chassis.set_turn_pid(229, 70);
  chassis.wait_drive();

  setIntake(100);

  chassis.set_drive_pid(conv(32), 90, false, true);
  chassis.wait_drive();

  chassis.set_drive_pid(conv(-5), 60, false, true);
  chassis.wait_drive();

  setFlyAuto(76.8);

  chassis.set_drive_pid(conv(29), 70, false, true);
  chassis.wait_drive();

  chassis.set_turn_pid(134.3, 70);
  chassis.wait_drive();
  delay(500);

  // shoot 3rd disc
  fireOneDisc();

  delay(1000); // wait for flywheel to get up to speed again
  // shoot 4th disc
  fireOneDisc();

  delay(1000); // wait for flywheel to get up to speed again
  // shoot 5th disc
  fireOneDisc();
  setFlyAuto(30);
}

void skillsPID1() {
  chassis.set_slew_min_power(70, 70);
  chassis.set_slew_distance(10, 10);
  chassis.set_pid_constants(&chassis.headingPID, 0, 0, 0, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.24, 0.05, 0, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.24, 0.05, 0, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5.6, 0.002, 32, 0);
  chassis.set_pid_constants(&chassis.swingPID, 0, 0, 0, 0);
}

void skills(){
  double o = 3; // starting orientation offset
  skillsPID1();

  setFlyAuto(30);

  chassis.set_drive_pid(conv(2.5), 80); // drive into colour wheel
  chassis.wait_drive(); 

  setIntake(-100); // turn colour wheel
  delay(150);
  setIntake(0);
  
  chassis.set_drive_pid(conv(-4), 90); // drive away from wall
  chassis.wait_drive();

  chassis.set_turn_pid(215+o, 80);
  chassis.wait_drive();

  chassis.set_drive_pid(conv(9.5), 80);
  chassis.wait_drive();

  setIntake(100);

  chassis.set_turn_pid(93+o, 80); // turn towards single disc / second colour wheel
  chassis.wait_drive();

  chassis.set_drive_pid(conv(33), 80); // intake one disc // and go to colour wheel
  chassis.wait_drive();

  setFlyAuto(76);

  setIntake(-100); // turn colour wheel
  delay(100);

  chassis.set_drive_pid(conv(-6), 80); // drive away from colour wheel
  chassis.wait_drive(); 

  setIntake(100);

  chassis.set_turn_pid(175.5+o, 80); // aim to first net
  chassis.wait_drive();

  chassis.set_drive_pid(conv(11), 80); // drive closer to goal
  chassis.wait_drive(); 

  delay(600);

  // shoot 1st disc
  fireOneDisc();
  delay(1500); // wait for flywheel to get up to speed
  setIntake(0);
  
  // shoot 2nd disc
  fireOneDisc();
  delay(1500); // wait for flywheel to get up to speed

  // shoot 3nd disc
  fireOneDisc();

  setFlyAuto(30); //idle flywheel; easier to ramp up speed for next shot

  chassis.set_turn_pid(270+o, 80); // turn to triple stack
  chassis.wait_drive();

  setIntake(100);
  chassis.set_drive_pid(conv(11), 80); // knock over the triple stack
  chassis.wait_drive(); 

  chassis.set_drive_pid(conv(-2), 40); // back up a little
  chassis.wait_drive(); 

  setFlyAuto(75);

  chassis.set_drive_pid(conv(20), 75); // intake triple stack
  chassis.wait_drive();

  chassis.set_turn_pid(277+o, 80); // aim to second net
  chassis.wait_drive();

  delay(500);

  // shoot 1st disc
  fireOneDisc();
  delay(1500); // wait for flywheel to get up to speed

  // shoot 2nd disc
  fireOneDisc();
  delay(1500); // wait for flywheel to get up to speed
  setIntake(0);

  // shoot 3nd disc
  fireOneDisc();

  setFlyAuto(30); //idle flywheel; easier to ramp up speed for next shot

  chassis.set_turn_pid(270+o, 80); // turn to other triple stack
  chassis.wait_drive();

  chassis.set_drive_pid(conv(11), 80); // knock over the triple stack
  chassis.wait_drive(); 

  chassis.set_drive_pid(conv(-2), 40); // back up a little
  chassis.wait_drive(); 

  setIntake(100);

  setFlyAuto(75);

  chassis.set_drive_pid(conv(20), 75); // intake triple stack
  chassis.wait_drive();

  chassis.set_turn_pid(277+o, 80); // aim to second net
  chassis.wait_drive();

  delay(500);

  // shoot 1st disc
  fireOneDisc();
  delay(1500); // wait for flywheel to get up to speed

  // shoot 2nd disc
  fireOneDisc();
  delay(1500); // wait for flywheel to get up to speed
  setIntake(0);

  // shoot 3nd disc
  fireOneDisc();

  setFlyAuto(30); //idle flywheel; easier to ramp up speed for next shot

  chassis.set_turn_pid(230+o, 80); // turn towards three lined up discs and colour wheel-ish
  chassis.wait_drive();

  setIntake(100);

  setFlyAuto(76);

  chassis.set_drive_pid(conv(50), 75); // intake the three consecutive discs
  chassis.wait_drive();

  chassis.set_turn_pid(328+o, 80); // turn towards second net
  chassis.wait_drive();

  delay(500);

  // shoot 1st disc
  fireOneDisc();
  delay(1500); // wait for flywheel to get up to speed

  // shoot 2nd disc
  fireOneDisc();
  delay(1500); // wait for flywheel to get up to speed
  setIntake(0);

  // shoot 3nd disc
  fireOneDisc();

  setFlyAuto(30); //idle flywheel; easier to ramp up speed for next shot

  chassis.set_turn_pid(230+o, 80); // turn towards colour wheel-ish
  chassis.wait_drive();

  chassis.set_drive_pid(conv(25), 75); // intake the three consecutive discs
  chassis.wait_drive();

  chassis.set_turn_pid(270+o, 80); // turn to be perpendicular to colour wheel
  chassis.wait_drive();

  // AT THIS POINT SHOULD HAVE 12 DISCS AND 2 COLOUR WHEELS 
}

// JIGGLES

void newhalfWPleft(){ // left colour wheel; shoot 6
  tuning_constants();
  setFlyAuto(85.6);

  chassis.set_drive_pid(conv(2.5), 50);
  chassis.wait_drive(); 

  setIntake(-100); // turn colour wheel
  delay(130);
  setIntake(0);

  // drive backwards so turn doesnt collide with the wall
  chassis.set_drive_pid(conv(-6), 80);
  chassis.wait_drive(); 


  // turn to goal
  chassis.set_turn_pid(168.3, 75);
  chassis.wait_drive();

  doubleAuto();

  chassis.set_turn_pid(229, 70);
  chassis.wait_drive();
  setFlyAuto(30);

  setIntake(100);

  chassis.set_drive_pid(conv(32), 90, false, true);
  chassis.wait_drive();

  chassis.set_drive_pid(conv(-5), 60, false, true);
  chassis.wait_drive();

  setFlyAuto(78.5);
  
  chassis.set_drive_pid(conv(27.5), 70, false, true);
  chassis.wait_drive();

  chassis.set_turn_pid(135.7, 70);
  chassis.wait_drive();

  tripleAuto();

  setFlyAuto(75);

  chassis.set_drive_pid(conv(11), 70, false, true);
  chassis.wait_drive();

  delay(2300);

  fireOneDisc();
}
