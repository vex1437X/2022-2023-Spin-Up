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
  delay(150);
  set_colour(0);

  chassis.set_drive_pid(7, 127);
  chassis.wait_drive();

  set_intake(100);
  chassis.set_turn_pid(219, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(-27, 90);
  chassis.wait_drive();

  chassis.set_turn_pid(107, 127);
  chassis.wait_drive();

  // Shoot 2 discs
  chassis.set_drive_pid(13, 127);
  set_intake(100);
  delay(390);
  superIdol();
  chassis.wait_drive();

  chassis.set_drive_pid(-14, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(222, 127);
  chassis.wait_drive();


  chassis.set_drive_pid(-38.5, 94);
  chassis.wait_drive();

  chassis.set_turn_pid(132, 127);
  chassis.wait_drive();

  // chassis.set_drive_pid(-6, 100);
  // chassis.wait_drive();

  // delay(300);

  // Shoot 3 discs
  chassis.set_drive_pid(13, 127);
  set_intake(0);
  delay(320);
  superIdol();
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
  delay(310);
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


void old_right_halfwp() { // allign in the middle of allowed section
  illPIDurmom();
  set_intake(100);
  // Intake middle disc
  chassis.set_drive_pid(-33, 110);
  chassis.wait_drive();
  // Align cata with goal
  chassis.set_turn_pid(-148, 120);
  chassis.wait_drive();
  // Drive and shoot 2 discs
  set_intake(0);
  chassis.set_drive_pid(14, 120);
  delay(300);
  superIdol();
  chassis.wait_drive();
  // Back-up from centre line
  chassis.set_drive_pid(-10, 120);
  chassis.wait_drive();
  // Align intake with single disc
  chassis.set_turn_pid(-50, 120);
  chassis.wait_drive();
  // Drive and intake 1st disc
  set_intake(100);
  chassis.set_drive_pid(-20.4, 90);
  chassis.wait_drive();
  // Align 2nd disc
  chassis.set_turn_pid(-180, 120);
  chassis.wait_drive();
  // Drive and intake 2nd & 3rd disc
  chassis.set_drive_pid(-37, 120);
  chassis.wait_drive();

  chassis.set_drive_pid(35, 120);
  chassis.wait_drive();


  // Align to goal
  chassis.set_turn_pid(-122, 127);
  chassis.wait_drive();
  // Drive and shoot 2 discs
  set_intake(0);
  chassis.set_drive_pid(13, 127);
  delay(300);
  superIdol();
  chassis.wait_drive();
  // Align to be anti-parallel with the centre line
  chassis.set_turn_pid(-222, 127);
  chassis.wait_drive();
  // Drive towards colour wheel
  chassis.set_drive_pid(-68, 127);
  chassis.wait_drive();
  // Align to be perpendicular to the colour wheel
  chassis.set_turn_pid(-180, 120);
  chassis.wait_drive();
  // Drive into colour wheel
  chassis.set_drive_pid(-40, 120);
  chassis.wait_drive();
  // Spin colour wheel
  set_colour(-100);
  delay(250);
  set_colour(0);
  // Drive outside of colour wheel zone
  chassis.set_drive_pid(4.5, 120);
  chassis.wait_drive();
}

void old_left_wp() {
  illPIDurmom();
  // Back up into colour wheel
  chassis.set_drive_pid(-3, 127);
  chassis.wait_drive();
  // Spin colour wheel
  set_colour(-100);
  delay(350);
  set_colour(0);
  // Drive outside of colour wheel zone
  chassis.set_drive_pid(8, 100);
  chassis.wait_drive();
  // Turn to be parallel with the centre line
  set_intake(-100);
  chassis.set_turn_pid(-134.5, 100);
  chassis.wait_drive();
  // Drive to the centre of the field
  chassis.set_drive_pid(-65, 100);
  chassis.wait_drive();
  // Turn to align catapult with goal
  chassis.set_turn_pid(-45, 100);
  chassis.wait_drive();
  // Drive back a bit
  chassis.set_drive_pid(-12, 80);
  chassis.wait_drive();
  // Drive and shoot 2 discs
  chassis.set_drive_pid(12, 120);
  delay(200);
  superIdol();
  chassis.wait_drive();
  // Drive back a bit
  chassis.set_drive_pid(-6, 80);
  chassis.wait_drive();
  // Turn to be parallel with the centre line
  chassis.set_turn_pid(-137.5, 100);
  chassis.wait_drive();
  // Drive to the towards other colour wheel
  chassis.set_drive_pid(-55, 100);
  chassis.wait_drive();
  // Turn to be perpendicular to the colour wheel
  chassis.set_turn_pid(-90, 100);
  chassis.wait_drive();
  // Back up into the colour wheel
  chassis.set_drive_pid(-32, 100);
  chassis.wait_drive();
  // Spin colour wheel
  set_colour(-100);
  delay(700);
  set_colour(0);
  // Drive outside of the colour wheel
  chassis.set_drive_pid(5, 100);
  chassis.wait_drive();
}