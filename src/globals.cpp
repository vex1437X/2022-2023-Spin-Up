#include "main.h"
#include "globals.hpp"
using namespace pros;

Controller controller(E_CONTROLLER_MASTER);

// drive motors
// change gearset when motors are changed
// blue: 06 // green: 18 // red: 36
Motor leftF(6, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_COUNTS);
Motor leftB(12, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_COUNTS);
Motor rightF(20, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_COUNTS);
Motor rightB(10, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_COUNTS);

Motor flymotor1(1, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_COUNTS);
Motor flymotor2(2, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_COUNTS);

// tracking wheel encoders
// 1 is A; 2 is B; 3 is C; etc..
// ADIEncoder leftT(2, 1, false);
// ADIEncoder rightT(7, 8, false);
// ADIEncoder auxT(5, 6, false);

double radToDeg(double rad){
  return rad*180/PI;
}

double degToRad(double deg){
  return deg*PI/180;
}

double inToEnc(double inches){
  return inches/(PI*trackWheelDiam)*trackTicksPerRev;
}

double encToIn(double enc){
  return enc*(PI*trackWheelDiam)/trackTicksPerRev;
}
