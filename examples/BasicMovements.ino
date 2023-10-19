#include "CarControl.h"

// Create CarControl object with pin numbers for PWMA, PWMB, AIN, BIN, STBY, and modeSwitch
CarControl car(5, 6, 7, 8, 3, 2);

void setup() {
  car.setup();  // Call setup function to initialize the car
}

void loop() {
  car.moveForward(2000);  // Move forward for 2 seconds
  delay(1000);            // Wait for 1 second

  car.moveBackward(2000);  // Move backward for 2 seconds
  delay(1000);             // Wait for 1 second

  car.turnLeft(2000);  // Turn left for 2 seconds
  delay(1000);         // Wait for 1 second

  car.turnRight(2000);  // Turn right for 2 seconds
  delay(1000);          // Wait for 1 second

  car.turnAround();  // Perform a 180-degree turn
  delay(1000);       // Wait for 1 second
}
