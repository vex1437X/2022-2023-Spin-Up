#pragma once
#include "main.h"
#include "pros/adi.hpp"

extern Motor intake;
extern ADIDigitalOut indexer;

void setIntake(int percent);

void setIndexState(bool state);

bool getIndexState();

void intakeControl();