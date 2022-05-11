#include "main.h"
using namespace pros;

void setDrive(int left, int right);
void resetDrive();
void resetDriveEncoders();
double avgDriveEncoders();

void driveCoast();
void driveBrake();

void driverControl();

void driveFor(double inches, double percent);
void turnFor(double degrees, double percent);
