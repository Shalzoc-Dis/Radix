#pragma once
#include "vex.h"
#include <algorithm>
#include "Core.h"

namespace Radix{ namespace HolonomicDrivetrain {

  // Functions
  int driverControl();

  void setDriveVelocity(double velocity, vex::percentUnits units);
  void setDriveVelocity(double velocity, vex::velocityUnits units);
  void drive(vex::directionType dir);
  void driveFor(vex::directionType dir, double distance, vex::distanceUnits units, bool waitForCompletion=true);

  void setTurnVelocity(double velocity, vex::percentUnits units);
  void setTurnVelocity(double velocity, vex::velocityUnits units);
  void turn(vex::turnType dir);
  void turnFor(vex::turnType dir, double angle, vex::rotationUnits units, bool waitForCompletion=true);

  bool isDone();
  bool isMoving();

  void setStopping(vex::brakeType mode);
  void stop();
  void stop(vex::brakeType mode);

  // Global variables
  int updateTick = 25;
  vex::brakeType stoppingMode = vex::brakeType::hold;

  //    Front
  // +---------+
  // |m1  ^  m2|
  // |         |
  // |m3     m4|
  // +---------+
} }