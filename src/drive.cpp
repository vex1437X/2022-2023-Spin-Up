#include "main.h"
#include "drive.hpp"
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

double avgTrackEncoders(){
  return (abs(leftT.get_value()) +
         abs(rightT.get_value()) +
         abs(auxT.get_value())) / 3;
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
  double scaleFactor = 1.575;
  leftF.move_velocity(leftJoystickY*scaleFactor);
  leftB.move_velocity(leftJoystickY*scaleFactor);
  rightF.move_velocity(rightJoystickY*scaleFactor);
  rightB.move_velocity(rightJoystickY*scaleFactor);
}

void driveFor(double inches, double percent){
  // percent to voltage conversion
  double voltage = percent*1.27;
  double targetEnc = inToEnc(inches);

  setDrive(voltage, voltage);

  //   _   _  ____ _______   _____   ____  _   _ ______ 
  //  | \ | |/ __ \__   __| |  __ \ / __ \| \ | |  ____|
  //  |  \| | |  | | | |    | |  | | |  | |  \| | |__   
  //  | . ` | |  | | | |    | |  | | |  | | . ` |  __|  
  //  | |\  | |__| | | |    | |__| | |__| | |\  | |____ 
  //  |_| \_|\____/  |_|    |_____/ \____/|_| \_|______|
                                                   
                                                   
  // while (deltatotalenc < targetEnc){
  //   delay(10);
  // }

  delay(100);
  resetDrive();
}

void driveTo(double X, double Y, double percent){
  // percent to voltage conversion
  double voltage = percent*1.27;

  double deltX = X-getX();
  double deltY = Y-getY();
  double theta;

  // determine direction
  int directionX;

  if (deltX < 0){
    directionX = -1;
  } else if (deltX > 0){
    directionX = 1;
  } else if (directionX == 0){ 
    directionX = 0;
  }

  int directionY;

  if (deltY < 0){
    directionY = -1;
  } else if (deltY > 0){
    directionY = 1;
  } else if (directionY == 0){
    directionY = 0;
  }

  // get the distance needed to reach target
  double d = sqrt(pow(deltX, 2) + pow(deltY, 2));

  // determine orientation
  if (directionX == 1 && directionY == 0){
    theta = 90;
  } else if (directionX == -1 && directionY == 0){
    theta = 270;
  } else if (directionX == 0 && directionY == 1){
    theta = 0;
  } else if (directionX == 0 && directionY == -1){
    theta = 180;
  } else if (directionX == 1 && directionY == 1){
    theta = atan(deltY/deltX);
  } else if (directionX == -1 && directionY == 1){
    theta = atan(deltY/deltX);
  } else if (directionX == 1 && directionY == -1){
    theta = atan(deltX/deltY);
  } else if (directionX == -1 && directionY == -1){
    theta = atan(deltX/deltY);
  }

  // turn to target
  turnTo(theta, 20);

  // drive to target
  driveFor(d, percent);
  
  /*
  if (directionX == 1 && directionY == 0){
    setDrive(voltage, voltage);
    while(getX() < X-1 && getX() < getX() < X+1){
      delay(10);
    }
  } else if (directionX == -1 && directionY == 0){
    setDrive(voltage, voltage);
    while(getX() > X-1 && getX() > X+1){
      delay(10);
    }
  } else if (directionX == 0 && directionY == 1){
    setDrive(voltage, voltage);
    while(getY() < Y-1 && getY() < Y+1){
      delay(10);
    }
  } else if (directionX == 0 && directionY == -1){
    setDrive(voltage, voltage);
    while(getY() > Y-1 && getY() > Y+1){
      delay(10);
    }
  } else if (directionX == 1 && directionY == 1){
    setDrive(voltage, voltage);
    while(getX() < X-1 && getX() < X+1){
      delay(10);
    }
  } else if (directionX == -1 && directionY == 1){
    setDrive(voltage, voltage);
    while(getX() > X-1 && getX() > X+1){
      delay(10);
    }
  } else if (directionX == 1 && directionY == -1){
    setDrive(voltage, voltage);
    while(getX() < X-1 && getX() < X+1){
      delay(10);
    }
  } else if (directionX == -1 && directionY == -1){
    setDrive(voltage, voltage);
    while(getX() > X-1 && getX() > X+1){
      delay(10);
    }
  }
  */

  delay(100);
  resetDrive(); // stop all drive motors
}

