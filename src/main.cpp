/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       hypatia                                                   */
/*    Created:      Wed Mar 08 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// drive_FL             motor         1               
// drive_FR             motor         10              
// drive_BL             motor         11              
// drive_BR             motor         19              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "Core.h"
#include "HolonomicDrivetrain.h"

int main() {
  vexcodeInit();
  //printf("%d", vex::thread::hardware_concurrency);  // Find out wether or not to use threads
  vex::thread driveThread = thread(Radix::HolonomicDrivetrain::driverControl);
}
