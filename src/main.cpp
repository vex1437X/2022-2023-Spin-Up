#include "main.h"

using namespace pros;

void on_center_button() {
	// static bool pressed = false;
	// pressed = !pressed;
	// if (pressed) {
	// 	pros::lcd::set_text(2, "I was pressed!");
	// } else {
	// 	pros::lcd::clear_line(2);
	// }
}

double stime;

void initialize() {
	lcd::initialize();
	lcd::set_text(1, "TEAM 1437X");

	// reset the driver timer
	resetTimer();

	// set drive motors to coast
	driveCoast();

	// reset tracking wheel encoders
	resetTrack();

	if (pros::competition::get_status() & COMPETITION_CONNECTED == true) {
    // Field Control is Connected
    // Run LCD Selector code or similar
  	}
}


void disabled() {
	// set drive motors to coast
	driveCoast();
}

void competition_initialize() {}

void autonomous() {
	lcd::set_text(2, "Autonomous");
	// begin odometry tracking
	Task odometry(updateOdometry);

	// reset tracking wheel encoders
	resetTrack();

	// set drive motors to brake
	driveBrake();
	
	driveTo(0, 10, 20);
	// delay(1000);
	// driveTo(0, 0, 20);
	// turnTo(270, 25);
	// delay(1000);
	// turnTo(0, 25);
}

void opcontrol() {
	lcd::set_text(3, "Driver Control");
	// begin odometry tracking
	Task odometry(updateOdometry);
	// begin timer for driver
	Task timer(updateDriveTimer);

	// set drive motors to brake
	driveBrake();

	while (true) {
		// control drive using the controller
		driverControl();


		delay(20);
	}
}
