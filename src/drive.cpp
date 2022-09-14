#include "main.h"
#include "drive.hpp"
#include "pros/misc.h"
using namespace pros;

bool first = true;

void setDrive(int left, int right){
  // inputs in voltage
  // -127 to +127
  leftF.move(left);
  leftB.move(left);
  rightF.move(right);
  rightB.move(right);
}

void setDrive(int leftFv, int leftBv, int rightFv, int rightBv){
  // inputs in voltage
  // -127 to +127
  leftF.move(leftFv);
  leftB.move(leftBv);
  rightF.move(rightFv);
  rightB.move(rightBv);
}

void resetDrive(){setDrive(0, 0);}

void resetDriveEncoders(){
  leftF.tare_position();
  leftB.tare_position();
  rightF.tare_position();
  rightB.tare_position();
}

double avgDriveEncoders(){
  return (fabs(leftF.get_position()) +
         fabs(leftB.get_position()) +
         fabs(rightF.get_position()) +
         fabs(rightB.get_position())) / 4;
}

void driveCoast(){
  leftF.set_brake_mode(E_MOTOR_BRAKE_COAST);
  leftB.set_brake_mode(E_MOTOR_BRAKE_COAST);
  rightF.set_brake_mode(E_MOTOR_BRAKE_COAST);
  rightB.set_brake_mode(E_MOTOR_BRAKE_COAST);
}

void driveBrake(){
  leftF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  leftB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  rightF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  rightB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
}

void driverControl(){
  int leftJoystickY = controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
  int rightJoystickY = controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);

  // Regular tank drive

  // left joystick deadzone
  if (abs(leftJoystickY) < 6){ // change if deadzone is wrong
    leftJoystickY = 0;
  }
  // right joystick deadzone
  if (abs(rightJoystickY) < 6){ // change if deadzone is wrong
    rightJoystickY = 0;
  }

  // Set the motor velocities
  // RED: factor = 0.78742 || GREEN: factor = 1.575 || BLUE: factor = 4.725
  double scaleFactor = 0;
  if (controller.get_digital(E_CONTROLLER_DIGITAL_R2)){
    scaleFactor = 4.725/3;
  } else{
    scaleFactor = 4.725;
  }
  leftF.move_velocity(leftJoystickY*scaleFactor);
  leftB.move_velocity(leftJoystickY*scaleFactor);
  rightF.move_velocity(rightJoystickY*scaleFactor);
  rightB.move_velocity(rightJoystickY*scaleFactor);
}

void driveFor(double inches, double percent){
  resetDriveEncoders();
  // percent to voltage conversion
  double voltage = percent*1.27;
  inches *= 1.52;
  double targetEnc = inToEnc(inches);

  setDrive(voltage, voltage);
  while (avgDriveEncoders() < targetEnc - inToEnc(.5)){
    delay(10);
  }
  setDrive(-voltage/4, -voltage/4);
  while (avgDriveEncoders() > targetEnc + inToEnc(.5)){
    delay(10);
  }
  delay(50);
  resetDrive();
}