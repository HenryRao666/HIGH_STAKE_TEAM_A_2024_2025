/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       zhongshunrao                                              */
/*    Created:      9/27/2024, 7:33:42 AM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "auton.hpp"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
motor rightFront = motor(PORT18, ratio18_1, false);
motor rightMiddle = motor(PORT19, ratio18_1, false);
motor rightBack = motor(PORT20, ratio18_1, false);
motor leftFront = motor(PORT13, ratio18_1, true);
motor leftMiddle = motor(PORT12, ratio18_1, true);
motor leftBack = motor(PORT11, ratio18_1, true);
motor Fintake = motor(PORT3, false);
motor Bintake = motor(PORT2, ratio18_1, false);

// Create motor groups for each side of the drive train
motor_group rightDrive = motor_group(rightFront, rightMiddle, rightBack);
motor_group leftDrive = motor_group(leftFront, leftMiddle, leftBack);

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  runAuton();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    controller Controller1 = controller();
    // Get the vertical axis value from the left joystick for forward/backward
    double driveY = Controller1.Axis3.position();
    // Get the horizontal axis value from the right joystick for turning
    double turnX = Controller1.Axis1.position();

    // Calculate motor speeds for left and right sides
    double leftSpeed = driveY + turnX;
    double rightSpeed = driveY - turnX;

    // Set the left and right motor velocities
    drive(leftSpeed, rightSpeed);

    // Intake controls
    if(Controller1.ButtonR2.pressing()) {
        Bintake.spin(reverse, 100, percent);
        Fintake.spin(forward, 100, percent);
    } else if(Controller1.ButtonR1.pressing()) {
        Bintake.spin(forward, 100, percent);
        Fintake.spin(reverse, 100, percent);
    } else {
        Bintake.stop();
        Fintake.stop();
    }

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
