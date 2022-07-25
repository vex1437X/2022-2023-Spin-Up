#include "main.h"
#include "odometry.hpp"
using namespace pros;

#define Tl    6     // inches
#define Tr    7     // inches
#define Tb    8      // inches

#define inPerDeg trackWheelDiam*PI/360 // inches

double deltaOrientationRad = 0;   // radians
double deltaOrientationDeg = 0;   // degrees

double prevOrientationRad = 0;    // radians
double prevOrientationDeg = 0; 	  // degrees

double currentOrientationRad = 0; // radians
double currentOrientationDeg = 0; // degrees
double avgOrientationRad = 0;	  // radians

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

// Cartesian coordinates
double prevX = 0;
double prevY = 0;
double posX = 0;
double posY = 0;
double deltaX = 0;
double deltaY = 0;

// Polar coordinates
double posR = 0;
double posTheta = 0;

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
	if (currentOrientationRad > 2*PI-0.001 && currentOrientationRad < 2*PI+0.001){
		currentOrientationRad = 0;
	}

	currentOrientationDeg = radToDeg(currentOrientationRad);

	if (currentOrientationDeg >= 360.00){
		currentOrientationDeg = 0;
	}

	deltaOrientationDeg = currentOrientationDeg-prevOrientationDeg;
	deltaOrientationRad = currentOrientationRad-prevOrientationRad;
}



void updatePosition(){
	deltaLeftEnc = (leftEnc - prevLeftEnc)*inPerDeg;
	deltaRightEnc = (rightEnc - prevRightEnc)*inPerDeg;
	deltaAuxEnc = (auxEnc - prevAuxEnc)*inPerDeg;
	totalDeltaEnc = deltaLeftEnc+deltaRightEnc;

	prevX = posX;
	prevY = posY;

	// if (deltaOrientationRad == 0){
	// 	posX += deltaAuxEnc;
	// 	posY += totalDeltaEnc;
	// 	// posX = 1;
	// 	// posY = 1;
	// } else{
	// 	posX += 2*sin(prevOrientationRad/2)*((deltaAuxEnc/deltaOrientationRad)+Tb);
	// 	posY += 2*sin(prevOrientationRad/2)*((deltaRightEnc/deltaOrientationRad)+Tr);
	// }

	// avgOrientationRad = prevOrientationRad + (deltaOrientationRad/2);

	// posR = sqrt(pow(posX, 2) + pow(posY, 2));
	// posTheta = atan(posY/posX);
	// posTheta -= avgOrientationRad;

	// posX = posR * cos(posTheta);
	// posY = posR * sin(posTheta);

	if (deltaOrientationRad == 0){
		posX += totalDeltaEnc/2*sin(currentOrientationRad);
		posY += totalDeltaEnc/2*cos(currentOrientationRad);
	}
	else{
		double s = (totalDeltaEnc/deltaOrientationRad)*sin(deltaOrientationRad/2);
		posX += s * sin(prevOrientationRad+deltaOrientationRad/2);
		posY += s * cos(prevOrientationRad+deltaOrientationRad/2);
	}
	if (deltaY < 0.001){
		posX += deltaAuxEnc;
	}
	deltaX = posX-prevX;
	deltaY = posY-prevY;
}

void updateOdometry(){
	while (true){
		prevOrientationRad = currentOrientationRad;
		prevOrientationDeg = currentOrientationDeg;
		updateValues();
		updateOrientation();
		updatePosition();

		printf("Orientation: %f \n", getCurrentOrientation());
		printf("PosX: %f \n", getX());
		printf("PosY: %f \n", getY());

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