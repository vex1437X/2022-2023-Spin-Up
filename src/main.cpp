#include "main.h"
using namespace pros;

void initialize() {
	lcd::initialize();
	lcd::set_text(1, "TEAM 1437X");
	// pros::lcd::register_btn1_cb(on_center_button);

  // set drive motors to coast
  driveCoast();
/*
  imu.reset(); // ensure the inertial sensor is calibrated and ready to return accurate values
  while(imu.is_calibrating()){
    // should take about 2000 ms
    delay(10);
  }

  imu.tare(); // reset all inertial sensor values to 0
	*/
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	lcd::set_text(2, "Autonomous");
  // set drive motors to brake
  driveBrake();
}

void opcontrol() {
	lcd::set_text(3, "Driver Control");
  // set drive motors to coast
  driveCoast();

	// pros::Controller master(pros::E_CONTROLLER_MASTER);
	// pros::Motor left_mtr(1);
	// pros::Motor right_mtr(2);

	while (true) {
		// pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		//                  (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		//                  (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		// int left = master.get_analog(ANALOG_LEFT_Y);
		// int right = master.get_analog(ANALOG_RIGHT_Y);
		//
		// left_mtr = left;
		// right_mtr = right;
		// pros::delay(20);

		// driver control
    driverControl();

    delay(20);
	}
}
