#include "flywheel.hpp"
#include "main.h"
using namespace ez;

Motor flymotor1(14, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_COUNTS);
Motor flymotor2(15, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_COUNTS);

double flypct = 0;
bool flytoggle = false;
bool flytoggle1 = false;

double autpct = 0;

bool canFire1 = false;

bool canFire(){
  return canFire1;
}

void flyCalc(void*){
  while (true){
    // * voltage/rpm correction *           Use task for this version of setFly
    // percent to miliVolts
    double targetRPM = 600*autpct; // 600 is max internal rpm :: total rpm of system is 600*5/1 = 3000 rpm
    double mV = 12000*autpct;       // 12000 is max mV          20 mV : 1 rpm
    double exMV = 0;                 // extra mV needed to be added to flywheel
    // canFire1 = false;
    if (getActRPM() < targetRPM-5 || getActRPM() > targetRPM+5) {exMV = 10*(targetRPM - getActRPM()); canFire1 = false;}
    else{canFire1 = true;}

    flymotor1.move_voltage(mV + exMV);
    flymotor2.move_voltage(mV + exMV);
  }
}

void setFlyAuto(double percent){
  autpct = percent/100;
}

void setFlyDriver(double percent){
  //  * move voltage *
  // percent to voltage
  int voltage = percent*1.27;
  // -127 to +127
  flymotor1.move(voltage);
  flymotor2.move(voltage);

  /* move velocity PID
  // percent to RPM
  double RPM = percent * 6;
  // -600 to +600 RPM
  flymotor1.move_velocity(RPM);
  flymotor2.move_velocity(RPM);
  */
}

double getActRPM(){
  return (flymotor1.get_actual_velocity()+flymotor2.get_actual_velocity())/2;
}

int getFlyVolt(){
  return round(((flymotor1.get_voltage()/1.27)+(flymotor2.get_voltage()/1.27))/2);
}

void setflypct(int set){
	flypct = set;
}

void flywheelControl(){
  // flywheel toggle 84%
  // single
  if (master.get_digital(E_CONTROLLER_DIGITAL_L2)){
    if (flytoggle == false){
        flypct = 84;
        flytoggle = true;
    } else if (flytoggle == true){
        // set back to idle
        flypct = 30;
        flytoggle = false;
    }
    delay(250);
  }
  // flywheel toggle 82%
  // triple
  if (master.get_digital(E_CONTROLLER_DIGITAL_L1)){
    if (flytoggle1 == false){
        flypct = 82;
        flytoggle1 = true;
    } else if (flytoggle1 == true){
        // set back to idle
        flypct = 30;
        flytoggle1 = false;
    }
    delay(250);
  }
  setFlyDriver(flypct);
  master.print(0, 0, "Fly: %f", flypct);
}

double getFly(){
  return flypct;
}
