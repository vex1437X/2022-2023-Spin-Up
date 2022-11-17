#pragma once
#include "main.h"

extern Motor catapult;
extern ADIDigitalIn cataLimit;

void resetCata();

void fireCata();

void cataControl(void*);