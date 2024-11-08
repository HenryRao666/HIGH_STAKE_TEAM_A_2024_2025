#pragma once

#include "pid.hpp"

void runAuton(){
    drive(100,-100);
    wait(3000,msec);
    drive(0,0);
}