void turnTo(double degrees, double percent){
  // percent to voltage conversion
  double voltage = percent*1.27;

  // orientation locked to (0,359.999...)
  printf("Orien %f \n", getCurrentOrientation());
  printf("Deg %f \n", degrees);

  // determine direction
  int direction = 0;
  /*
  double currOrien = 0;
  if (first == true){
    if (currOrien-degrees < 0){
      direction = -1;
      printf("Direction %d \n", -1);
    } else if (currOrien-degrees > 0){
      direction = 1;
      printf("DirectionBye %d \n", 1);
    }
    first = false;
  } else if (direction == false){
  */
  if (direction == false){ // comment out when using first & currOrien; only when Orientation starts off as 360 and not 0 deg
    if (getCurrentOrientation()-degrees < 0){
      direction = -1;
    } else if (getCurrentOrientation()-degrees > 0){
      direction = 1;
    }
  }

  /*
  // determine direction
  int direction = 0;
  if (degrees > getCurrentOrientation()){
    direction = 1;
  } else if (degrees < getCurrentOrientation()){
    direction = -1;
  } else{
    direction = 0;
  }
  // direction = fabs(degrees) / degrees; // direction = -1 when degrees is negative & +1 when degrees is positive
  */

 if (getCurrentOrientation() == degrees){
   return;
 }
 
  if (direction == -1){
    // turning the drivetrain
    setDrive(voltage*direction, -voltage*direction);
    while (getCurrentOrientation()-1 > degrees && getCurrentOrientation()+1 > degrees){
      printf("nOrientation: %f \n", getCurrentOrientation());
      delay(10);
    }

    delay(100);

    // overshoot correction
    if(getCurrentOrientation()-.5 < degrees && getCurrentOrientation()+.5 < degrees){
      setDrive(-voltage*direction*0.8, voltage*direction*0.8);
      while(getCurrentOrientation()-.5 < degrees && getCurrentOrientation()+.5 < degrees){
        printf("nOrientation1: %f \n", getCurrentOrientation());
        delay(10);
      }
    }

    // undershoot correction
    else if(getCurrentOrientation()-.5 > degrees && getCurrentOrientation()+.5 > degrees){
      setDrive(voltage*direction*0.8, -voltage*direction*0.8);
      while(getCurrentOrientation()-.5 > degrees && getCurrentOrientation()+.5 > degrees){
        printf("nOrientation2: %f \n", getCurrentOrientation());
        delay(10);
      }
    }
  } 
  else if (direction == 1){
    // turning the drivetrain
    setDrive(voltage*direction, -voltage*direction);
    while (!(getCurrentOrientation()-1 < degrees && getCurrentOrientation()+1 > degrees)){
      printf("pOrientation: %f \n", getCurrentOrientation());
      delay(10);
    }

    delay(100);

    // overshoot correction
    if(getCurrentOrientation()-.5 > degrees && getCurrentOrientation()+.5 > degrees){
      setDrive(-voltage*direction*0.8, voltage*direction*0.8);
      while(getCurrentOrientation()-.5 > degrees && getCurrentOrientation()+.5 > degrees){
        printf("pOrientation1: %f \n", getCurrentOrientation());
        delay(10);
      }
    }

    // undershoot correction
    else if(getCurrentOrientation()-.5 < degrees && getCurrentOrientation()+.5 < degrees){
      setDrive(voltage*direction*0.8, -voltage*direction*0.8);
      while(getCurrentOrientation()-.5 < degrees && getCurrentOrientation()+.5 < degrees){
        printf("pOrientation2: %f \n", getCurrentOrientation());
        delay(10);
      }
    }
  }
  resetDrive(); // stops all drive motors
}
