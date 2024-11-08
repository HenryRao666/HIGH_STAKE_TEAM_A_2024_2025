#pragma once

#include "vex.h"

void drive(double left, double right){
  leftDrive.spin(forward, left*120, voltageUnits::mV);
  rightDrive.spin(forward, right*120, voltageUnits::mV);
}

struct pid_consts {
    double kP, kI, kD;
}pid_drive_constants, pid_turn_constants;

void pidInit(){
    pid_drive_constants = {0.1, 0.0, 0.0};
    pid_turn_constants = {5, 0.0, 0.0};
}

void pidDrive(double target, int timeout, const pid_consts &constants=pid_drive_constants){
    double error = target;
    double prevError = 0;
    double integral = 0;
    double derivative = 0;
    double power = 0;
    
    timer Timer;
    Timer.reset();

    leftDrive.resetPosition();
    rightDrive.resetPosition();
    
    while(Timer.time(msec) < timeout){
        error = target - (leftDrive.position(degrees) + rightDrive.position(degrees))/2;
        
        integral += error;
        derivative = error - prevError;
        
        power = constants.kP * error + constants.kI * integral + constants.kD * derivative;
        
        drive(power, power);
        
        prevError = error;
        wait(20, msec);
    }
    
    leftDrive.stop();
    rightDrive.stop();
}

void pidTurn(double target, int timeout, const pid_consts &constants=pid_turn_constants){

}