#include "main.h"
#include "odometry.hpp"
using namespace pros;

#define Tl    5.5     // inches
#define Tr    6.5     // inches
#define Tb    8      // inches

#define inPerDeg driveWheelDiam*PI/360 // inches

double deltaOrientationRad = 0; // radians
double deltaOrientationDeg = 0; // degrees

double prevOrientationRad = 0; // radians
double prevOrientationDeg = 0; // degrees

double currentOrientationRad = 0; // radians
double currentOrientationDeg = 0; // degrees

double deltaLeftEnc = 0;
double deltaRightEnc = 0;

double prevLeftEnc = 0;
double prevRightEnc = 0;

double leftEnc = 0;
double rightEnc = 0;

// source: https://youtu.be/vxSK2NYtYJQ

void resetTrack(){
	leftT.reset();
	rightT.reset();
	auxT.reset();
}

void updateValues(){
	prevLeftEnc = leftEnc;
	prevRightEnc = rightEnc;

	leftEnc = leftT.get_value();
	rightEnc = rightT.get_value();

	deltaLeftEnc = leftEnc-prevLeftEnc;
	deltaRightEnc = rightEnc-prevRightEnc;
}

void updateOrientation(){
	while (true){
		prevOrientationRad = currentOrientationRad;
		prevOrientationDeg = currentOrientationDeg;

		updateValues();

		// currentOrientationRad += ((deltaLeftEnc-deltaRightEnc)/(Tl+Tr))*0.02707;
		// currentOrientationRad += (deltaLeftEnc-deltaRightEnc)/(Tl+Tr)*inPerDeg;
		// currentOrientationRad += (deltaLeftEnc-deltaRightEnc)/(11.6)*inPerDeg;
		currentOrientationRad += (deltaLeftEnc-deltaRightEnc)/(11)*inPerDeg;

		currentOrientationDeg = radToDeg(currentOrientationRad);

		deltaOrientationDeg = currentOrientationDeg-prevOrientationDeg;
		deltaOrientationRad = currentOrientationRad-prevOrientationRad;
		Task::delay(15);
	}
}

double getCurrentOrientation(){
	return currentOrientationDeg;
}