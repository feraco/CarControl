/* Function: moveForward(int speed, int duration)
 * Moves the car forward at a specified speed for a specified duration.
 * Example: car.moveForward(100, 2000); // Move forward at speed 100 for 2 seconds
 */

/* Function: moveBackward(int speed, int duration)
 * Moves the car backward at a specified speed for a specified duration.
 * Example: car.moveBackward(100, 2000); // Move backward at speed 100 for 2 seconds
 */

/* Function: turnLeft(int speed, int duration)
 * Turns the car left at a specified speed for a specified duration.
 * Example: car.turnLeft(100, 2000); // Turn left at speed 100 for 2 seconds
 */

/* Function: turnRight(int speed, int duration)
 * Turns the car right at a specified speed for a specified duration.
 * Example: car.turnRight(100, 2000); // Turn right at speed 100 for 2 seconds
 */

/* Function: stopMotors()
 * Stops all motors, bringing the car to a halt.
 * Example: car.stopMotors(); // Stop the car immediately
 */

/* Function: lightRGBForDuration(CRGB color, int duration)
 * Lights up an RGB LED in a specified color for a specified duration.
 * Example: car.lightRGBForDuration(CRGB::Red, 5000); // Light the LED in red for 5 seconds
 */

/* Function: attachClaw(int pin)
 * Attaches a claw servo to a specified pin.
 * Example: car.attachClaw(9); // Attach the claw servo to pin 9
 */

/* Function: openClaw()
 * Opens the claw by setting the servo to a specific angle.
 * Example: car.openClaw(); // Opens the claw
 */

/* Function: closeClaw()
 * Closes the claw by setting the servo to a specific angle.
 * Example: car.closeClaw(); // Closes the claw
 */

/* Function: setup()
 * Initializes the IO pins for the motors and sets initial conditions.
 * Example: car.setup(); // Call in the setup() to initialize car's motors and sensors
 */

/* Function: getLeftDistance()
 * Measure the distance to an obstacle from the left.
 * Example: int leftDistance = car.getLeftDistance(); // Get distance to the left
 */

/* Function: getRightDistance()
 * Measure the distance to an obstacle from the right.
 * Example: int rightDistance = car.getRightDistance(); // Get distance to the right
 */

/* Function: getCenterDistance()
 * Measure the distance to an obstacle from the center.
 * Example: int centerDistance = car.getCenterDistance(); // Get distance straight ahead
 */

/* Function: checkObstacleInFront()
 * Checks for an obstacle in front of the car using an ultrasonic sensor.
 * Example: if(car.checkObstacleInFront()) { 
 *            // Code to execute if there is an obstacle in front
 *         }
 */

/* Function: getDistanceToObstacle()
 * Returns the distance to the nearest obstacle using an ultrasonic sensor.
 * Example: int distance = car.getDistanceToObstacle(); // Get distance to the nearest obstacle
 */


#include <CarControl.h>
#include <Ultrasonic.h>
#include <FastLED.h>
#include <Servo.h>
#include "MPU6050.h"
#include <Ultrasonic.h>

// Define pin numbers for motors and other components

#define CLAWSERVOPIN 11
#define SENSORSERVOPIN 10
#define RIGHT_SENSOR_PIN A1
#define MIDDLE_SENSOR_PIN A2
#define LEFT_SENSOR_PIN A3

// Create an instance of the CarControl class
CarControl car(5, 6, 7, 8, 3, 2);

void setup() {
  Serial.begin(9600);
  // Initialize the car and its components
  car.setup();
  car.attachClaw(CLAWSERVOPIN);
  car.attachSensorServo(SENSORSERVOPIN);
  car.initLineSensors();

  // Set initial state of the car
  car.stopMotors(); // Ensure the car is stationary at startup
}



void loop() {
// Continuously check for obstacles and follow the black line
car.checkObstacleInFront();

if (car.getDistanceToObstacle() < 10) { // If obstacle is closer than 10 cm
car.stopMotors(); // Stop the car
// Removed the turnRight command to ensure the car stops when an obstacle is detected
} else {
car.followLine(500); // Follow the black line using line sensor feedback
}

delay(100); // Short delay before next loop iteration
}