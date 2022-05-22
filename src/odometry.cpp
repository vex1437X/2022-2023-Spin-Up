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
	prevOrientationRad = currentOrientationRad;
	prevOrientationDeg = currentOrientationDeg;

	updateValues();

	// currentOrientationRad += ((deltaLeftEnc-deltaRightEnc)/(Tl+Tr))*0.02707;
	currentOrientationRad += ((deltaLeftEnc-deltaRightEnc)*inPerDeg/(Tl+Tr));

	currentOrientationDeg = radToDeg(currentOrientationRad);

	deltaOrientationDeg = currentOrientationDeg-prevOrientationDeg;
	deltaOrientationRad = currentOrientationRad-prevOrientationRad;
}

double getCurrentOrientation(){
	return currentOrientationDeg;
}



// Code from https://github.com/jloh02/VEX-Worlds-2019-8059A/blob/master/src/base_lib.cpp
/*
#define COMPETITION_MODE true //Set to false to test odometry during driver

#define baseRPM 200									//Enter RPM of base motors
#define UNLIMITED_POWER 100         //Enter maximum power of base motors
#define rampingPow 8              	//Increase in power / 25 millis

#define DISTANCE_LEEWAY   3.0				//Enter Distance Leeway in Degrees

#define baseWidth 12.52198690477777	//Enter distance in inches between side encoders
#define inPerDeg 0.0354472057977424 //Determine empirically using at least 1 rotation

typedef struct{
	double x,y,angle;
} Coordinates;

Coordinates position;

double targetL=0,targetR=0;
double kP=0,kI=0,kD=0;
double lastResetAngle=0; //IN RADIANS

double encdL=0,encdR=0;

double motorTargetL=0,motorTargetR=0;

void baseOdometry(void * ignore){
	Controller master(E_CONTROLLER_MASTER);

  leftF.tare_position();
	rightF.tare_position();
	leftB.tare_position();
	rightB.tare_position();

  double prevEncdL = 0;
	double prevEncdR = 0;
	double prevAngle = 0;
	int count = 0;
	while(!COMPETITION_MODE || competition::is_autonomous()){
    encdL = leftB.get_position();
    encdR = rightB.get_position();
		double encdChangeL = (encdL - prevEncdL)*inPerDeg;
		double encdChangeR = (encdR - prevEncdR)*inPerDeg;
		position.angle = lastResetAngle + (encdL - encdR)*inPerDeg/baseWidth; //Theta = (s2-s1)/width
		double deltaAngle = position.angle - prevAngle;
		double sumEncdChange = encdChangeL+encdChangeR;

		if(deltaAngle == 0) //Cannot divide by 0
		{
			position.x += sumEncdChange/2*sin(position.angle);            	//Simple trigo
			position.y += sumEncdChange/2*cos(position.angle);
		}
		else                //Refer to formulas
		{
			double halfDeltaAngle = deltaAngle/2;
			double strDist = (sumEncdChange/deltaAngle)*sin(halfDeltaAngle);
			position.x += strDist * sin(prevAngle+halfDeltaAngle);
			position.y += strDist * cos(prevAngle+halfDeltaAngle);
		}

		prevEncdL = encdL;
		prevEncdR = encdR;
		prevAngle = position.angle;

		//master.print(2,0,"%2.1f %2.1f %3f",position.x,position.y,position.angle/PI*180.0);
		if(count++ % 10 == 0) printf("%2.1f \t %2.1f \t %3f\n",position.x,position.y,position.angle/PI*180.0);

    Task::delay(5);
	}
}

bool basePause = false;
void pauseBase(bool pause){
	basePause = pause;
}
void baseMotorControl(void * ignore){
  double powerL=0,powerR=0;
	//printf("Left \t Right\n");
  while(competition::is_autonomous()){
    double dileftFeftF = motorTargetL - powerL;
    if(fabs(dileftFeftF) > rampingPow) powerL += dileftFeftF>0?rampingPow:-rampingPow;
    else powerL = motorTargetL;

    double difrightF = motorTargetR - powerR;
    if(fabs(difrightF) > rampingPow) powerR += difrightF>0?rampingPow:-rampingPow;
    else powerR = motorTargetR;

    if(powerL > UNLIMITED_POWER) powerL = UNLIMITED_POWER;
    else if(powerL < -UNLIMITED_POWER) powerL = -UNLIMITED_POWER;
    if(powerR > UNLIMITED_POWER) powerR = UNLIMITED_POWER;
    else if(powerR < -UNLIMITED_POWER) powerR = -UNLIMITED_POWER;

		if(!basePause){
			leftF.move(powerL);
			leftB.move(powerL);
			rightF.move(powerR);
			rightB.move(powerR);
		}
		//printf("%4.0f \t %4.0f\n",powerL,powerR);

    Task::delay(15);
  }
}

void timerBase(double powerL, double powerR, double time){
	double start = millis();
	pauseBase(true);
	leftF.move(powerL);
	leftB.move(powerL);
	rightF.move(powerR);
	rightB.move(powerR);
	while(millis()-start<time)delay(25);
	leftF.move(0);
	leftB.move(0);
	rightF.move(0);
	rightB.move(0);
	pauseBase(false);
}

bool forceStraight = false;
void baseStraight(bool state){
	 forceStraight = state;
}

void baseControl(void * ignore){
  double prevErrorL = 0, prevErrorR = 0;
  while(competition::is_autonomous()){
    double errorL = targetL - leftB.get_position();
    double errorR = targetR - rightB.get_position();

		if(!forceStraight){
	    double deltaErrorL = errorL - prevErrorL;
	    double deltaErrorR = errorR - prevErrorR;

	    prevErrorL = errorL;
	    prevErrorR = errorR;

	    motorTargetL = kP*errorL+kD*deltaErrorL;
	    motorTargetR = kP*errorR+kD*deltaErrorR;
		}
		else{
			double combErrorP = (errorL+errorR)/2*kP;

			prevErrorL = errorL;
	    prevErrorR = errorR;

			motorTargetL = errorL>0?combErrorP:-combErrorP;
	    motorTargetR = errorR>0?combErrorP:-combErrorP;
		}

		//printf("Error: %f %f\n",errorL,errorR);

    Task::delay(15);
  }
}



void waitBase(double cutoff){
	double start = millis();
	while(fabs(targetL-leftB.get_position())>DISTANCE_LEEWAY && fabs(targetR-rightB.get_position())>DISTANCE_LEEWAY && millis()-start < cutoff){
		//printf("TL:%3f, leftF:%3f, TR:%3f, rightF:%3f\n",targetL,leftF.get_position(),targetR,rightF.get_position());
		//printf("~\t  \t%4.0f \t %4.0f\n",targetL-leftF.get_position(),targetR-rightF.get_position());
		delay(25);
	}
	leftF.move_relative(0, 100);
	leftB.move_relative(0, 100);
	rightF.move_relative(0, 100);
	rightB.move_relative(0, 100);
}

void baseMove(double dis, double p, double d){
  targetR += dis/inPerDeg;
	targetL += dis/inPerDeg;

  kP = p;
  kD = d;
}

void baseMove(double dis){
  baseMove(dis,0.40,1.4);
}

void baseMove(double x, double y, double p, double d){
	double errY = y-position.y;
	double errX = x-position.x;
	double distance = sqrt(errY*errY + errX*errX);
	double targAngle = atan2(errX,errY);
	//printf("Angle: %f %f", targAngle, position.angle);
	//printf("Distance: %f",distance);

	int negator = 1;
  if(fabs(targAngle-position.angle) >= PI/2) negator = -1;

  targetL += distance/inPerDeg*negator;
  targetR += distance/inPerDeg*negator;

  kP = p;
  kD = d;
}

void baseMove(double x, double y){
	baseMove(x,y,0.5,1.3);
}

void baseTurn(double angle, double p, double d){
	double error = angle/180.00000*PI - position.angle;
	double diff = error*baseWidth/inPerDeg/2.0000;
	targetL += diff;
	targetR += -diff;

	kP = p;
	kD = d;
}

void baseTurn(double angle){
  baseTurn(angle, 0.4, 0.0);
}

void baseTurnRelative(double angle, double p, double d){
  double diff = angle/180.00000*PI*baseWidth/inPerDeg/2;
  targetL += diff;
  targetR += -diff;

  kP = p;
  kD = d;
}

void baseTurnRelative(double angle){
  baseTurnRelative(angle, 0.7, 0.3);
}

void baseTurn(double x, double y, double p, double d){
	double targAngle = atan2((x-position.x),(y-position.y));
  double diff = (targAngle - position.angle)*baseWidth/inPerDeg/2;
  targetL += diff;
  targetR += -diff;
  kP = p;
  kD = d;
}

void baseTurn(double x, double y, double p, double d, bool inverted){
	double targAngle = atan2((x-position.x),(y-position.y));
	printf("HI: %f\n",targAngle);
	if(inverted) targAngle += PI;
	printf("HI: %f\n",targAngle);
	if(targAngle-position.angle > PI) targAngle -= (PI*2);
	printf("HI: %f\n",targAngle);
  double diff = (targAngle - position.angle)*baseWidth/inPerDeg/2;
  targetL += diff;
  targetR += -diff;
  kP = p;
  kD = d;
}

void baseTurn(double x, double y){
  baseTurn(x,y,0.7,0.3);
}

void baseTurn(double x, double y, bool inverted){
  baseTurn(x,y,0.7,0.3,inverted);
}

void resetCoord(double x, double y, double angleInDeg){
	position.x = x;
	position.y = y;
	position.angle = angleInDeg/180*PI;
	lastResetAngle = angleInDeg/180*PI;

	leftF.tare_position();
	rightF.tare_position();
	leftB.tare_position();
	rightB.tare_position();

	targetL = 0;
	targetR = 0;
}

double getY(){
	return position.y;
}
*/
