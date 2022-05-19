#include "main.h"
#include "globals.hpp"
using namespace pros;

Controller controller(E_CONTROLLER_MASTER);

// drive motors
// change gearset when motors are changed
// blue: 06 // green: 18 // red: 36
Motor leftF(15, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_COUNTS);
Motor leftB(14, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_COUNTS);
Motor rightF(10, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_COUNTS);
Motor rightB(17, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_COUNTS);

// tracking wheel encoders
// 1 is A; 2 is B; 3 is C; etc..
ADIEncoder leftT(1, 2, false);
ADIEncoder rightT(3, 4, false);
ADIEncoder auxT(5, 6, false);

// inertial sensor
Imu imu(7);

double radToDeg(double rad){
  return rad*180/PI;
}

double degToRad(double deg){
  return deg*PI/180;
}

double inToEnc(double inches){
  return inches/(PI*driveWheelDiam)*ticksPerRev;
}
