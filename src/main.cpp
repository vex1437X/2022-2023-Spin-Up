#include "main.h"
using namespace pros;

void initialize() {
	lcd::initialize();
	lcd::set_text(1, "TEAM 1437X");
	// pros::lcd::register_btn1_cb(on_center_button);

	// set drive motors to coast
	driveCoast();

	int delayT = 0;
	imu.reset(); // ensure the inertial sensor is calibrated and ready to return accurate values
	while(imu.is_calibrating()){
		// should take about 2000 ms
		delayT+=10;
		printf("Calibration timer (ms): %f \n", delayT);
		delay(10);
	}

	imu.tare(); // reset all inertial sensor values to 0
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	lcd::set_text(2, "Autonomous");
	// set drive motors to brake
	driveBrake();

	turnFor(90, 100);
}

void opcontrol() {
	lcd::set_text(3, "Driver Control");
	// set drive motors to coast
  	// driveCoast();
	driveBrake();

	while (true) {
		driverControl();

		delay(20);
	}
}
