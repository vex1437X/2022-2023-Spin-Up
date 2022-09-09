#pragma once
#include "main.h"
using namespace pros;

extern Controller controller;

// drive motors
extern Motor leftF;
extern Motor leftB;
extern Motor rightF;
extern Motor rightB;

extern Motor flymotor1;
extern Motor flymotor2;

// tracking encoders
// extern ADIEncoder leftT;
// extern ADIEncoder rightT;
// extern ADIEncoder auxT;

double radToDeg(double rad);
double degToRad(double deg);
double inToEnc(double inches);
double encToIn(double enc);

// not checked
#define trackWheelDiam    3.25 // inches
#define trackWheelRad     driveWheelDiam/2
#define trackTicksPerRev  360
#define trackCirc         PI*trackWheelDiam

#define driveWheelDiam    3.25 // inches
#define driveWheelRad     driveWheelDiam/2


#define ticksPerRev       300
  // 1800 ticks/rev with 36:1 gears :: RED
  // 900 ticks/rev with 18:1 gears :: GREEN
  // 300 ticks/rev with 6:1 gears :: BLUE

#define PI              3.141592653589793238462643383279