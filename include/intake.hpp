#pragma once
#include "main.h"
#include "pros/adi.hpp"

extern Motor intake;
extern Motor intake2;
extern ADIDigitalOut indexer;

void setIntake(int percent);

void setIndexState(bool state);

bool getIndexState();

void intakeControl();