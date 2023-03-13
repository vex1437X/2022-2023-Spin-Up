#include "autons.hpp"
#include "main.h"
#include "systems.hpp"
using namespace pros;

void none(){}

void stl() {
  // chassis.set_slew_min_power(80, 80);
  // chassis.set_slew_distance(7, 7);
  // chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 0, 0, 0, 0);
  // chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  // chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  // chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  // chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}
// chassis.set_drive_pid(10, 127);
// superIdol();
// chassis.wait_drive();

void illPIDurmom() {
  chassis.set_pid_constants(&chassis.headingPID, 5, 0, 8, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.18, 0.001, 0, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 0.65, 0.0025, 0, 0);
}


void pid_tune(){
  illPIDurmom();
  chassis.set_turn_pid(180, 100);
  chassis.wait_drive();
}

void elims_right_halfwp(){
  illPIDurmom();
  chassis.set_drive_pid(-18, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(90, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(-8, 127);
  chassis.wait_drive();

  set_colour(-100);
  delay(150);
  set_colour(0);

  chassis.set_drive_pid(7, 127);
  chassis.wait_drive();

  set_intake(100);
  chassis.set_turn_pid(219, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(-27, 90);
  chassis.wait_drive();

  chassis.set_turn_pid(340, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(15, 90);
  chassis.wait_drive();

  fireCata();

  chassis.set_drive_pid(-15, 100);
  chassis.wait_drive();

  set_intake(100);

  chassis.set_turn_pid(219, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(-26, 90);
  chassis.wait_drive();

  pros::delay(1500);

  set_intake(0);
}

void left_wp() {
  illPIDurmom();
  // Back up into colour wheel
  chassis.set_drive_pid(-3, 127);
  chassis.wait_drive();
  // Spin colour wheel
  set_colour(-100);
  delay(250);
  set_colour(0);
  // Drive outside of colour wheel zone
  chassis.set_drive_pid(4, 127);
  chassis.wait_drive();

  // delay(25);

  chassis.set_pid_constants(&chassis.turnPID, 0.9, 0.004, 0, 0);


  chassis.set_turn_pid(-10, 127);
  delay(350);
  // chassis.wait_drive();

  illPIDurmom();

  // delay(25);

  chassis.set_drive_pid(9.75, 80);
  delay(20);
  superIdol();
  chassis.wait_drive();

  chassis.set_drive_pid(-3.75, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(-126, 127);
  chassis.wait_drive();

  // delay(1500); //  ******************************* remove this after 

  // Drive closer to triple stack
  set_intake(100);
  chassis.set_drive_pid(-22, 90);
  chassis.wait_drive();

  // Intake triple stack
  chassis.set_drive_pid(-21.5, 45);
  chassis.wait_drive();

  // Turn to align catapult with goal
  chassis.set_turn_pid(-34.6, 127);
  chassis.wait_drive();
  set_intake(-100);
  // Shoot 3 discs
  chassis.set_drive_pid(9.75, 70);
  // delay(10);
  superIdol();
  chassis.wait_drive();

  chassis.set_drive_pid(-8, 127);
  chassis.wait_drive();
  // Turn to be parallel with the centre line
  chassis.set_turn_pid(-134, 127);
  chassis.wait_drive();

  set_intake(90);

  delay(50);


  // Drive to the towards other colour wheel
  chassis.set_drive_pid(-82.5, 110);
  delay(1700);
  set_colour(-100);

  chassis.wait_drive();
  delay(30);
  set_colour(0);

  // Drive outside of the colour wheel
  // chassis.set_drive_pid(20, 127);

  // chassis.set_drive_pid(31, 127);
  chassis.set_drive_pid(39, 127);
  
  delay(250);
  set_intake(100);
  chassis.wait_drive();

  // chassis.set_turn_pid(-65, 127);
  chassis.set_turn_pid(-60, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(7.75, 127);
  delay(5);
  superIdol();
  chassis.wait_drive();
}

void right_halfwp(){
  illPIDurmom();
  chassis.set_drive_pid(-18, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(90, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(-8, 127);
  chassis.wait_drive();

  set_colour(-100);
  delay(210);
  set_colour(0);

  

  chassis.set_drive_pid(8, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(84, 127);
  delay(200);

  chassis.set_drive_pid(9.75, 80);
  delay(20);
  superIdol();
  chassis.wait_drive();

  chassis.set_drive_pid(-11, 80);
  chassis.wait_drive();

  chassis.set_turn_pid(84, 127);
  chassis.wait_drive();

  set_intake(100);
  chassis.set_turn_pid(219, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(-27, 90);
  chassis.wait_drive();

  chassis.set_turn_pid(106, 127);
  chassis.wait_drive();

  // Shoot 3 discs
  chassis.set_drive_pid(7.5, 127);
  delay(20);
  superIdol();
  chassis.wait_drive();

  chassis.set_drive_pid(-12, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(87, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(-25, 94);
  chassis.wait_drive();

  chassis.set_drive_pid(39.5, 127);
  chassis.wait_drive();
}

void left_halfwp() {
  illPIDurmom();
  // Back up into colour wheel
  chassis.set_drive_pid(-3, 127);
  chassis.wait_drive();
  // Spin colour wheel
  set_colour(-100);
  delay(250);
  set_colour(0);
  // Drive outside of colour wheel zone
  chassis.set_drive_pid(4, 127);
  chassis.wait_drive();


  chassis.set_pid_constants(&chassis.turnPID, 0.9, 0.004, 0, 0);


  chassis.set_turn_pid(-11, 127);
  delay(380);

  illPIDurmom();


  chassis.set_drive_pid(9.75, 86);
  delay(20);
  superIdol();
  chassis.wait_drive();

  chassis.set_drive_pid(-3.75, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(-125, 127);
  chassis.wait_drive();

  // Drive closer to triple stack
  chassis.set_drive_pid(-22, 95);
  chassis.wait_drive();

  set_intake(100);
  // Intake triple stack
  chassis.set_drive_pid(-21.5, 45);
  chassis.wait_drive();

  // Turn to align catapult with goal
  chassis.set_turn_pid(-34.6, 127);
  chassis.wait_drive();
  set_intake(-100);
  // Shoot 3 discs
  chassis.set_drive_pid(9.75, 81);
  // delay(10);
  superIdol();
  chassis.wait_drive();

  set_intake(-100);

  chassis.set_drive_pid(-8, 127);
  chassis.wait_drive();
  
  chassis.set_turn_pid(-78, 127);
  chassis.wait_drive();

  set_intake(100);

  chassis.set_drive_pid(-15, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(8, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(-33.5, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(9, 110);
  // delay(10);
  superIdol();
  chassis.wait_drive();
}

void skills() {
  illPIDurmom();
  // start with 2 preload

  // Back up into colour wheel
  chassis.set_drive_pid(-3, 127);
  chassis.wait_drive();
  // Spin 1st colour wheel
  set_colour(-100);
  delay(400);
  set_colour(0);
  // Drive outside of colour wheel zone
  chassis.set_drive_pid(8, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(110, 127);
  chassis.wait_drive();

  set_intake(100);

  chassis.set_drive_pid(-12, 127);
  chassis.wait_drive();

  // 3 discs in

  chassis.set_turn_pid(90, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(-17.5, 127);
  chassis.wait_drive();

  // spin 2nd colour wheel
  set_intake(-100);
  delay(400);
  set_intake(0);

  chassis.set_drive_pid(8, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(-3.5, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(77, 127); // drive up to goal
  chassis.wait_drive();

  chassis.set_turn_pid(25, 127);
  chassis.wait_drive();

  fireCata(); // shoot 3


  chassis.set_turn_pid(-4, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(-16.5, 127); // back out of goal
  chassis.wait_drive();

  chassis.set_turn_pid(-89, 127);
  chassis.wait_drive();

  // drive back and intake 3 discs close to goal
  set_intake(100);

  chassis.set_drive_pid(-30, 60);
  chassis.wait_drive();

  chassis.set_drive_pid(29, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(10, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(21, 127); // drive into goal
  chassis.wait_drive();

  set_intake(0);

  fireCata(); // shoot 3

  /*  counter: 6 disc - 2 colour  */

  chassis.set_drive_pid(22.8, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(-91, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(-34, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(1, 127);
  chassis.wait_drive();

  set_intake(100);

  chassis.set_drive_pid(-30, 60);
  chassis.wait_drive();

  chassis.set_drive_pid(30, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(-100, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(21, 127); // drive into goal
  chassis.wait_drive();

  set_intake(0);

  fireCata(); // shoot 3

  /*  counter: 9 disc - 2 colour  */

  chassis.set_drive_pid(-21, 127); // drive out of goal
  chassis.wait_drive();

  chassis.set_turn_pid(-53, 127);
  chassis.wait_drive();

  set_intake(100);

  chassis.set_drive_pid(-20, 127); // drive to triple stack
  chassis.wait_drive();

  chassis.set_drive_pid(-27, 80);
  chassis.wait_drive();

  chassis.set_drive_pid(47, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(-100, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(21, 127); // drive into goal
  chassis.wait_drive();

  fireCata(); // shoot 3

  /*  counter: 12 disc - 2 colour  */

}