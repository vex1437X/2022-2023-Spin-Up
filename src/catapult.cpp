#include "catapult.hpp"
#include "main.h"
using namespace ez;

Motor catapult(14, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_COUNTS);

bool canFire1 = false;

bool canFire(){
  return canFire1;
}

void resetCata(){}

void cataControl(){
  if (master.get_digital(E_CONTROLLER_DIGITAL_L2)){
    
    delay(250);
    resetCata();
  }
}
