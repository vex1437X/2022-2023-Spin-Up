#include "main.h"
#include "flywheel.hpp"

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

// double stime;

void initialize() {
	lcd::initialize();
	lcd::set_text(1, "TEAM 1437X");

	// reset the driver timer
	resetTimer();

	// reset vision sensor
	vsensor.clear_led();

	// set drive motors to coast
	driveCoast();


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

	// set drive motors to brake
	driveBrake();
}

void opcontrol() {
	// begin timer for driver
	Task timer(updateDriveTimer);

	bool flytoggle = true;

	// set drive motors to brake
	driveCoast();

	while (true) {
		lcd::set_text(3, "Driver Control");
		// control drive using the controller
		driverControl();

		if (controller.get_digital(E_CONTROLLER_DIGITAL_L1)){
			if (flytoggle == true){
				setFly(127);
				flytoggle = false;
			} else if (flytoggle == false){
				setFly(0);
				flytoggle = true;
			}
			delay(150);
		}
		
		if (controller.get_digital(E_CONTROLLER_DIGITAL_R1)){
			centerGoal();
		}

		delay(20);
	}
}
