#include "main.h"
#include "flywheel.hpp"
using namespace pros;

void setFly(int voltage){
  // inputs in voltage
  // -127 to +127
  flymotor1.move(voltage);
  flymotor2.move(voltage);
}
