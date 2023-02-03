#include "main.h"
#include "systems.hpp"
using namespace pros;

void none(){}

void illPIDurmom() {
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

void pid_tune(){

}

void left_wp() {
  illPIDurmom();
  // Back up into colour wheel
  chassis.set_drive_pid(-3, 127);
  chassis.wait_drive();
  // Spin colour wheel
  set_colour(-100);
  delay(700);
  set_colour(0);
  // Drive outside of colour wheel zone
  chassis.set_drive_pid(26, 80);
  chassis.wait_drive();
  // Turn to be parallel with the centre line
  chassis.set_turn_pid(45, 80);
  chassis.wait_drive();
  // Drive to the centre of the field
  chassis.set_drive_pid(50, 80);
  chassis.wait_drive();
  // Turn to align catapult with goal
  chassis.set_turn_pid(-45, 80);
  chassis.wait_drive();
  // Drive back a bit
  chassis.set_drive_pid(-12, 40);
  chassis.wait_drive();
  // Drive and shoot 2 discs
  chassis.set_drive_pid(12, 110);
  delay(200);
  superIdol();
  chassis.wait_drive();
  // Turn to be parallel with the centre line
  chassis.set_turn_pid(45, 80);
  chassis.wait_drive();
  // Drive to the towards other colour wheel
  chassis.set_drive_pid(50, 80);
  chassis.wait_drive();
  // Turn to be perpendicular to the colour wheel
  chassis.set_turn_pid(-90, 80);
  chassis.wait_drive();
  // Back up into the colour wheel
  chassis.set_drive_pid(-26, 80);
  chassis.wait_drive();
  // Spin colour wheel
  set_colour(-100);
  delay(700);
  set_colour(0);
  // Drive outside of the colour wheel
  chassis.set_drive_pid(5, 80);
  chassis.wait_drive();
}

void left_halfwp() {
  illPIDurmom();
}

void right_halfwp() { // allign in the middle of allowed section
  illPIDurmom();
  set_intake(100);
  // Intake middle disc
  chassis.set_drive_pid(-33, 80);
  chassis.wait_drive();
  // Align cata with goal
  
}