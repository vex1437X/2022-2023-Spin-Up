#include "main.h"
#include "pros/misc.h"
#include "autons.hpp"
#include "systems.hpp"

using namespace pros;


// * CHANGE
// ports
#define piston_boost_port 7
#define catapult_limit_switch_port 8
#define expansion_port_1 6
#define expansion_port_2 0
#define plate_optical_port 0
#define colourwheel_optical_port 0

// buttons
pros::controller_digital_e_t CATA_SHOT = pros::E_CONTROLLER_DIGITAL_L1;
pros::controller_digital_e_t COLOUR_SPIN = pros::E_CONTROLLER_DIGITAL_L2;
pros::controller_digital_e_t INTAKE_IN = pros::E_CONTROLLER_DIGITAL_R1;
pros::controller_digital_e_t INTAKE_OUT = pros::E_CONTROLLER_DIGITAL_R2;
pros::controller_digital_e_t EXPAND_LEFT = pros::E_CONTROLLER_DIGITAL_X;
pros::controller_digital_e_t EXPAND_RIGHT = pros::E_CONTROLLER_DIGITAL_A;

// speeds
int INTAKE_IN_SPEED = 100;
int INTAKE_OUT_SPEED = 100;
int COLOUR_SPEED = 100;
int CATA_SPEED = -100;

// colourwheel 
pros::Motor c1(11, E_MOTOR_GEARSET_18, false);
// intake
pros::Motor i1(11, E_MOTOR_GEARSET_18, false);

// catapult
pros::Motor cat1(18, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_COUNTS);

// const
std::vector<pros::Motor> colour_motors{c1};
std::vector<pros::Motor> intake_motors{i1};
std::vector<pros::Motor> catapult_motors{cat1};

// * DONT CHANGE
pros::ADIDigitalOut PistonBoost(piston_boost_port);
pros::ADIDigitalOut Expansion1(expansion_port_1);
pros::ADIDigitalOut Expansion2(expansion_port_2);
pros::ADIDigitalIn cataLimit(catapult_limit_switch_port);
pros::Optical plateColour(plate_optical_port);
pros::Optical colourW(colourwheel_optical_port);

bool fst = true;
bool colourtoggle = false;
double redHue = 0;
double blueHue = 240;
bool didReach = false;
bool intaketoggleIN = false;
bool intaketoggleOUT = false;
double cata_kP = 0;
double cata_kI = 0;
double cata_kD = 0;
bool justshot = false;
bool first = true;
bool expand = false;

void set_intake(double percent) {
    for (pros::Motor i : intake_motors) {
        i.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        i.move(127*(percent/100));
    }
}

void set_cata(double percent) {
    for (pros::Motor i : catapult_motors) {
        i.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        i.move(127*(percent/100));
    }
}

void intake_control(void*){
    while(true){
        if (master.get_digital(INTAKE_IN)){
            if (intaketoggleIN == false){
                set_intake(abs(INTAKE_IN_SPEED));
                intaketoggleIN = true;
            } else if (intaketoggleIN == true){
                set_intake(0);
                intaketoggleIN = false;
            }
            pros::delay(350);
        }
        if (master.get_digital(INTAKE_OUT)){
            if (intaketoggleOUT == false){
                set_intake(abs(INTAKE_OUT_SPEED)*-1);
                intaketoggleOUT = true;
            } else if (intaketoggleOUT == true){
                set_intake(0);
                intaketoggleOUT = false;
            }
            pros::delay(350);
        }
        if (master.get_digital(EXPAND_LEFT) || master.get_digital(EXPAND_RIGHT) || 
            master.get_digital(E_CONTROLLER_DIGITAL_LEFT) || master.get_digital(E_CONTROLLER_DIGITAL_UP)){
            if (expand == false){
                Expansion1.set_value(true);
                expand = true;
            } else if (expand == true){
                Expansion1.set_value(false);
                expand = false;
            }
            pros::delay(350);
            
            // Expansion2.set_value(true);
        }
        pros::delay(20);
    }
}


