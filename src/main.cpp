#include "main.h"
#include "autons.hpp"
#include "intake.hpp"
#include "pros/misc.h"

Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  {-1, -2, -3}

  // Right Chassis Ports (negative port will reverse it!)
  ,{4, 5, 6}

  // IMU Port
  ,11

  // Wheel Diameter
  ,3.25

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  // 1:2 gear ratio , 360 rpm
  ,0.6
);

void initialize() {
  ez::print_ez_template();
  
  pros::delay(500);

  // Configure your chassis controls
  chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.set_active_brake(0); // Sets the active brake kP. We recommend 0.1.
  chassis.set_curve_default(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!
  catapult.set_brake_mode(MOTOR_BRAKE_COAST);

  ez::as::auton_selector.add_autons({
    Auton("Half WP Left\n", leftside),
    Auton("Half WP Right\n", rightside),
    Auton("None\n", none),
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_BRAKE); // Set motors to hold.  This helps autonomous consistency.
  // Task sinCalc1(sinCalc, nullptr);

  testCode();
  // tune_PID();

  // ez::as::auton_selector.call_selected_auton(); // Calls selected auton from autonomous selector.
}

void opcontrol() {
  // Task anti_jam_task(anti_jam, nullptr);
  // Task limit(limitS, nullptr);
  Task cataCont(cataControl, nullptr);

  chassis.left_motors[0].move_voltage(0);
  chassis.left_motors[1].move_voltage(0);
  chassis.left_motors[2].move_voltage(0);
  chassis.right_motors[0].move_voltage(0);
  chassis.right_motors[1].move_voltage(0);
  chassis.right_motors[2].move_voltage(0);

  // reset intake
  setIntake(0);

	// set drive motors to coast
	bool braketoggle = true;
  chassis.set_drive_brake(MOTOR_BRAKE_BRAKE);


  while (true) {
    intakeControl();
    chassis.tank();

    // Coast/Brake drive toggle 
		if (master.get_digital(E_CONTROLLER_DIGITAL_Y)){
    		if (braketoggle == true){
          chassis.set_drive_brake(MOTOR_BRAKE_COAST);
          braketoggle = false;
			} else if (braketoggle == false){
          chassis.set_drive_brake(MOTOR_BRAKE_BRAKE);
          braketoggle = true;
			}
      delay(250);
  	}
    
    delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
