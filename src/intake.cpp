#include "intake.hpp"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
using namespace ez;

Motor intake(6, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);
Motor intake2(16, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);
ADIDigitalOut indexer(1, false);
ADIDigitalOut tripleIndexer(8, false);

Task anti_jam_task(anti_jam, nullptr);

bool indexState = false;
bool tripIndexState = false;
bool isJammed = false;
bool isIntakeOn = false;
bool isOuttakeOn = false;
bool stop = false;

bool intaketoggle = false;
bool intaketoggle1 = false;

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

void anti_jam(void*) {
  isJammed = false;
  int jamCounter = 0;
  int waitTime = 1000;

  while (true) {
    if (isJammed) {
      stop = true;
      setIntake(-100);
      jamCounter++;
      if (jamCounter > waitTime) {
        isJammed = false;
        jamCounter = 0;
        stop = false;
      }
    } else if (abs(intake.get_actual_velocity()) <= 15 && abs(intake2.get_actual_velocity()) <= 15 && (isOuttakeOn || isIntakeOn)) {

      jamCounter += ez::util::DELAY_TIME;
      if (jamCounter > waitTime) {
      //   jamCounter = 0;
        isJammed = true;
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
  if (master.get_digital(E_CONTROLLER_DIGITAL_RIGHT) && !stop){
    if (intaketoggle1 == false){
      setIntake(-100);
      intaketoggle1 = true;
        isOuttakeOn = true;
    } else if (intaketoggle1 == true){
      // set back to idle
      setIntake(0);
      intaketoggle1 = false;
      isOuttakeOn = false;
    }
    delay(250);
  }
  
  if (stop){
    setIntake(0);
  }

  // Toggle indexer
  if (master.get_digital(E_CONTROLLER_DIGITAL_UP)){
    if (indexState == false){
      indexer.set_value(indexState);
      indexState = true;
    } else if (indexState == true){
      indexer.set_value(indexState);
      indexState = false;
    }
    delay(250);
  }

  // Toggle triple indexer
  if (master.get_digital(E_CONTROLLER_DIGITAL_R2)){
    if (tripIndexState == false){
      tripleIndexer.set_value(tripIndexState);
      tripIndexState = true;
    } else if (tripIndexState == true){
      tripleIndexer.set_value(tripIndexState);
      tripIndexState = false;
    }
    delay(250);
  }
}