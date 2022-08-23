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
double deltT = 0;

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
double changeX = 0;
double changeY = 0;

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
	deltaLeftEnc = ((leftEnc-prevLeftEnc)*trackCirc)/360;
	deltaRightEnc = ((rightEnc-prevRightEnc)*trackCirc)/360;
	deltaAuxEnc = ((auxEnc-prevAuxEnc)*trackCirc)/360;
	totalDeltaEnc = deltaLeftEnc+deltaRightEnc;
	deltT = (deltaRightEnc-deltaRightEnc)/(Tl+Tr);

	prevX = posX;
	prevY = posY;

	// **

	// if (deltaOrientationRad == 0){
	// 	posX += deltaAuxEnc;
	// 	posY += totalDeltaEnc;
	// 	// posX = 1;
	// 	// posY = 1;
	// } else{
	// 	posX += 2*((deltaAuxEnc/deltaOrientationDeg)+Tb)*sin(deltaOrientationDeg/2);
	// 	posY += 2*((deltaRightEnc/deltaOrientationDeg)+Tr)*sin(deltaOrientationDeg/2);
	// }

	// avgOrientationRad = prevOrientationRad + (deltaOrientationRad/2);

	// posR = sqrt(pow(posX, 2) + pow(posY, 2));
	// posTheta = atan(posY/posX);
	// posTheta -= avgOrientationRad;

	// posX = posR * cos(posTheta);
	// posY = posR * sin(posTheta);

	// **

	// if (deltaOrientationRad == 0){
	// 	posX += totalDeltaEnc/2*sin(currentOrientationRad);
	// 	posY += totalDeltaEnc/2*cos(currentOrientationRad);
	// }
	// else{
	// 	double s = (totalDeltaEnc/deltaOrientationRad)*sin(deltaOrientationRad/2);
	// 	posX += s * sin(prevOrientationRad+deltaOrientationRad/2);
	// 	posY += s * cos(prevOrientationRad+deltaOrientationRad/2);
	// }
	// if (deltaY < 0.001){
	// 	posX += deltaAuxEnc;
	// }

	// **

	if (deltaOrientationRad==0){
		posX += deltaLeftEnc*sin(currentOrientationRad);
		posY += deltaLeftEnc*cos(currentOrientationRad);
	} else{
		double s = 2*((deltaLeftEnc/deltaOrientationRad)+Tl)*sin(deltaOrientationRad/2);
		changeX = s*sin(currentOrientationRad+(deltaOrientationRad/2));
		changeY = s*cos(currentOrientationRad+(deltaOrientationRad/2));

		posX += changeX;
		posY += changeY;
	}

	// **
	
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

		Task::delay(20);
	}
}

double getCurrentOrientation(){
	return currentOrientationDeg;
}

double getDeltaOrientation(){
	return deltaOrientationDeg;
}

int getAuxEnc(){
	return auxT.get_value();
}

double getX(){
	return posX/12;
}

double getY(){
	return posY/12;
}

void setCurrentOrientation(double x){
	currentOrientationRad = 0;
}