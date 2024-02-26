#include <CarControl.h>
#include <Ultrasonic.h>

// Motor control pins
int pwma = 3; // PWM control for motor A
int pwmb = 5; // PWM control for motor B
int ain = 2;  // Direction control for motor A
int bin = 4;  // Direction control for motor B
int stby = 6; // Standby
int clawPin = 11; // Pin for the servo controlling the claw

// Initialize CarControl object
CarControl car(pwma, pwmb, ain, bin, stby, 0); // 0 for modeSwitch if not used

void setup() {
  // Setup the car control
  car.setup();
  car.attachClaw(clawPin); // Attach the claw servo to its pin
}

void loop() {
  // Continuously check for obstacles
  car.checkObstacleInFront();
  int distance = car.getDistanceToObstacle();

  if (distance <= 5) {
    // If obstacle is closer than or equal to 5 cm, close the claw
    car.closeClaw();
  } else {
    // If obstacle is farther than 5 cm, open the claw
    car.openClaw();
  }

  delay(100); // Short delay before next loop iteration
}
