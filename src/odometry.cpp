#include "main.h"
#include "odometry.hpp"
using namespace pros;

#define Tl    6     // inches
#define Tr    7     // inches
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

		currentOrientationRad += (deltaLeftEnc-deltaRightEnc)/(12)*inPerDeg;

		if (currentOrientationRad < 0){
			currentOrientationRad += 2*PI;
		}
		if (currentOrientationRad >= 2*PI){
			currentOrientationRad -= 2*PI;
		}
		if (currentOrientationRad == 2*PI){
			currentOrientationRad = 0;
		}
		if (currentOrientationRad > PI/180-0.001 && currentOrientationRad < PI/180+0.001){
			currentOrientationRad = 0;
		}

		currentOrientationDeg = radToDeg(currentOrientationRad);

		if (currentOrientationDeg >= 360.0){
			currentOrientationDeg = 0;
		}

		deltaOrientationDeg = currentOrientationDeg-prevOrientationDeg;
		deltaOrientationRad = currentOrientationRad-prevOrientationRad;
		Task::delay(15);
	}
}

double getCurrentOrientation(){
	return currentOrientationDeg;
}

void setCurrentOrientation(double x){
	currentOrientationRad = 0;
}