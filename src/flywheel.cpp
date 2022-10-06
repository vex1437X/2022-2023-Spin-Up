#include "flywheel.hpp"
#include "main.h"
using namespace ez;

Motor flymotor1(14, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_COUNTS);
Motor flymotor2(15, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_COUNTS);

double flypct = 0;
bool flytoggle = false;
bool flytoggle1 = false;

void setFly(double percent){
  /*
  // percent to voltage
  int voltage = percent*1.27;
  // -127 to +127
  flymotor1.move(voltage);
  flymotor2.move(voltage);
  */
 
  // percent to turbo motor gearset (600rpm)
  int tb = percent*6;
  // -600 to 600
  flymotor1.move_velocity(tb);
  flymotor2.move_velocity(tb);
}

int getFlyVolt(){
  return round(((flymotor1.get_voltage()/1.27)+(flymotor2.get_voltage()/1.27))/2);
}

void setflypct(int set){
	flypct = set;
}

void flywheelControl(){
  // flywheel toggle 85%
  if (master.get_digital(E_CONTROLLER_DIGITAL_L2)){
    if (flytoggle == false){
        flypct = 85;
        flytoggle = true;
    } else if (flytoggle == true){
        // set back to idle
        flypct = 30;
        flytoggle = false;
    }
    delay(250);
  }
  // flywheel toggle 85%
  if (master.get_digital(E_CONTROLLER_DIGITAL_L1)){
    if (flytoggle1 == false){
        flypct = 85;
        flytoggle1 = true;
    } else if (flytoggle1 == true){
        // set back to idle
        flypct = 30;
        flytoggle1 = false;
    }
    delay(250);
  }
  setFly(flypct);
}

int getFly(){
  return flypct;
}
