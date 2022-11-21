#include "colour.hpp"
#include "intake.hpp"
#include "main.h"
#include "pros/motors.h"
using namespace ez;

// Motor intake(16);    already defined in intake.cpp

double redHue = 0;
double blueHue = 240;

// proximity
// saturation

Optical colour(9);

Optical plateColour(15);

int pctToVolt(double pct){
    // percent to voltage conversion
    // ** -100 to +100 --> -12000 to +12000 **
    return 12000 * (pct/100);
}

void setLeft(double pct){
    chassis.left_motors[0].move_voltage(pctToVolt(pct));
    chassis.left_motors[1].move_voltage(pctToVolt(pct));
    chassis.left_motors[2].move_voltage(pctToVolt(pct));
}

void setRight(double pct){
    chassis.right_motors[0].move_voltage(pctToVolt(pct));
    chassis.right_motors[1].move_voltage(pctToVolt(pct));
    chassis.right_motors[2].move_voltage(pctToVolt(pct));
}

void setDrive(double leftpct, double rightpct){
    setLeft(leftpct); setRight(rightpct);
}

void setDrive(double pct){
    setLeft(pct); setRight(pct);
}

void driveFor(double sec, double leftpct, double rightpct){
    setDrive(leftpct, rightpct);
    delay(sec*1000);
    setDrive(0, 0);
}

void driveFor(double sec, double speedpct){
    setDrive(speedpct);
    delay(sec*1000);
    setDrive(0);
}

void spinRed(){
    int exit = 0;
    while((!(colour.get_hue() > blueHue - 20 && colour.get_hue() < blueHue + 20)) && exit < 2500){
        setIntake(-80);
        exit++;
    }
    setIntake(0);
}

void spinBlue(){
    int exit = 0;
    while((!(colour.get_hue() > redHue - 60 && colour.get_hue() < redHue + 60)) && exit < 2500){
        setIntake(-80);
        exit++;
    }
    setIntake(0);
}

// auton colour check
bool isRed(){
    if (plateColour.get_hue() > redHue - 60 && plateColour.get_hue() < redHue + 60){
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

bool colourswap = false;

void colourControl(){
    // TUNE THE PROXIMITY VALUES ***********
    colour.disable_gesture();
    colour.set_led_pwm(100);
    if (master.get_digital(E_CONTROLLER_DIGITAL_L2)){
        if (colour.get_proximity() < 25){
            // if (colourswap == false){
            //     spinBlue();
            //     colourswap = true;
            // } else if(colourswap == true){
            //     spinRed();
            //     colourswap = false;
            // }
            spinColour();
        }
        delay(300);
    }
}