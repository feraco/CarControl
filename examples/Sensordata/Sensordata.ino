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
  // Get the distance to the nearest obstacle
  int distanceToObstacle = car.getDistanceToObstacle();

  // Get the values from the line sensors
  int lineSensorLeft = car.getLineSensorLeft();
  int lineSensorMiddle = car.getLineSensorMiddle();
  int lineSensorRight = car.getLineSensorRight();
float batteryLevel = car.getBatteryLevel();

// Print the battery level to the serial port
Serial.print("Battery level: ");
Serial.println(batteryLevel);
  // Print the values to the serial port
  Serial.print("Distance to obstacle: ");
  Serial.println(distanceToObstacle);
  Serial.print("Line sensor left: ");
  Serial.println(lineSensorLeft);
  Serial.print("Line sensor middle: ");
  Serial.println(lineSensorMiddle);
  Serial.print("Line sensor right: ");
  Serial.println(lineSensorRight);

  // Delay for 100 milliseconds before the next loop iteration
  delay(100);
}