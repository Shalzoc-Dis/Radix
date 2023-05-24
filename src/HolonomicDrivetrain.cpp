#include "HolonomicDrivetrain.h"
using namespace Radix;

int HolonomicDrivetrain::driverControl() {

  while (true) {
    // Some variables
    // xDist and yDist range from -100 to 100 and represent the left joystick position
    float xDist = Controller1.Axis4.position(percent);
    float yDist = Controller1.Axis3.position(percent);
    // This can be changed if the robot moves without input due to interferance returning low joystick values that should be ignored.
    int translateBuffer = 1;
    // turn is the horizontal motion of the right joystick position, ranging from -100 to 100 and indicates with what speed the bot should turn
    float turn = Controller1.Axis1.position(percent);
    // Same as translate buffer, but for turns
    int turnBuffer = 1;
    // This is the power, or speed, the robot should drive at.
    double power = sqrt(xDist * xDist + yDist * yDist);
    
    float angle = 0;  // Radians, from 0 to PI going over the top, and 0 to -PI going around the bottom
    bool shouldTranslate;
    // Checks wether or not the robot should be moving
    if (fabs(xDist) < translateBuffer && fabs(yDist) < translateBuffer) {
      shouldTranslate = false;
    } else {
      shouldTranslate = true;
      angle = atan2(yDist, xDist);
    }

    DEBUG_ONLY(printf("Angle %f\n\n", angle))
    DEBUG_ONLY(this_thread::sleep_for(10))

    // Some short hand
    #ifdef RX_MECANUM // For a Mecanum drive
      double sine = sin(angle - M_PI / 4);
      double cosine = cos(angle - M_PI / 4);
    #elif RX_XDRIVE // For an Xdrive
      float sine = sin(angle);
      float cosine = cos(angle);
    #endif

    DEBUG_ONLY(printf("\nsine: %f cosine: %f\n\n", sine, cosine))
    DEBUG_ONLY(this_thread::sleep_for(15))

    // Change the amount to turn based on the buffer
    //  FIXME the robot is not turning
    if(fabs(turn) < turnBuffer)
      turn = 0;

    // Calculate the largest thing this evaluates to
    double maxPower = fmax(fabs(sine), fabs(cosine));
    // Variables for the velocities of the individual motors
    double vFL, vFR, vBL, vBR;

    // Calculate the required velocity of the motors
    vFL = power * cosine / (maxPower + turn);
    vFR = power * sine   / (maxPower - turn);
    vBL = power * sine   / (maxPower + turn);
    vBR = power * cosine / (maxPower - turn);

    // Normalise the power such that does not exceed the motors' capabilities
    // FIXME - Suspicion that the 11A max for the motors is exceeded anyway. The 100 seems arbitrary
    // THIS CODE IS EVIL. IT WSA USELESS AND CAUSED THE MOTORS TO LOCK UP WHEN APPROACHING MAX SPEED. COST ME DAYS (at least when purely translating)
    if (power + fabs(turn) > 100) {
      vFL /= power + turn;
      vFR /= power + turn;
      vBL /= power + turn;
      vBR /= power + turn;
      DEBUG_ONLY(printf("\n--Normalised--\n\n"))
      // FIXME This normalises to very low values, not the right ones
    }

    //printf("Angle: %f W1: %f  W2: %f  W3: %f  W4: %f\n", angle, vFL, vFR, vBL, vBR);
    //printf("Angle: %f\nxDist: %f\nyDist: %f\npower: %f\n", angle, xDist, yDist, power);

    DEBUG_ONLY(printf("\nshouldTranslate %i\n\n", shouldTranslate))
    DEBUG_ONLY(printf("actVelFLpct %f | simVelFLpct %f\nactVelFRpct %f | simVelFRpct %f\nactVelBLpct %f | simVelBLpct %f\nactVelBRpct %f | simVelBRpct %f\n\n-----------\n", drive_FL.velocity(pct), vFL, drive_FR.velocity(pct), vFR, drive_BL.velocity(pct), vBL, drive_BR.velocity(pct), vBR))

    
    if (shouldTranslate) {
      drive_FL.setVelocity(vFL, vex::velocityUnits::pct);
      drive_FR.setVelocity(vFR, vex::velocityUnits::pct);
      drive_BL.setVelocity(vBL, vex::velocityUnits::pct);
      drive_BR.setVelocity(vBR, vex::velocityUnits::pct);

      drive_FL.spin(vex::forward);
      drive_FR.spin(vex::forward);
      drive_BL.spin(vex::forward);
      drive_BR.spin(vex::forward);
    } else {
      drive_FL.stop();
      drive_FR.stop();
      drive_BL.stop();
      drive_BR.stop();
    }

    this_thread::sleep_for(/*HolonomicDrivetrain::updateTick*/100);
  }

  

  /*
  while (active) {
    double x = controller1.Axis4.position(percent);
    double y = controller1.Axis3.position(percent);
    double turn = controller1.Axis1.position(percent);

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

    drive_FL.setVelocity(power * cosine / maxPow + turn, vex::velocityUnits::pct);
    drive_FR.setVelocity(power * sine / maxPow - turn, vex::velocityUnits::pct);
    drive_BL.setVelocity(power * sine / maxPow + turn, vex::velocityUnits::pct);
    drive_BR.setVelocity(power * cosine / maxPow - turn, vex::velocityUnits::pct);
  }
  */
  
  return 0;
}


void HolonomicDrivetrain::setDriveVelocity(double velocity, vex::percentUnits units) {

}


void HolonomicDrivetrain::setDriveVelocity(double velocity, vex::velocityUnits units) {

}


void HolonomicDrivetrain::drive(vex::directionType dir) {

}


void HolonomicDrivetrain::driveFor(vex::directionType dir, double distance, vex::distanceUnits units, bool waitForCompletion) {

}




void HolonomicDrivetrain::setTurnVelocity(double velocity, vex::percentUnits units) {

}


void HolonomicDrivetrain::setTurnVelocity(double velocity, vex::velocityUnits units) {

}


void HolonomicDrivetrain::turn(vex::turnType dir) {

}


void HolonomicDrivetrain::turnFor(vex::turnType dir, double angle, vex::rotationUnits units, bool waitForCompletion) {

}





bool HolonomicDrivetrain::isDone() {
  if (drive_FL.isDone() && drive_FR.isDone() && drive_BL.isDone() && drive_BR.isDone())
    return true;
  else
    return false;
}


bool HolonomicDrivetrain::isMoving() {
  if (drive_FL.isSpinning() || drive_FR.isSpinning() || drive_BL.isSpinning() || drive_BR.isSpinning())
    return true;
  else
    return false;
}





/// Sets the stopping mode for the drivetrain
void HolonomicDrivetrain::setStopping(vex::brakeType mode) {
  drive_FL.setStopping(HolonomicDrivetrain::stoppingMode);
  drive_FR.setStopping(HolonomicDrivetrain::stoppingMode);
  drive_BL.setStopping(HolonomicDrivetrain::stoppingMode);
  drive_BR.setStopping(HolonomicDrivetrain::stoppingMode);
}


void HolonomicDrivetrain::stop() {
  drive_FL.stop();
  drive_FR.stop();
  drive_BL.stop();
  drive_BR.stop();
}


void HolonomicDrivetrain::stop(vex::brakeType mode) {
  drive_FL.stop(mode);
  drive_FR.stop(mode);
  drive_BL.stop(mode);
  drive_BR.stop(mode);
}