#include "CarControl.h"

// Create CarControl object with pin numbers for PWMA, PWMB, AIN, BIN, STBY, and modeSwitch
CarControl car(5, 6, 7, 8, 3, 2);

void setup() {
  car.setup();  // Call setup function to initialize the car
}

void loop() {
  for (int i = 0; i < 3; i++) {  // Repeat the following block of code 3 times
    car.moveForward(1000);  // Move forward for 1 second
    delay(500);             // Wait for 0.5 seconds

    car.turnLeft(500);  // Turn left for 0.5 seconds
    delay(500);         // Wait for 0.5 seconds

    car.moveBackward(1000);  // Move backward for 1 second
    delay(500);              // Wait for 0.5 seconds

    car.turnRight(500);  // Turn right for 0.5 seconds
    delay(500);          // Wait for 0.5 seconds
  }
  
  car.stopMotors();  // Stop the motors
  delay(2000);       // Wait for 2 seconds before repeating the loop
}
