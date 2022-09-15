#pragma once
#include "main.h"

extern Motor flymotor1;
extern Motor flymotor2;


void setFly(int percent);

int getFlyVolt();

void setflypct(int set);

void flywheelControl();

int getFly();