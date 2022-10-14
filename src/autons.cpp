#include "intake.hpp"
#include "main.h"
#include "pros/imu.h"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////

Imu imu(13);

const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;

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
  setDisc(2);
  setFly(81);

  chassis.set_drive_pid(conv(2.5), 50);
  chassis.wait_drive(); 

  setIntake(-100); // turn colour wheel
  delay(75);
  setIntake(0);

  // drive backwards so turn doesnt collide with the wall
  chassis.set_drive_pid(conv(-7), 80);
  chassis.wait_drive(); 

  // turn to goal
  chassis.set_turn_pid(175, 75);
  chassis.wait_drive();


  delay(1500);

  // shoot 1st disc
  fireOneDisc();
  setDisc(1);
  setFly(79);

  delay(1900); // wait for flywheel to get up to speed again
  // shoot 2nd disc
  fireOneDisc();
  setDisc(0);
  setFly(30);


  chassis.set_turn_pid(270, 70);
  chassis.wait_drive();

  setIntake(100);

  chassis.set_drive_pid(conv(34), 110, false, true);
  chassis.wait_drive();

  chassis.set_turn_pid(210, 50);
  chassis.wait_drive();

  chassis.set_drive_pid(conv(55), 100, false, true);
  chassis.wait_drive();

  chassis.set_turn_pid(235, 50);
  chassis.wait_drive();

  chassis.set_drive_pid(conv(62), 110, false, false);
  chassis.wait_drive();
  
  chassis.set_turn_pid(282, 50);
  chassis.wait_drive();

  setIntake(0);
  
  // drive into colour wheel
  chassis.set_drive_pid(conv(25), 70);
  chassis.wait_drive();

  // spin colour wheel
  setIntake(-100);
  delay(150);
}

void halfWPright(){ // right colour wheel; shoot 3
  tuning_constants();

  setIntake(100);
  setFly(74.5); // spin up flywheel instantly

  chassis.set_drive_pid(conv(30), 70); // drive closer to the centre line to shoot
  chassis.wait_drive();

  chassis.set_turn_pid(18.5, 40); // turn to be parallel with the centre line
  chassis.wait_drive();

  delay(1000);

  fireOneDisc();
  delay(2000); // wait for flywheel to get up to speed
  setFly(74.5);

  // shoot 2nd disc
  fireOneDisc();
  delay(2000); // wait for flywheel to get up to speed
  setFly(74.5);

  // shoot 3nd disc
  fireOneDisc();
  setFly(30); //idle flywheel; easier to ramp up speed for next shot
  setDisc(0);
  setIntake(0);

  chassis.set_turn_pid(135, 40); // turn to be parallel with the centre line
  chassis.wait_drive();

  chassis.set_drive_pid(conv(36), 70);
  chassis.wait_drive();

  chassis.set_turn_pid(180, 40); // turn to be perpendicular with the colour wheel
  chassis.wait_drive();

  setIntake(-100);
  chassis.set_drive_pid(conv(30), 70); // drive into colour wheel
  chassis.wait_drive();

  setIntake(-100);
  delay(600);
  setIntake(0);
}

void halfWPleft(){ // left colour wheel; shoot 5
  tuning_constants();

  tuning_constants();
  setDisc(2);
  setFly(81);

  chassis.set_drive_pid(conv(2.5), 50);
  chassis.wait_drive(); 

  setIntake(-100); // turn colour wheel
  delay(75);
  setIntake(0);

  // drive backwards so turn doesnt collide with the wall
  chassis.set_drive_pid(conv(-7), 80);
  chassis.wait_drive(); 

  // turn to goal
  chassis.set_turn_pid(175.5, 75);
  chassis.wait_drive();


  delay(1500);

  // shoot 1st disc
  fireOneDisc();
  setDisc(1);
  setFly(81.5);

  delay(1900); // wait for flywheel to get up to speed again
  // shoot 2nd disc
  fireOneDisc();
  setDisc(0);
  setFly(30);

  chassis.set_turn_pid(215, 70);
  chassis.wait_drive();

  chassis.set_drive_pid(conv(30), 80);
  chassis.wait_drive(); 

  setIntake(100);

  chassis.set_drive_pid(conv(30), 50);
  chassis.wait_drive(); 

  setIntake(0);

  chassis.set_turn_pid(145, 70);
  chassis.wait_drive();

  delay(1000);

  fireOneDisc();
  delay(2000); // wait for flywheel to get up to speed
  setFly(75);

  // shoot 2nd disc
  fireOneDisc();
  delay(2000); // wait for flywheel to get up to speed
  setFly(75);

  // shoot 3nd disc
  fireOneDisc();
  setFly(30); //idle flywheel; easier to ramp up speed for next shot
  setDisc(0);
}

void skills(){
  tuning_constants();
  setDisc(2);

  imu.reset();
  delay(1500);

  // spin colour wheel
  setIntake(-100);
  delay(75);
  setIntake(0);

  // drive away from wall
  chassis.set_drive_pid(conv(-10), 70);
  chassis.wait_drive();

  chassis.set_turn_pid(105, 70);
  chassis.wait_drive();

  setIntake(100);
  chassis.set_drive_pid(conv(20), 40);
  chassis.wait_drive();
  setIntake(0);
  setDisc(3);

  // turn to face colour wheel
  chassis.set_turn_pid(70, 70);
  chassis.wait_drive();

  // drive into colour wheel
  chassis.set_drive_pid(conv(30), 55);
  chassis.wait_drive();

  // spin colour wheel
  setIntake(-100); // turn colour wheel
  delay(75);
  setIntake(0);

  // drive away from wall
  chassis.set_drive_pid(conv(-20), 70);
  chassis.wait_drive();

  setFly(84);
  // turn to face goal
  chassis.set_turn_pid(130, 70);
  chassis.wait_drive();

  // drive towards goal
  chassis.set_drive_pid(conv(60), 80);
  chassis.wait_drive();

  fireThreeDiscs();
  setDisc(0);
  delay(300);
  setFly(0);
}