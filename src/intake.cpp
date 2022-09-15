#include "intake.hpp"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
using namespace ez;

Motor intake(20, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_COUNTS);

bool indexState = false;

ADIDigitalOut indexer(1, indexState);

void setIntake(int percent){
  // percent to voltage
  int voltage = percent*1.27;
  // -127 to +127
  intake.move(voltage);
}

void setIndexState(bool state){
  indexState = state;
}

bool getIndexState(){
  return indexState;
}

bool intaketoggle = true;

void intakeControl(){
  // Toggle intake
  if (master.get_digital(E_CONTROLLER_DIGITAL_R1)){
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

  // Toggle indexer
  if (master.get_digital(E_CONTROLLER_DIGITAL_R2)){
    if (indexState == true){
      indexer.set_value(indexState);
      setIntake(100);
      indexState = false;
    } else if (indexState == false){
      indexer.set_value(indexState);
      indexState = true;
    }
    delay(250);
  }
}