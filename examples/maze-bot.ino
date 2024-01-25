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
    delay(500);

    // Look straight ahead (center)
    car.centerServo();
    delay(500);
    int centerDistance = car.getDistanceToObstacle();
    Serial.print("Center Distance: ");
    Serial.println(centerDistance);

    // Look left
    car.lookLeft();
    delay(500);
    int leftDistance = car.getDistanceToObstacle();
    Serial.print("Left Distance: ");
    Serial.println(leftDistance);

    // Look right
    car.lookRight();
    delay(500);
    int rightDistance = car.getDistanceToObstacle();
    Serial.print("Right Distance: ");
    Serial.println(rightDistance);

    // Decision making based on distance measurements
    if (car.getCenterDistance() > 15 && (car.getCenterDistance() >= car.getLeftDistance() && c >= rightDistance)) {
        // Path is clear ahead and it's the longest path
        car.moveForward(100, 500);
        Serial.println("Moving Forward");
    } else if (leftDistance > 15 && leftDistance >= rightDistance) {
        // Left path is clearer or longer than the right path
        car.turnLeft(100, 500);
        Serial.println("Turning Left");
    } else if (rightDistance > 15) {
        // Right path is clear
        car.turnRight(100, 500);
        Serial.println("Turning Right");
    } else {
        // All paths are blocked, stop the motors
        car.stopMotors();
        car.lightRGBForDuration(CRGB::LightCoral, 5000);
        car.lightRGBForDuration(CRGB::MediumSpringGreen , 5000);

        Serial.println("All Paths Blocked, Stopping");
    }

    delay(1000); // Short delay before the next loop iteration
}
