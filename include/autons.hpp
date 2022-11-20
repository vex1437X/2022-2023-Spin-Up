#pragma once

#include "EZ-Template/drive/drive.hpp"

extern Drive chassis;

double conv(double i);

void default_constants();
void tuning_constants();
void autonCalcs(void*);
void sinCalc(void*);
void testCode();
void none();
void tune_PID();
void winpoint();
void rightside();
void leftside();