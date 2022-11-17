#pragma once
#include "main.h"
#include "pros/adi.hpp"

extern Motor intake;

extern ADIDigitalOut expand1;
extern ADIDigitalOut expand2;

// extern ADIDigitalIn limitswitch;

void setIntake(int percent);

void limitS(void*);

void intakeControl();