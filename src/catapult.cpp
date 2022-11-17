#include "catapult.hpp"
#include "main.h"
using namespace ez;

Motor catapult(14, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_COUNTS);

ADIDigitalIn cataLimit(3);

void setCata(int percent){
  // percent to voltage
  int voltage = percent*1.27;
  // -127 to +127
  catapult.move(voltage);
}

void cataFor(double sec, int percent){
  setCata(percent);
  delay(sec*1000);
  setCata(0);
}

void resetCata(){
  while(!cataLimit.get_value()) {
    setCata(-100);
  }
  setCata(0);
}

void fireCata(){
  cataFor(0.5, -100);
}

void cataControl(void*){
  while (true){
    if (master.get_digital(E_CONTROLLER_DIGITAL_L2)){
      fireCata();
      delay(600);
    }
    resetCata();
    delay(20);
  }
}
