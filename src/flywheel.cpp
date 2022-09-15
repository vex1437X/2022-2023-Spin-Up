#include "flywheel.hpp"
#include "main.h"
using namespace ez;

Motor flymotor1(14, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_COUNTS);
Motor flymotor2(15, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_COUNTS);

int flypct = 0;
bool flytoggle = true;
bool flytoggle1 = true;

void setFly(int percent){
  // percent to voltage
  int voltage = percent*1.27;
  // -127 to +127
  flymotor1.move(voltage);
  flymotor2.move(voltage);
}

int getFlyVolt(){
  return round(((flymotor1.get_voltage()/1.27)+(flymotor2.get_voltage()/1.27))/2);
}

void setflypct(int set){
	flypct = set;
}

void flywheelControl(){
  if (master.get_digital(E_CONTROLLER_DIGITAL_L1)){
        if (flytoggle == true){
            flypct = 90;
            flytoggle = false;
        } else if (flytoggle == false){
            // set back to idle
            flypct = 30;
            flytoggle = true;
        }
        delay(200);
    }

    if (master.get_digital(E_CONTROLLER_DIGITAL_L2)){
        if (flytoggle1 == true){
            flypct = 70;
            flytoggle1 = false;
        } else if (flytoggle1 == false){
            // set back to idle
            flypct = 30;
            flytoggle1 = true;
        }
        delay(200);
    }
    setFly(flypct);
}

int getFly(){
  return flypct;
}