void set_colour(double percent) {
    for (pros::Motor i : colour_motors) {
        i.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        i.move(127*(percent/100));
    }
}
void set_cata_pid(double kP, double kI, double kD) {
    cata_kP = kP;
    cata_kI = kI;
    cata_kD = kD;
}

int get_cataLimit_value(){
    return cataLimit.get_value();
}

void cataFor(double sec, int percent){
  set_cata(abs(CATA_SPEED)*-1);
  pros::delay(sec*1000);
  set_cata(0);
}

void superCata(double del, double sec, int percent){
    set_cata(abs(CATA_SPEED)*-1);
    pros::delay(del*1000);
    PistonBoost.set_value(1);
    pros::delay(sec*1000);
    set_cata(0);
}

void resetCata(){
    while(!didReach){
        cat1.set_brake_mode(MOTOR_BRAKE_COAST);
        set_cata(abs(CATA_SPEED)*-1);
        if (get_cataLimit_value()){
            didReach = true;
            set_cata(0);
            delay(10);
            cat1.set_brake_mode(MOTOR_BRAKE_BRAKE);
            delay(1000);
            cat1.set_brake_mode(MOTOR_BRAKE_COAST);
            first = false;
            return;   
        }
        pros::delay(10);
    }
}

void fireCata(){
  if(didReach){
    cat1.set_brake_mode(MOTOR_BRAKE_COAST);
    set_intake(0);
    intaketoggleIN = false;
    cataFor(0.2, CATA_SPEED);
    justshot = true;
  }
  didReach = false;
}

bool super = false;

void superIdol(){
    super = true;
}

int get_colourW_prox(){
    return colourW.get_proximity();
}

double get_colourW_hue(){
    colourW.disable_gesture();
    colourW.set_led_pwm(100);
    return colourW.get_hue();
}

double get_plate_hue(){
    plateColour.disable_gesture();
    plateColour.set_led_pwm(100);
    return plateColour.get_hue();
}

void spinRed(){ // spin until blue is bottom
    int exit = 0;
    while((!(get_colourW_hue() > blueHue - 100 && get_colourW_hue() < blueHue + 80)) && exit < 1000){
        set_colour(abs(COLOUR_SPEED)*-1);
        exit++;
        pros::delay(10);
    }
    set_colour(0);
}

void spinBlue(){ // spin until red is bottom
    int exit = 0;
    while((!(get_colourW_hue() > 360 - 40 || get_colourW_hue() < redHue + 100)) && exit < 1000){
        set_colour(abs(COLOUR_SPEED)*-1);
        exit++;
        pros::delay(10);
    }
    set_colour(0);
}

bool isRed(){
    if (get_plate_hue() > 360 - 40 || get_plate_hue() < redHue + 100){
        return true;
    } else {
        return false;
    }
}

void spinColour(){
    if (isRed()){
        spinRed();
    } else {
        spinBlue();
    }
}

void Auton_task(void*){
    while(true){
        if (super && didReach){      
            superCata(0.2,1.5, CATA_SPEED);
            PistonBoost.set_value(0);
            didReach = false;
            super = false;
        }
        pros::delay(10);
    }
}

void Systems_task(void*) {
    while(true){ // BEING RAN IN MAIN
        if(fst){ pros::delay(500); fst = false;}

        if (master.get_digital(CATA_SHOT)){
            fireCata();
            pros::delay(600);
        }
        // /*
        if (master.get_digital(COLOUR_SPIN)){
            superIdol();
        }
        // */
        resetCata();


        // if (master.get_digital(CATA_SHOT)){
        //     set_cata(-100);
        // } else {
        //     set_cata(0);
        // }

        // Colour wheel control

        // if (master.get_digital(COLOUR_SPIN)){
        //     // if (get_colourW_prox() < 30){
        //         spinColour();
        //     // }
        // }
        pros::delay(10);
    }
}