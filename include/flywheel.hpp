#pragma once
#include "main.h"

extern Motor flymotor1;
extern Motor flymotor2;


void setFly(double percent);

int getFlyVolt();

void setflypct(int set);

void flywheelControl();

double getFly();