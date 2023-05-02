#include "HolonomicDrivetrain.h"

int HolonomicDrivetrain::driverControl() {

  while (true) {
    // Some variables
    float xDist = controller.Axis4.position(percent);
    float yDist = controller.Axis3.position(percent);
    float turn = controller.Axis1.position(percent);
    float power = sqrt(xDist * xDist + yDist * yDist);
    
    float angle;  // Radians, from 0 to PI going over the top, and 0 to -PI going around the bottom
    if (xDist == 0 && yDist == 0) {
      angle = 666;
    } else {
      angle = atan2(yDist, xDist); // If it is 666, the bot should not move
    }
    

    // Method 1
    /*
    float vX = power * cos(angle);
    float vY = power * sin(angle);

    frontLeft.setVelocity(vX + vY, vex::velocityUnits::pct);
    frontRight.setVelocity(vX - vY, vex::velocityUnits::pct);
    backLeft.setVelocity(vX - vY, vex::velocityUnits::pct);
    backRight.setVelocity(vX + vY, vex::velocityUnits::pct);
    */

    // Method 2
    float sine = sin(angle - M_PI / 4);
    float cosine = cos(angle - M_PI / 4);
    float maxPower = fmax(fabs(sine), fabs(cosine));

    float vFL, vFR, vBL, vBR;


    vFL = power * cosine / maxPower + turn;
    vFR = power * sine   / maxPower - turn;
    vBL = power * sine   / maxPower + turn;
    vBR = power * cosine / maxPower - turn;

    
    if (power + fabs(turn) > 100) {
      vFL /= power + turn;
      vFR /= power + turn;
      vBL /= power + turn;
      vBR /= power + turn;
    }

    printf("Angle: %f\nW1: %f\nW2: %f\nW3: %f\nW4: %f\n", angle, vFL, vFR, vBL, vBR);

    frontLeft.setVelocity(vFL, vex::velocityUnits::pct);
    frontRight.setVelocity(vFR, vex::velocityUnits::pct);
    backLeft.setVelocity(vBL, vex::velocityUnits::pct);
    backRight.setVelocity(vBR, vex::velocityUnits::pct);
    
    if (angle != 666) {
      frontLeft.spin(vex::forward);
      frontRight.spin(vex::forward);
      backLeft.spin(vex::forward);
      backRight.spin(vex::forward);
    } else {
      frontLeft.stop();
      frontRight.stop();
      backLeft.stop();
      backRight.stop();
    }

    vex::task::sleep(25);
  }

  /*
  while (active) {
    double x = controller.Axis4.position(percent);
    double y = controller.Axis3.position(percent);
    double turn = controller.Axis1.position(percent);

    double angle;
    if (y != 0 && x != 0) {
      angle = atan2(y, x);
    } else {
      angle = 888;
    }

    double power = hypot(x, y);

    double sine = sin(angle - M_PI / 4);
    double cosine = cos(angle - M_PI / 4);
    double maxPow = std::max(fabs(sine), fabs(cosine));

    frontLeft.setVelocity(power * cosine / maxPow + turn, vex::velocityUnits::pct);
    frontRight.setVelocity(power * sine / maxPow - turn, vex::velocityUnits::pct);
    backLeft.setVelocity(power * sine / maxPow + turn, vex::velocityUnits::pct);
    backRight.setVelocity(power * cosine / maxPow - turn, vex::velocityUnits::pct);
  }
  */
  
  return 0;
}

void HolonomicDrivetrain::drive(vex::directionType dir) {

}


void HolonomicDrivetrain::driveFor(vex::directionType dir, double distance, vex::distanceUnits units, bool waitForCompletion) {

}


void HolonomicDrivetrain::isDone() {

}


void HolonomicDrivetrain::isMoving() {

}


void HolonomicDrivetrain::setDriveVelocity(double velocity, vex::percentUnits units) {

}


void HolonomicDrivetrain::setDriveVelocity(double velocity, vex::velocityUnits units) {

}


void HolonomicDrivetrain::setStopping(vex::brakeType mode) {

}


void HolonomicDrivetrain::turn(vex::turnType dir) {

}


void HolonomicDrivetrain::turnFor(vex::turnType dir, double angle, vex::rotationUnits units, bool waitForCompletion) {

}


void HolonomicDrivetrain::stop() {

}


void HolonomicDrivetrain::stop(vex::brakeType mode) {

}