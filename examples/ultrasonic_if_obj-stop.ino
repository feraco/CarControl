#include <CarControl.h>
#include <Ultrasonic.h>

// Motor control pins
int pwma = 3; // PWM control for motor A
int pwmb = 5; // PWM control for motor B
int ain = 2;  // Direction control for motor A
int bin = 4;  // Direction control for motor B
int stby = 6; // Standby

// Initialize CarControl object
CarControl car(pwma, pwmb, ain, bin, stby, 0); // 0 for modeSwitch if not used

void setup() {
  // Setup the car control
  car.setup();
}

void loop() {
  // Continuously check for obstacles
  car.checkObstacleInFront();

  if (car.getDistanceToObstacle() < 10) { // If obstacle is closer than 10 cm
    car.stopMotors(); // Stop the car
    // Removed the turnRight command to ensure the car stops when an obstacle is detected
  } else {
    car.moveForward(255, 100); // Move forward at full speed for 100ms
  }

  delay(100); // Short delay before next loop iteration
}
