#pragma once
#include "main.h"

extern Optical colour;
extern Optical plateColour;

extern Drive chassis;

int pctToVolt(double pct);

void setLeft(double pct);
void setRight(double pct);

void setDrive(double leftpct, double rightpct);
void setDrive(double pct);

void driveFor(double sec, double leftpct, double rightpct);
void driveFor(double sec, double speedpct);

void spinRed();
void spinBlue();

bool isRed();

void spinColour();

void colourControl();