#include "main.h"
#include "autons.hpp"
#include "intake.hpp"
#include "pros/misc.h"

Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {-17, -18}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{19, 20}

  // IMU Port
  ,13

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,3.25

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  // 1:2 gear ratio , 300 rpm
  ,0.5


  // Uncomment if using tracking wheels
  /*
  // Left Tracking Wheel Ports (negative port will reverse it!)
  // ,{1, 2} // 3 wire encoder
  // ,8 // Rotation sensor

  // Right Tracking Wheel Ports (negative port will reverse it!)
  // ,{-3, -4} // 3 wire encoder
  // ,-9 // Rotation sensor
  */

  // Uncomment if tracking wheels are plugged into a 3 wire expander
  // 3 Wire Port Expander Smart Port
  // ,1
);

void initialize() {
  // Print our branding over your terminal :D
  ez::print_ez_template();
  
  pros::delay(500); // Stop the user from doing anything while legacy ports configure.

  // Configure your chassis controls
  chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.set_active_brake(0); // Sets the active brake kP. We recommend 0.1.
  chassis.set_curve_default(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.set_left_curve_buttons (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.add_autons({
    // Auton("PID Tuner\n", tune_PID),
    Auton("Half WP Right\n", halfWPright),
    Auton("Half WP Left\n", halfWPleft),
    Auton("Winpoint\n", winpoint),
    Auton("None\n", none),
    Auton("Skills Auton\n", skills)
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();

  tripleIndexer.set_value(false);
  indexer.set_value(false);
  toggleSingle.set_value(true);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_BRAKE); // Set motors to hold.  This helps autonomous consistency.
  Task sinCalc1(sinCalc, nullptr);

  jiggletest();

  // ez::as::auton_selector.call_selected_auton(); // Calls selected auton from autonomous selector.
}

void opcontrol() {
  // Task anti_jam_task(anti_jam, nullptr);
  Task limit(limitS, nullptr);

  chassis.left_motors[0].move_voltage(0);
  chassis.left_motors[1].move_voltage(0);
  chassis.right_motors[0].move_voltage(0);
  chassis.right_motors[1].move_voltage(0);

  // idle the flywheel @ 30%
	setflypct(30);

  // reset intake
  setIntake(0);

	// set drive motors to coast
	bool braketoggle = true;
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);


  while (true) {
    flywheelControl();
    intakeControl();
    chassis.tank();
    
    delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
