#pragma once
#include "main.h"

extern Motor flymotor1;
extern Motor flymotor2;


void flyCalc(void*);

void setFlyAuto(double percent);

void setFlyDriver(double percent);

bool canFire();

double getActRPM();

int getFlyVolt();

void setflypct(int set);

void flywheelControl();

double getFly();