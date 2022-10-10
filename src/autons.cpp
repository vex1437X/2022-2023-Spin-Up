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

Task intakeT(intaketask, nullptr);
bool cringer = false;
void intaketask(void*){
  while(true){
    if(cringer){
      setIntake(-100);
      delay(4000);
      setIntake(100);
    }
    delay(30);
  }
  
}

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
  // use conv whenever youa re using drive PID
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

/*
void winpoint(){
  tuning_constants();
  setDisc(2);

  setFly(96);
  setIntake(-100); // turn colour wheel
  delay(75);
  setIntake(0);

  // drive backwards so turn doesnt collide with the wall
  chassis.set_drive_pid(conv(-7), 80);
  chassis.wait_drive(); 

  // turn to goal
  chassis.set_turn_pid(164, 75);
  chassis.wait_drive();


  delay(2500);
  // shoot 1st disc
  setDisc(1);
  indexer.set_value(true);
  delay(300);
  indexer.set_value(false);
  setFly(96);
  delay(2700); // wait for flywheel to get up to speed again
  // shoot 2nd disc
  setDisc(0);
  indexer.set_value(true);
  delay(300);
  indexer.set_value(false);
  setFly(30);


  // turn to be parallel to the auton line
  chassis.set_turn_pid(235, 70);
  chassis.wait_drive();

  // cringer = true;
  // cringer = false;
  setIntake(100);

  // drive forwards while intaking 3 discs for driver control
  chassis.set_drive_pid(conv(135), 127, false, true);
  chassis.wait_drive();


  // setIntake(100);
  // turn to face other colour wheel
  chassis.set_turn_pid(292, 50);
  chassis.wait_drive();
 
  // delay(800);
  
  
  // drive into colour wheel
  chassis.set_drive_pid(conv(27), 70);
  chassis.wait_drive();

  // spin colour wheel
  setIntake(-100);
  delay(300);
  setIntake(0);
}
*/

void winpoint(){
  tuning_constants();
  setDisc(2);
  setFly(80.5);

  chassis.set_drive_pid(conv(2.5), 50);
  chassis.wait_drive(); 

  setIntake(-100); // turn colour wheel
  delay(75);
  setIntake(0);

  // drive backwards so turn doesnt collide with the wall
  chassis.set_drive_pid(conv(-7), 80);
  chassis.wait_drive(); 

  // turn to goal
  chassis.set_turn_pid(172.5, 75);
  chassis.wait_drive();


  delay(1500);

  // shoot 1st disc
  fireOneDisc();
  setDisc(1);
  setFly(80.5);

  delay(2000); // wait for flywheel to get up to speed again
  // shoot 2nd disc
  fireOneDisc();
  setDisc(0);
  setFly(30);


  chassis.set_turn_pid(270, 70);
  chassis.wait_drive();

  setIntake(100);

  chassis.set_drive_pid(conv(38), 127, false, true);
  chassis.wait_drive();

  chassis.set_turn_pid(210, 50);
  chassis.wait_drive();

  chassis.set_drive_pid(conv(55), 127, false, true);
  chassis.wait_drive();

  chassis.set_turn_pid(245, 50);
  chassis.wait_drive();

  chassis.set_drive_pid(conv(50), 127, false, true);
  chassis.wait_drive();
  
  chassis.set_turn_pid(295, 50);
  chassis.wait_drive();

  setIntake(0);
  
  // drive into colour wheel
  chassis.set_drive_pid(conv(23), 70);
  chassis.wait_drive();

  // spin colour wheel
  setIntake(-100);
  delay(150);
  setIntake(0);
}

void halfWPright(){
  tuning_constants();

  setFly(100); // spin up flywheel instantly

  chassis.set_drive_pid(45, 70); // drive closer to the centre line to shoot
  chassis.wait_drive();

  fireOneDisc();
  delay(3000); // wait for flywheel to get up to speed
  // shoot 2nd disc
  fireOneDisc();
  setFly(30); //idle flywheel; easier to ramp up speed for next shot

  chassis.set_turn_pid(90, 40); // turn to be parallel with the centre line
  chassis.wait_drive();

  // drive forwards
  // turn right
  // spin wheel
}

void halfWPleft(){
  tuning_constants();

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