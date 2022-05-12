#include "main.h"
#include "globals.hpp"
using namespace pros;

Controller controller(E_CONTROLLER_MASTER);

// drive motors
// change gearset when motors are changed
// blue: 06 // green: 18 // red: 36
Motor leftF(1, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);
Motor leftB(2, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);
Motor rightF(3, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_COUNTS);
Motor rightB(4, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_COUNTS);

// inertial sensor
Imu imu(7);

double inToEnc(double inches){
  return inches/(PI*driveWheelDiam)*ticksPerRev;
}
