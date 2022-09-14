#pragma once
#include "main.h"

Motor flymotor1(14, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_COUNTS);
Motor flymotor2(15, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_COUNTS);


void setFly(int percent);

int getFlyVolt();

void setflypct(int set);

void flywheelControl();

int getFly();