#pragma once
#include "main.h"
#include "pros/adi.hpp"

extern Motor intake;
extern Motor intake2;
extern ADIDigitalOut indexer;
extern ADIDigitalOut tripleIndexer;
extern ADIDigitalIn limitswitch;

extern Task anti_jam_task;
extern Task limit;

extern bool isJammed;


void setIntake(int percent);

void setIndexState(bool state);

bool getIndexState();

void anti_jam(void*);

void limitS(void*);

void intakeControl();