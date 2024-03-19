
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
  // Line sensor readings
  int leftSensor = car.getLineSensorLeft();
  int middleSensor = car.getLineSensorMiddle();
  int rightSensor = car.getLineSensorRight();

  // Threshold for detecting the black line
  int lineThreshold = 120; // Adjusted based on your sensor readings

  // Check for the opponent
  int distanceToOpponent = car.getDistanceToObstacle();
  if (distanceToOpponent < 15) {
    car.lightRGBForDuration(CRGB::Red, 500); // Red for aggressive forward movement
    car.moveForward(255, 50); // Move forward at full speed
  } else {
    // Determine the robot's movement based on the sensor readings
    if (middleSensor < lineThreshold) {
      // Middle sensor detects white surface - move forward
     // car.lightRGBForDuration(CRGB::Green, 500);
      car.moveForward(200, 50);
    } else {
      // Middle sensor detects black line - adjust direction
      if (leftSensor > lineThreshold) {
        // Left sensor detects white - turn left
        car.lightRGBForDuration(CRGB::Yellow, 500);
        car.turnLeft(200, 400);
      } else if (rightSensor > lineThreshold) {
        // Right sensor detects white - turn right
        car.lightRGBForDuration(CRGB::Blue, 500);
        car.turnRight(200, 400);
      } else {
        // All sensors detect black - back up and turn around
        car.lightRGBForDuration(CRGB::Purple, 500);
        car.moveBackward(200, 100);
        car.turnAround();
      }
    }
  }

  // Reset LED color to black after each action
  car.lightRGBForDuration(CRGB::Black, 500);
}
