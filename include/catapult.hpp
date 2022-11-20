#pragma once
#include "main.h"

extern Motor catapult;
extern ADIDigitalIn cataLimit;

void cataFor(double sec, int percent);

void resetCata();

void fireCata();

void cataControl(void*);