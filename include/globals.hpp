#pragma once
#include "main.h"
using namespace pros;

extern Controller controller;

// drive motors
extern Motor leftF;
extern Motor leftB;
extern Motor rightF;
extern Motor rightB;

// tracking encoders
extern ADIEncoder leftT;
extern ADIEncoder rightT;
extern ADIEncoder auxT;

// inertial sensor
extern Imu imu;

// Optical/colour sensor
extern Optical optical_sensor;
c::optical_rgb_s_t rgb_value;

double radToDeg(double rad);
double degToRad(double deg);
double inToEnc(double inches);

#define driveWheelDiam  3.25             // inches
#define driveWheelRad   driveWheelDiam/2

#define ticksPerRev     1800
  // 1800 ticks/rev with 36:1 gears :: RED
  // 900 ticks/rev with 18:1 gears :: GREEN
  // 300 ticks/rev with 6:1 gears :: BLUE

// "blue" or "red"
#define allianceColour  "blue"

#define PI              3.141592653589793238462643383279 // pi constant
