#include "main.h"
#include "drive.hpp"
using namespace pros;

Controller controller();
Motor leftF(15);
Motor leftB(14);
Motor rightF(10);
Motor rightB(17);

int power;
int turn;
int strafe;

int front_l_speed;
int front_r_speed;
int back_l_speed;
int back_r_speed;

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
  return (abs(leftT.get_value()) +
          abs(rightT.get_value()) +
          abs(leftT.get_value())) / 3;
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
  // double leftJoystickY = controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y); // power
  // double leftJoystickX = controller.get_analog(E_CONTROLLER_ANALOG_LEFT_X); // strafe
  // double rightJoystickY = controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
  // double rightJoystickX = controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_X); // turn
  //
  // // X drive
  // if (abs(leftJoystickY) < 10){ // change if deadzone is wrong
  //   leftJoystickY = 0;
  // }
  // if (abs(leftJoystickX) < 10){ // change if deadzone is wrong
  //   leftJoystickY = 0;
  // }
  // if (abs(rightJoystickX) < 10){ // change if deadzone is wrong
  //   leftJoystickY = 0;
  // }
  // // setDrive(int leftFv, int leftBv, int rightFv, int rightBv)
  // setDrive(leftJoystickY + rightJoystickX + leftJoystickX, // Left Front
  //          leftJoystickY + rightJoystickX - leftJoystickX,       // Left Back
  //          leftJoystickY - rightJoystickX - leftJoystickX,      // Right Front
  //          leftJoystickY - rightJoystickX + leftJoystickX     // Right Back

        // leftJoystickY + rightJoystickX + leftJoystickX,
        // leftJoystickY + rightJoystickX - leftJoystickX,
        // leftJoystickY - rightJoystickX - leftJoystickX,
        // leftJoystickY - rightJoystickX + leftJoystickX

  power = controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
  strafe = controller.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
  turn = controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);

  /* Equations for X-Drive */
  front_l_speed = power + turn + strafe;
  front_r_speed = power - turn - strafe;
  back_l_speed = power + turn - strafe;
  back_r_speed = power - turn + strafe;

  /* Set the motor velocities */
  leftF.move_velocity(front_l_speed);
  rightF.move_velocity(front_r_speed);
  leftB.move_velocity(back_l_speed);
  rightB.move_velocity(back_r_speed);
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
    setDrive(voltage*direction-(imu.get_heading()*10),
             voltage*direction+(imu.get_heading()*10));
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
