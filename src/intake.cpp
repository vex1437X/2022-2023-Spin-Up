#include "intake.hpp"
#include "EZ-Template/sdcard.hpp"
#include "EZ-Template/util.hpp"
#include "catapult.hpp"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
using namespace ez;

Motor intake(11, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);

ADIDigitalOut expand1(1, false);
ADIDigitalOut expand2(2, false);

ADIDigitalIn limitswitch(2);

bool isIntakeOn = false;
bool stop = false;

int numDisc = 0;

bool intaketoggle = false;
bool intaketoggle1 = false;
bool expandtoggle = false;

void setIntake(int percent){
  // percent to voltage
  int voltage = percent*1.27;
  // -127 to +127
  intake.move(voltage);
}

void limitS(void*){
  bool cringe = false;
  bool cringe2 = false;

  while(true){
    if(limitswitch.get_value() && !cringe){
      numDisc++;
      cringe = true;
      delay(350);
    } else if (!limitswitch.get_value()){
      cringe = false;
    }
    if (numDisc == 3 && !cringe2){
      delay(230);
      setIntake(0);
      isIntakeOn = false;
      cringe2 = true;
    }
    if (numDisc != 3){
      cringe2 = false;
    }
    delay(20);
  }
}

void intakeControl(){
  // expansion
  if (master.get_digital(E_CONTROLLER_DIGITAL_X)){
    if(expandtoggle == false){
      expand1.set_value(true);
      expand2.set_value(true);
      expandtoggle = true;
    } else if (expandtoggle == true){
      expand1.set_value(false);
      expand2.set_value(false);
      expandtoggle = false;
    }
    delay(300);
    }

  // Toggle intake
  if (master.get_digital(E_CONTROLLER_DIGITAL_R1) && !stop){
    if (intaketoggle == false){
      setIntake(100);
      intaketoggle = true;
      isIntakeOn = true;
    } else if (intaketoggle == true){
      // set back to idle
      setIntake(0);
      intaketoggle = false;
      isIntakeOn = false;
    }
      delay(250);
  }

  // Toggle intake reverse
  if (master.get_digital(E_CONTROLLER_DIGITAL_R2) && !stop){
    if (intaketoggle1 == false){
      setIntake(-100);
      intaketoggle1 = true;
        // isOuttakeOn = true;
        isIntakeOn = true;
    } else if (intaketoggle1 == true){
      // set back to idle
      setIntake(0);
      intaketoggle1 = false;
      // isOuttakeOn = false;
      isIntakeOn = false;
    }
    delay(250);
  }
  
  if (stop){
    setIntake(0);
    // isOuttakeOn = false;
    isIntakeOn = false;
  }
}