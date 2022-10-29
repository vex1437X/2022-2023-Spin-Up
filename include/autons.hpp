#pragma once

#include "EZ-Template/drive/drive.hpp"

extern Drive chassis;

double conv(double i);

void default_constants();
void tuning_constants();
void sinCalc(void*);
void tune_PID();
void winpoint();
void halfWPright();
void halfWPleft();
void skills();