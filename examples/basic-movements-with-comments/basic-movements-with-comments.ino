

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
  // Move Forward
  car.moveForward(255, 2000);
  Serial.println("Moving forward at maximum speed for 2 seconds");
  delay(2000); // Wait for 2 seconds
  car.lightRGBForDuration(CRGB::Blue, 1000); // Blue LED for 1 second
  delay(1000);

  // Move Backward
  car.moveBackward(200, 1500);
  Serial.println("Moving backward at speed 200 for 1.5 seconds");
  delay(1500);
  car.lightRGBForDuration(CRGB::Green, 1000); // Green LED for 1 second
  delay(1000);

  // Turn Left
  car.turnLeft(180, 1000);
  Serial.println("Turning left at speed 180 for 1 second");
  delay(1000);
  car.lightRGBForDuration(CRGB::Red, 1000); // Red LED for 1 second
  delay(1000);

  // Turn Right
  car.turnRight(150, 500);
  Serial.println("Turning right at speed 150 for 0.5 seconds");
  delay(500);
  car.lightRGBForDuration(CRGB::Yellow, 1000); // Yellow LED for 1 second
  delay(1000);

  // Stop Motors
  car.stopMotors();
  Serial.println("Stopping motors");
  delay(1000);
  car.lightRGBForDuration(CRGB::Purple, 1000); // Purple LED for 1 second
  delay(1000);

  // Stop Time
  car.stopTime(1000);
  Serial.println("Car in standby for 1 second");
  delay(1000);
  car.lightRGBForDuration(CRGB::Orange, 1000); // Orange LED for 1 second
  delay(1000);

  
  car.lightRGBForDuration(CRGB::White, 1000); // White LED for 1 second
  delay(1000);

  
  car.lightRGBForDuration(CRGB::Blue, 1000); // Blue LED for 1 second
  delay(1000);

  // Follow Line
  car.followLine(1000);
  Serial.println("Following line");
  delay(2000); // Assume it follows for 2 seconds
  car.lightRGBForDuration(CRGB::Green, 1000); // Green LED for 1 second
  delay(1000);

  // Stop At Line
  car.stopAtLine(1000);
  Serial.println("Stopping at line");
  delay(2000); // Assume it stops for 2 seconds
  car.lightRGBForDuration(CRGB::Red, 1000); // Red LED for 1 second
  delay(1000);

  // Custom Movement
  car.customMovement(true, false, 200, 150, 2500);
  Serial.println("Custom movement: Motor A forward, Motor B backward");
  delay(2500);
  car.lightRGBForDuration(CRGB::Yellow, 1000); // Yellow LED for 1 second
  delay(1000);

  
  car.stopTime(500); // Wait for 0.5 seconds

 // Get Distance to Obstacle
  Serial.println("Getting Distance to Obstacle");
  int distance = car.getDistanceToObstacle(); // Get the distance to the nearest obstacle
  Serial.print("Distance to obstacle: ");
  Serial.println(distance);
  car.lightRGBForDuration(CRGB::Yellow, 500); // Turn LED yellow for 0.5 seconds
  car.stopTime(500); // Wait for 0.5 seconds

  // Look Left
  Serial.println("Looking Left");
  car.lookLeft(); // Turn the sensor left
  car.lightRGBForDuration(CRGB::Blue, 500); // Turn LED blue for 0.5 seconds
  car.stopTime(500); // Wait for 0.5 seconds

  // Look Right
  Serial.println("Looking Right");
  car.lookRight(); // Turn the sensor right
  car.lightRGBForDuration(CRGB::Green, 500); // Turn LED green for 0.5 seconds
  car.stopTime(500); // Wait for 0.5 seconds

  // Center Servo
  Serial.println("Centering Servo");
  car.centerServo(); // Bring the servo to the center position
  car.lightRGBForDuration(CRGB::Red, 500); // Turn LED red for 0.5 seconds
  car.stopTime(500); // Wait for 0.5 seconds

  // Get Left Line Sensor Value
  Serial.println("Getting Left Line Sensor Value");
  int leftSensorValue = car.getLineSensorLeft(); // Get left line sensor reading
  Serial.print("Left Sensor Value: ");
  Serial.println(leftSensorValue);
  car.lightRGBForDuration(CRGB::Blue, 500); // Turn LED blue for 0.5 seconds
  car.stopTime(500); // Wait for 0.5 seconds

  // Get Middle Line Sensor Value
  Serial.println("Getting Middle Line Sensor Value");
  int middleSensorValue = car.getLineSensorMiddle(); // Get middle line sensor reading
  Serial.print("Middle Sensor Value: ");
  Serial.println(middleSensorValue);
  car.lightRGBForDuration(CRGB::Green, 500); // Turn LED green for 0.5 seconds
  car.stopTime(500); // Wait for 0.5 seconds

  // Get Right Line Sensor Value
  Serial.println("Getting Right Line Sensor Value");
  int rightSensorValue = car.getLineSensorRight(); // Get right line sensor reading
  Serial.print("Right Sensor Value: ");
  Serial.println(rightSensorValue);
  car.lightRGBForDuration(CRGB::Red, 500); // Turn LED red for 0.5 seconds
  car.stopTime(500); // Wait for 0.5 seconds

  // Continue with other commands or loop back as needed

  // Get Battery Level
  Serial.println("Getting Battery Level");
  float batteryLevel = car.getBatteryLevel(); // Get the current battery level percentage
  Serial.print("Battery level: ");
  Serial.print(batteryLevel);
  Serial.println("%");
  car.lightRGBForDuration(CRGB::Orange, 500); // Turn LED orange for 0.5 seconds
  car.stopTime(500); // Wait for 0.5 seconds


  
}
