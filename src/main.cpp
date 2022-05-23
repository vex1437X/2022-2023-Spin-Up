#include "main.h"

using namespace pros;
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	// static bool pressed = false;
	// pressed = !pressed;
	// if (pressed) {
	// 	pros::lcd::set_text(2, "I was pressed!");
	// } else {
	// 	pros::lcd::clear_line(2);
	// }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	lcd::initialize();
	lcd::set_text(1, "TEAM 1437X");
	// pros::lcd::register_btn1_cb(on_center_button);

	// set drive motors to coast
	driveCoast();

	// reset tracking wheel encoders
	resetTrack();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	lcd::set_text(1, "Autonomous");
	Task odom(updateOrientation);

	// set drive motors to brake
	driveBrake();
	
	turnTo(-90, 20);
	turnTo(0, 20);
}

void opcontrol() {
	lcd::set_text(3, "Driver Control");
	// set drive motors to coast
  	// driveCoast();
	driveBrake();
	Task odom(updateOrientation);


	while (true) {
		// control drive using the controller
		driverControl();

		printf("Orientation: %f \n", getCurrentOrientation());

		delay(20);
	}
}
