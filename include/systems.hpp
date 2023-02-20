#pragma once
#include "main.h"

#include "EZ-Template/drive/drive.hpp"

extern Drive chassis;


void Auton_task(void*);
void Systems_task(void*);
void intake_control(void*);
void superIdol();
void set_colour(double percent);
void set_intake(double percent);
extern pros::ADIDigitalOut Expansion1;
void fireCata();

