
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
  // Check for obstacles in front of the robot
  car.checkObstacleInFront();

  // If an obstacle is detected, stop the robot
  if (car.getDistanceToObstacle() < 10) {
    car.stopMotors();
  } else {
    // Move the robot forward at full speed
    car.moveForward(255, 100);

    // If a black line is detected, stop the robot, move backwards, turn around, and then move forward again at full speed
    if (car.getLineSensorMiddle() < 1000) {
      car.stopMotors();
      car.moveBackward(255, 100);
      car.turnAround();
      car.moveForward(255, 100);
    }

    // Check for other bots using the ultrasonic sensor
    int distanceToBot = car.getDistanceToObstacle();

    // If another bot is detected, push it out of the ring
    if (distanceToBot < 10) {
      car.turnRight(255, 100);
      car.moveForward(255, 100);
      car.turnLeft(255, 100);
    }
  }

  // Delay for 100 milliseconds before the next loop iteration
  delay(100);
}