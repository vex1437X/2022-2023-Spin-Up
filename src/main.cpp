#include "main.h"
#include "flywheel.hpp"
#include "pros/misc.h"

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
	lcd::set_text(1, "Autonomous");
	// begin odometry tracking

	// set drive motors to brake
	driveBrake();

	// driveFor(24, 50);
}

void opcontrol() {
	// begin timer for driver
	Task timer(updateDriveTimer);

	// idle the flywheel @ 30%
	setflypct(30);

	// set drive motors to coast
	driveCoast();
	bool braketoggle = true;

	while (true) {
		lcd::set_text(1, "Driver Control");
		

		// control drive using the controller
		driverControl();

		// control flywheel using the controller
		flywheelControl();

		// Coast/Brake drive toggle
		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)){
    		if (braketoggle == true){
				driveBrake();
				braketoggle = false;
			} else if (braketoggle == false){
				driveCoast();
				braketoggle = true;
			}
		delay(200);
  		}

		// center flywheel to goal
		if (controller.get_digital(E_CONTROLLER_DIGITAL_R1)){
			centerGoal();
		}

		delay(20);
	}
}
