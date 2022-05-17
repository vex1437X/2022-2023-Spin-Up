#include "main.h"
#include "drive.hpp"
using namespace pros;

void setDrive(int left, int right){
  // inputs in voltage
  // -127 to +127
  leftF = left;
  leftB = left;
  rightF = right;
  rightB = right;
}

void setDrive(int leftFv, int leftBv, int rightFv, int rightBv){
  // inputs in voltage
  // -127 to +127
  leftF = leftFv;
  leftB = leftBv;
  rightF = rightFv;
  rightB = rightBv;
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
          fabs(leftT.get_value())) / 3;
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
  int leftJoystickX = controller.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
  int rightJoystickY = controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
  int rightJoystickX = controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);

  // X drive
  if (abs(leftJoystickY) < 10){ // change if deadzone is wrong
    leftJoystickY = 0;
  }
  if (abs(leftJoystickX) < 10){ // change if deadzone is wrong
    leftJoystickY = 0;
  }
  if (abs(rightJoystickX) < 10){ // change if deadzone is wrong
    leftJoystickY = 0;
  }
  // setDrive(int leftFv, int leftBv, int rightFv, int rightBv)
  setDrive(leftJoystickY+leftJoystickX+rightJoystickX, // Left Front
    leftJoystickY-leftJoystickX+rightJoystickX,        // Left Back
    leftJoystickY-leftJoystickX-rightJoystickX,        // Right Front
    leftJoystickY+leftJoystickX-rightJoystickX);       // Right Back
}

void driveFor(double inches, double percent){
  // percent to voltage conversion
  double voltage = percent*1.27;
  // determine direction
  int direction = fabs(inches) / inches; // direction = -1 when inches is negative & = +1 when inches is positive

  // reset inertial sensor and drive encoders
  imu.tare();
  resetDriveEncoders();

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
}

void turnFor(double degrees, double percent){
  // percent to voltage conversion
  double voltage = percent*1.27;
  // determine direction
  int direction = fabs(degrees) / degrees; // direction = -1 when degrees is negative & +1 when degrees is positive

  imu.tare();

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
}
