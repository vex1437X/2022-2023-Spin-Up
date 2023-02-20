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

void elims_left_halfwp(){
  illPIDurmom();
  // Back up into colour wheel
  chassis.set_drive_pid(-3, 127);
  chassis.wait_drive();
  // Spin colour wheel
  set_colour(-100);
  delay(250);
  set_colour(0);
  // Drive outside of colour wheel zone
  chassis.set_drive_pid(3, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(-125, 127);
  chassis.wait_drive();

  // Drive closer to triple stack
  // chassis.set_drive_pid(-9, 100);
  set_intake(100);
  chassis.set_drive_pid(-25.5, 127);
  chassis.wait_drive();
  // Intake triple stack
  
  chassis.set_drive_pid(-41.5, 60);
  chassis.wait_drive();

  chassis.set_drive_pid(15, 127);
  chassis.wait_drive();
  // Turn to align catapult with goal
  chassis.set_turn_pid(95, 127);
  chassis.wait_drive();
  set_intake(0);

  fireCata();
}

void left_easy_single_colour(){
  illPIDurmom();
  // Back up into colour wheel
  chassis.set_drive_pid(-3, 127);
  chassis.wait_drive();
  // Spin colour wheel
  set_colour(-100);
  delay(250);
  set_colour(0);
  // Drive outside of colour wheel zone
  chassis.set_drive_pid(2, 100);
  chassis.wait_drive();
  // Turn towards goal
  chassis.set_turn_pid(-8, 100);
  chassis.wait_drive();
  // Shoot 2 discs
  chassis.set_drive_pid(4, 110);
  delay(100);
  superIdol();
  chassis.wait_drive();
}

void right_easy_single_colour(){
  illPIDurmom();
  chassis.set_drive_pid(-18, 110);
  chassis.wait_drive();

  chassis.set_turn_pid(90, 110);
  chassis.wait_drive();

  chassis.set_drive_pid(-8, 100);
  chassis.wait_drive();

  set_colour(-100);
  delay(150);
  set_colour(0);

  chassis.set_drive_pid(14, 110);
  chassis.wait_drive();

  chassis.set_turn_pid(98, 110);
  chassis.wait_drive();

  // Shoot 2 discs
  chassis.set_drive_pid(4, 110);
  set_intake(0);
  delay(100);
  superIdol();
  chassis.wait_drive();
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
  chassis.set_drive_pid(3, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(-125, 127);
  chassis.wait_drive();

  // Drive closer to triple stack
  // chassis.set_drive_pid(-9, 100);
  set_intake(100);
  chassis.set_drive_pid(-25.5, 127);
  chassis.wait_drive();
  // Intake triple stack
  
  chassis.set_drive_pid(-41.5, 60);
  chassis.wait_drive();

  chassis.set_drive_pid(10, 127);
  chassis.wait_drive();
  // Turn to align catapult with goal
  chassis.set_turn_pid(-37, 127);
  chassis.wait_drive();
  set_intake(0);
  // Shoot 3 discs
  chassis.set_drive_pid(15, 127);
  delay(320);
  superIdol();
  chassis.wait_drive();
  // Turn to be parallel with the centre line
  chassis.set_turn_pid(-129, 127);
  chassis.wait_drive();
  // Drive to the towards other colour wheel
  chassis.set_drive_pid(-80, 127);
  chassis.wait_drive();
  /*
  // Turn to be perpendicular to the colour wheel
  chassis.set_turn_pid(-90, 100);
  chassis.wait_drive();
  // Back up into the colour wheel
  chassis.set_drive_pid(-15, 100);
  delay(700);
  */
  set_colour(-100);
  delay(650);
  set_colour(0);
  // Drive outside of the colour wheel
  chassis.set_drive_pid(5, 127);
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

  chassis.set_drive_pid(7, 127);
  chassis.wait_drive();

  set_intake(100);
  chassis.set_turn_pid(219, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(-27, 90);
  chassis.wait_drive();

  chassis.set_turn_pid(105, 127);
  chassis.wait_drive();

  // Shoot 3 discs
  chassis.set_drive_pid(10, 127);
  delay(60);
  superIdol();
  chassis.wait_drive();

  chassis.set_drive_pid(-12, 127);
  chassis.wait_drive();

  delay(700);

  chassis.set_turn_pid(222, 127);
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
  pros::delay(250);
  set_colour(0);
  // Drive outside of colour wheel zone
  chassis.set_drive_pid(3, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(-125, 127);
  chassis.wait_drive();

  // Drive closer to triple stack
  // chassis.set_drive_pid(-9, 100);
  set_intake(100);
  chassis.set_drive_pid(-25.5, 110);
  chassis.wait_drive();
  // Intake triple stack
  
  chassis.set_drive_pid(-41.5, 60);
  chassis.wait_drive();

  chassis.set_drive_pid(10, 127);
  chassis.wait_drive();
  // Turn to align catapult with goal
  chassis.set_turn_pid(-38.5, 120);
  chassis.wait_drive();
  set_intake(0);
  chassis.set_drive_pid(-5, 120);
  chassis.wait_drive();
  delay(100);
  // Shoot 3 discs
  chassis.set_drive_pid(18, 127);
  pros::delay(60);
  superIdol();
  chassis.wait_drive();
  pros::delay(150);
  set_intake(100);
  chassis.set_turn_pid(-40, 127);
  chassis.wait_drive();
  
  chassis.set_drive_pid(-12, 90);
  chassis.wait_drive();

  chassis.set_turn_pid(-38.5, 127);
  chassis.wait_drive();
  // Shoot 3 discs
  chassis.set_drive_pid(12, 127);
  pros::delay(90);
  superIdol();
  chassis.wait_drive();
}

void skills() {
illPIDurmom();
  // Back up into colour wheel
  chassis.set_drive_pid(-3, 127);
  chassis.wait_drive();
  // Spin colour wheel
  set_colour(-100);
  delay(250);
  set_colour(0);
  // Drive outside of colour wheel zone
  chassis.set_drive_pid(5, 100);
  chassis.wait_drive();

  chassis.set_turn_pid(90, 100);
  chassis.wait_drive();

  chassis.set_drive_pid(-15, 100);
  chassis.wait_drive();

  chassis.set_turn_pid(45, 100);
  chassis.wait_drive();

  Expansion1.set_value(true);
}