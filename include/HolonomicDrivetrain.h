#pragma once
#include "vex.h"
#include <algorithm>

class HolonomicDrivetrain {

public:

  HolonomicDrivetrain(const vex::controller& controller, const vex::motor& frontLeft, const vex::motor& frontRight, const vex::motor& backLeft, const vex::motor& backRight)
   : controller(controller), frontLeft(frontLeft), frontRight(frontRight), backLeft(backLeft), backRight(backRight) {}

  int driverControl();
  void drive(vex::directionType dir);
  void driveFor(vex::directionType dir, double distance, vex::distanceUnits units, bool waitForCompletion=true);
  void isDone();
  void isMoving();
  void setDriveVelocity(double velocity, vex::percentUnits units);
  void setDriveVelocity(double velocity, vex::velocityUnits units);
  void setStopping(vex::brakeType mode);
  void turn(vex::turnType dir);
  void turnFor(vex::turnType dir, double angle, vex::rotationUnits units, bool waitForCompletion=true);
  void stop();
  void stop(vex::brakeType mode);

private:
  
  vex::brakeType stoppingMode = vex::brakeType::hold;

  vex::controller controller;

  vex::motor frontLeft, frontRight, backLeft, backRight;
  //    Front
  // +---------+
  // |m1  ^  m2|
  // |         |
  // |m3     m4|
  // +---------+
};