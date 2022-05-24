#pragma once
#include "main.h"
using namespace pros;

void resetTrack();
void updateValues();
void updateOrientation();
void updatePosition();
void updateOdometry();
double getCurrentOrientation();
int getAuxEnc();
double getX();
double getY();
void setCurrentOrientation(double x);
