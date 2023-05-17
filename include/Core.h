#pragma once
#include "vex.h"

namespace Radix {
  // Toggle between holonomic xdrive or mecanum drive
  #if 1
    #define RX_MECANUM
  #else
    #define RX_XDRIVE
  #endif


  // Main controller
  vex::controller controller1 = Controller1;
}