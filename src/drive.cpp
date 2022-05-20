#include "main.h"
#include "drive.hpp"
using namespace pros;

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

double avgTrackEncoders(){
  return (fabs(leftT.get_value()) +
         fabs(rightT.get_value()) +
         fabs(auxT.get_value())) / 3;
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
  // RED: factor = 0.78742 || GREEN: factor = 0.5 || BLUE: factor = .1666667
  double scaleFactor = 0.5;
  leftF.move_velocity(leftJoystickY*scaleFactor);
  leftB.move_velocity(leftJoystickY*scaleFactor);
  rightF.move_velocity(rightJoystickY*scaleFactor);
  rightB.move_velocity(rightJoystickY*scaleFactor);
}

void driveFor(double inches, double percent){
  // percent to voltage conversion
  double voltage = percent*1.27;
  // determine direction
  int direction = fabs(inches) / inches; // direction = -1 when inches is negative & = +1 when inches is positive

  // reset drive encoders
  resetDriveEncoders();

  /*
  while(avgDriveEncoders() < fabs(inToEnc(inches))){
    setDrive(voltage*direction-(imu.get_heading()*10), voltage*direction+(imu.get_heading()*10));
    delay(10);
  }
  // overshoot correction
  if(avgDriveEncoders() > fabs(inToEnc(inches))){
    setDrive(-voltage*direction-(imu.get_heading()*10)*0.5, -voltage*direction+(imu.get_heading()*10)*0.5);
    while(avgDriveEncoders() > fabs(inToEnc(inches))){
      delay(10);
    }
  }
  delay(50);
  resetDrive(); // stops all drive motors
  */
}

void turnFor(double degrees, double percent){
  // percent to voltage conversion
  double voltage = percent*1.27;
  // determine direction
  int direction = fabs(degrees) / degrees; // direction = -1 when degrees is negative & +1 when degrees is positive

  /*

  // turning the drivetrain
  setDrive(voltage*direction, -voltage*direction);
  while(fabs(imu.get_heading()) < fabs(degrees) - 5){
    delay(10);
  }
  delay(150);

  // overshoot correction
  if(fabs(imu.get_heading()) > fabs(degrees)){
    setDrive(-voltage*direction*0.5, voltage*direction*0.5);
    while(fabs(imu.get_heading()) > fabs(degrees)){
      delay(10);
    }
  }

  // undershoot correction
  else if(fabs(imu.get_heading()) < fabs(degrees)){
    setDrive(voltage*direction*0.5, -voltage*direction*0.5);
    while(fabs(imu.get_heading()) < fabs(degrees)){
      delay(10);
    }
  }
  resetDrive(); // stops all drive motors
  */
}
