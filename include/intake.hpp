#pragma once
#include "main.h"
#include "pros/adi.hpp"

extern Motor intake;
extern Motor intake2;
extern ADIDigitalOut indexer;

extern Task anti_jam_task;

extern bool isJammed;


void setIntake(int percent);

void setIndexState(bool state);

bool getIndexState();

void anti_jam(void*);

void intakeControl();