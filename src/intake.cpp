#include "intake.hpp"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
using namespace ez;

Motor intake(16, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_COUNTS);
ADIDigitalOut indexer(1, false);

bool indexState = false;
bool isJammed = false;

bool intaketoggle = false;
bool intaketoggle1 = false;

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

void intakeControl(){
  // Toggle intake
  if (master.get_digital(E_CONTROLLER_DIGITAL_R1)){
        if (intaketoggle == false){
            setIntake(100);
            intaketoggle = true;
        } else if (intaketoggle == true){
            // set back to idle
            setIntake(0);
            intaketoggle = false;
        }
        delay(250);
    }

  // Toggle indexer
  if (master.get_digital(E_CONTROLLER_DIGITAL_R2)){
    if (indexState == false){
      indexer.set_value(indexState);
      setIntake(100);
      indexState = true;
    } else if (indexState == true){
      indexer.set_value(indexState);
      indexState = false;
    }
    delay(250);
  }

  // Toggle intake reverse
  if (master.get_digital(E_CONTROLLER_DIGITAL_LEFT)){
    if (intaketoggle1 == false){
        setIntake(-100);
        intaketoggle1 = true;
    } else if (intaketoggle1 == true){
        // set back to idle
        setIntake(0);
        intaketoggle1 = false;
    }
    delay(250);
  }
}