#include "main.h"
#include "autons.hpp"
#include "pros/misc.h"
#include "systems.hpp"

using namespace pros;


// Chassis constructor
Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {-17, 19, 20}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{12, -15, -16}

  // IMU Port
  ,13

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,3.25

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,60.0/36.0
);

#define piston_boost_port 7
pros::ADIDigitalOut PistonBoost(piston_boost_port);

pros::Task SystemsCalc(Systems_task, nullptr);
pros::Task AutoTask(Auton_task, nullptr);
pros::Task cont(intake_control, nullptr);


void initialize() {
  // Expansion1.set_value(false);
  AutoTask.suspend();
  SystemsCalc.suspend();
  cont.suspend();
  
  pros::delay(500);

  // Configure your chassis controls
  chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.set_active_brake(0.0); // Sets the active brake kP. We recommend 0.1.
  chassis.set_curve_default(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)

  PistonBoost.set_value(0);  

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.add_autons({
    // Auton("Tune PID", pid_tune),
    
    Auton("Right Side HALF WP", right_halfwp),
    Auton("Left Side HALF WP", left_halfwp),

    Auton("Right Side HALF WP", elims_right_halfwp),
    Auton("None", none),



    Auton("Left Side WP", left_wp),
    Auton("Left Side HALF WP", elims_left_halfwp),
    // Auton("Left Side HALF WP", left_halfwp),
    // Auton("Left Side WP", left_wp),
    // Auton("Left Side HALF WP", left_halfwp),
    // Auton("Left Side WP", old_left_wp),
    // Auton("Left Easy Colourwheel", left_easy_single_colour),
    // Auton("Right Easy Colourwheel", right_easy_single_colour),
    // Auton("Skills", skills)
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
  chassis.reset_pid_targets();
  chassis.reset_gyro();
  chassis.reset_drive_sensor();
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.
  SystemsCalc.resume();
  AutoTask.resume();

  ez::as::auton_selector.call_selected_auton(); // Calls selected auton from autonomous selector.
}


void opcontrol() {
  // AutoTask.suspend();
  // AutoTask.remove();
  set_intake(0);
  AutoTask.resume();
  SystemsCalc.resume();
  cont.resume();
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD);

  while (true) {
    chassis.tank();
    // printf("right: %f \n", chassis.right_eff());
    // printf("\n");
    // printf("left: %f \n", chassis.left_eff());
    // intake_control();

    pros::delay(10);
  }
}
