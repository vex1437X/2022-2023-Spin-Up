#include "main.h"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;



///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

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
  chassis.set_pid_constants(&chassis.turnPID, 1.2, 0.13, 0, 10);
  chassis.set_pid_constants(&chassis.swingPID, 0, 0, 0, 0);
}

double conv(double i){
  // use conv whenever youa re using drive PID
  return i * 3.8;
}

void tune_PID() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches

  tuning_constants();

  // chassis.set_turn_pid(90, 100);
  // chassis.wait_drive();

  chassis.set_drive_pid(conv(24), 80);
  chassis.wait_drive();

  printf("done1: %d \n", true);

  delay(2000);

  chassis.set_drive_pid(conv(-24), 80);
  chassis.wait_drive();

  printf("done2: %d \n", true);
}

void winpointRED(){

}

void winpointBLUE(){
  setFly(30);      // idle flywheel for
  setIntake(-100); // turn colour wheel
  delay(3000);
  setIntake(0);

  // drive backwards so turn doesnt collide with the wall
  chassis.set_drive_pid(conv(-8), 60);
  chassis.wait_drive();

  // turn to goal
  chassis.set_turn_pid(80, 50);
  chassis.wait_drive();

  setFly(100);
  delay(2000); // let flywheel get up to speed
  // shoot 1st disc
  indexer.set_value(true);
  delay(200);
  indexer.set_value(false);
  delay(2000); // wait for flywheel to get up to speed again
  // shoot 2nd disc
  indexer.set_value(true);
  delay(200);
  indexer.set_value(false);
  setFly(30);

  // turn to be parallel to the auton line
  chassis.set_turn_pid(65, 50);
  chassis.wait_drive();

  setIntake(100);
  // drive forwards while intaking 3 discs for driver control
  chassis.set_drive_pid(conv(130), 90);
  chassis.wait_drive();

  // turn to face other colour wheel
  chassis.set_turn_pid(65, 50);
  chassis.wait_drive();

  // drive into colour wheel
  chassis.set_drive_pid(conv(24), 70);
  chassis.wait_drive();

  // spin colour wheel
  setIntake(-100);
  delay(3000);
  setIntake(0);
}

