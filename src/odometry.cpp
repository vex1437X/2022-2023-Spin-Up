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
double deltaAuxEnc = 0;
double totalDeltaEnc = 0;

double prevLeftEnc = 0;
double prevRightEnc = 0;
double prevAuxEnc = 0;

double leftEnc = 0;
double rightEnc = 0;
double auxEnc = 0;

double posX = 0;
double posY = 0;

// source: https://youtu.be/vxSK2NYtYJQ

void resetTrack(){
	leftT.reset();
	rightT.reset();
	auxT.reset();
}

void updateValues(){
	prevLeftEnc = leftEnc;
	prevRightEnc = rightEnc;
	prevAuxEnc = auxEnc;

	leftEnc = leftT.get_value();
	rightEnc = rightT.get_value();
	auxEnc = auxT.get_value();

	deltaLeftEnc = leftEnc-prevLeftEnc;
	deltaRightEnc = rightEnc-prevRightEnc;
	deltaAuxEnc = auxEnc-prevAuxEnc;

	totalDeltaEnc = deltaLeftEnc+deltaRightEnc;
}

void updateOrientation(){
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
}

void updatePosition(){
	deltaLeftEnc = (leftEnc - prevLeftEnc)*inPerDeg;
	deltaRightEnc = (rightEnc - prevRightEnc)*inPerDeg;
	deltaAuxEnc = (auxEnc - prevAuxEnc)*inPerDeg;
	totalDeltaEnc = deltaLeftEnc+deltaRightEnc+deltaAuxEnc;

	if (deltaOrientationRad == 0){
		posX += totalDeltaEnc*inPerDeg/2*sin(currentOrientationRad);
		posY += totalDeltaEnc*inPerDeg/2*cos(currentOrientationRad);
	}
	else{
		double strDist = (totalDeltaEnc/deltaOrientationRad)*sin(deltaOrientationRad/2);
		posX += strDist * sin(prevOrientationRad+deltaOrientationRad/2);
		posY += strDist * cos(prevOrientationRad+deltaOrientationRad/2);
	}
}

void updateOdometry(){
	while (true){
		prevOrientationRad = currentOrientationRad;
		prevOrientationDeg = currentOrientationDeg;
		updateValues();
		updateOrientation();
		updatePosition();

		Task::delay(15);
	}
}

double getCurrentOrientation(){
	return currentOrientationDeg;
}

int getAuxEnc(){
	return auxT.get_value();
}

double getX(){
	return posX;
}

double getY(){
	return posY;
}


void setCurrentOrientation(double x){
	currentOrientationRad = 0;
}