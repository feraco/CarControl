#include "CarControl.h"

// Create CarControl object with pin numbers for PWMA, PWMB, AIN, BIN, STBY, and modeSwitch
CarControl car(5, 6, 7, 8, 3, 2);

void setup() {
  car.setup();  // Call setup function to initialize the car
}

void loop() {
  int speed = 255;  // Set the speed of the car (0 to 255)
  
  car.moveForward(speed, 2000);  // Move forward at the specified speed for 2 seconds
  delay(1000);                   // Wait for 1 second

  car.moveBackward(speed, 2000);  // Move backward at the specified speed for 2 seconds
  delay(1000);                    // Wait for 1 second

  car.turnLeft(speed, 2000);  // Turn left at the specified speed for 2 seconds
  delay(1000);                 // Wait for 1 second

  car.turnRight(speed, 2000);  // Turn right at the specified speed for 2 seconds
  delay(1000);                 // Wait for 1 second

  car.turnAround();  // Perform a 180-degree turn
  delay(1000);       // Wait for 1 second
}
