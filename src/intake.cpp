#include "intake.hpp"
#include "EZ-Template/sdcard.hpp"
#include "EZ-Template/util.hpp"
#include "flywheel.hpp"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
using namespace ez;

Motor intake(6, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);
Motor intake2(16, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);
ADIDigitalOut indexer(1, false);
ADIDigitalOut toggleSingle(7, false);
ADIDigitalOut tripleIndexer(8, false);
ADIDigitalIn limitswitch(2);

bool indexState = false;
bool tripIndexState = false;
bool isJammed = false;
bool isIntakeOn = false;
// bool isOuttakeOn = false;
bool stop = false;

int numDisc = 0;

bool intaketoggle = false;
bool intaketoggle1 = false;

void fireOneDisc(){
  // fire
  indexer.set_value(true);
  delay(500);
  // retract
  indexer.set_value(false);
  toggleSingle.set_value(true);
}


void fireThreeDiscs(){
  // fire
  indexer.set_value(false);
  toggleSingle.set_value(false);
  tripleIndexer.set_value(true);
  delay(500);
  // retract
  indexer.set_value(false);
  toggleSingle.set_value(true);
  tripleIndexer.set_value(false); 
}

void setIntake(int percent){
  // percent to voltage
  int voltage = percent*1.27;
  // -127 to +127
  intake.move(voltage);
  intake2.move(voltage);
}

void setIndexState(bool state){
  indexState = state;
}

bool getIndexState(){
  return indexState;
}

void setDisc(int num){
  numDisc = num;
}

void limitS(void*){
  bool cringe = false;
  bool cringe2 = false;

  while(true){
    // intakeControl();
    // printf("limit: %d \n", limitswitch.get_new_press());
    // printf("numDisc: %d \n", numDisc);
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
      // isOuttakeOn = false;
      cringe2 = true;
    }
    if (numDisc != 3){
      cringe2 = false;
    }
    delay(20);
  }
}

void anti_jam(void*) {
  isJammed = false;
  int jamCounter = 0;
  int jamCheck = 0;
  int waitTime = 2000;

  while (true) {
    if (isJammed) {
      stop = true;
      setIntake(-100);
      // isOuttakeOn = true;
      isIntakeOn = true;
      jamCounter++;
      if (jamCounter > waitTime) {
        isJammed = false;
        jamCounter = 0;
        stop = false;
        setIntake(100);
        isIntakeOn = true;
        // isOuttakeOn = false;

      }
    } else if (abs(intake.get_actual_velocity()) <= 10 && abs(intake2.get_actual_velocity()) <= 10 && isIntakeOn) {

      jamCheck++;
      if (jamCheck > 500) {
      //   jamCounter = 0;
        isJammed = true;
        jamCheck = 0;
      }
    }
    pros::delay(ez::util::DELAY_TIME);
  }
}

void intakeControl(){
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
  // Toggle indexer
  if (master.get_digital(E_CONTROLLER_DIGITAL_DOWN)){
    /*
    if (indexState == true){
      if (numDisc > 0){
        numDisc--;
      }
      indexer.set_value(indexState);
      indexState = false;
    }
    delay(500);
    if (indexState == false){
      indexer.set_value(indexState);
      indexState = true;
    }
    */
    fireOneDisc();
    delay(20);
    if (numDisc > 0){
      numDisc--;
    }
    if (numDisc == 0){
      // setflypct(30);
    }
  }

  // Toggle triple indexer
  if (master.get_digital(E_CONTROLLER_DIGITAL_B)){
    /*
    tripleIndexer.set_value(true);
    numDisc = 0;
    delay(100);
    indexer.set_value(true);
    delay(500);
    indexer.set_value(false);
    tripleIndexer.set_value(false);
    setflypct(30);
    */
    fireThreeDiscs();
    delay(20);
    numDisc = 0;
    // setflypct(30);
  }
}