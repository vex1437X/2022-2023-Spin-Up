#include "intake.hpp"
#include "main.h"
#include "pros/misc.h"
using namespace ez;

Motor intake(20, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_COUNTS);

bool intaketoggle = true;

void setIntake(int percent){
  // percent to voltage
  int voltage = percent*1.27;
  // -127 to +127
  intake.move(voltage);
}

void intakeControl(){
  if (master.get_digital(E_CONTROLLER_DIGITAL_UP)){
        if (intaketoggle == true){
            setIntake(100);
            intaketoggle = false;
        } else if (intaketoggle == false){
            // set back to idle
            setIntake(0);
            intaketoggle = true;
        }
        delay(200);
    }
}