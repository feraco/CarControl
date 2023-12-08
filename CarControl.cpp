/*
 * Title: CarControl.cpp
 * Author: Frederick Feraco
 * Affiliation: New York State Master Teacher
 * Description: This library provides functionalities for controlling the movement of a car 
 * robot with an Arduino. This file contains the implementation of the CarControl class.
 */
#include "CarControl.h"
// Additional includes for sensor readings
#include <Ultrasonic.h>  // Assuming use of Ultrasonic sensor for distance measurement

// Define pins for Ultrasonic sensor
#define TRIG_PIN 9
#define ECHO_PIN 10

// Initialize the ultrasonic sensor
Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN);

// Define pin for Infrared sensor
#define IR_SENSOR_PIN A0

// Class variables for new functionalities
bool _obstacleInFront;
// Constructor function for CarControl class, initializes the motor and sensor pins
CarControl::CarControl(int pwma, int pwmb, int ain, int bin, int stby, int modeSwitch) {
  // Assign the parameter values to the class variables
  _pwma = pwma;
  _pwmb = pwmb;
  _ain = ain;
  _bin = bin;
  _stby = stby;
  _modeSwitch = modeSwitch;
    pinMode(IR_SENSOR_PIN, INPUT);
     _obstacleInFront = false;
     _carWasPickedUp = false;
   
}

// Setup function to initialize the IO pins
void CarControl::setup() {
  // Set the motor and standby pins as OUTPUT
  pinMode(_pwma, OUTPUT);
  pinMode(_pwmb, OUTPUT);
  pinMode(_bin, OUTPUT);
  pinMode(_ain, OUTPUT);
  pinMode(_stby, OUTPUT);

  // Set the motor pins to LOW and standby pin to HIGH
  digitalWrite(_pwma, LOW);
  digitalWrite(_stby, HIGH);
}

// Function to check for an obstacle in front
void CarControl::checkObstacleInFront() {
  long distance = ultrasonic.Ranging(CM);  // Get distance in centimeters
  if (distance < 10) {  // Assuming obstacle is considered within 10 cm
    _obstacleInFront = true;
  } else {
    _obstacleInFront = false;
  }
}

// Function to get the distance to the nearest obstacle
int CarControl::getDistanceToObstacle() {
    return ultrasonic.distanceCm();  // Updated function call
}

// Function to read the value of the infrared sensor
int CarControl::getValueOfInfraredSensor() {
  return analogRead(IR_SENSOR_PIN);  // Read and return the value from IR sensor
}

// Function to check if the car was picked up

// Function to move the car forward for a specified duration with speed
void CarControl::moveForward(int duration, int speed) {
  // Set motor direction to forward
  digitalWrite(_ain, HIGH);
  digitalWrite(_bin, HIGH);

  // Set motor power to the specified speed
  analogWrite(_pwma, speed);
  analogWrite(_pwmb, speed);

  // Wait for the specified duration
  delay(duration);

  // Stop the motors
  stopMotors();
}

// Function to move the car backward for a specified duration with speed
void CarControl::moveBackward(int duration, int speed) {
  // Set motor direction to backward
  digitalWrite(_ain, LOW);
  digitalWrite(_bin, LOW);

  // Set motor power to the specified speed
  analogWrite(_pwma, speed);
  analogWrite(_pwmb, speed);

  // Wait for the specified duration
  delay(duration);

  // Stop the motors
  stopMotors();
}

// Function to turn the car left for a specified duration with speed
void CarControl::turnLeft(int duration, int speed) {
  // Set motor directions to turn left
  digitalWrite(_ain, LOW);
  digitalWrite(_bin, HIGH);

  // Set motor power to the specified speed
  analogWrite(_pwma, speed);
  analogWrite(_pwmb, speed);

  // Wait for the specified duration
  delay(duration);

  // Stop the motors
  stopMotors();
}

// Function to turn the car right for a specified duration with speed
void CarControl::turnRight(int duration, int speed) {
  // Set motor directions to turn right
  digitalWrite(_ain, HIGH);
  digitalWrite(_bin, LOW);

  // Set motor power to the specified speed
  analogWrite(_pwma, speed);
  analogWrite(_pwmb, speed);

  // Wait for the specified duration
  delay(duration);

  // Stop the motors
  stopMotors();
}

// Function to stop the motors
void CarControl::stopMotors() {
  // Set motor power to low
  digitalWrite(_pwma, LOW);
  digitalWrite(_pwmb, LOW);
}

// Function to put the car in standby mode for a specified duration
void CarControl::stopTime(int mS) {
  // Set standby pin to low (standby mode)
  digitalWrite(_stby, LOW);

  // Wait for the specified duration
  delay(mS);

  // Set standby pin to high (active mode)
  digitalWrite(_stby, HIGH);
}

// Function to make the car perform a 180-degree turn
void CarControl::turnAround() {
  // Turn left for 1 second at a default speed (adjust duration and speed as needed)
  turnLeft(1000, 255);  // Added a second argument for speed
}


// Function to move the car forward at reduced speed for a specified duration with speed
void CarControl::moveSlowForward(int duration, int speed) {
  // Set motor direction to forward
  digitalWrite(_ain, HIGH);
  digitalWrite(_bin, HIGH);

  // Set motor power to the specified speed
  analogWrite(_pwma, speed);
  analogWrite(_pwmb, speed);

  // Wait for the specified duration
  delay(duration);

  // Stop the motors
  stopMotors();
}

// Function to create a custom movement pattern with speed
// Function to create a custom movement pattern
void CarControl::customMovement(bool forwardA, bool forwardB, int speedA, int speedB, int duration) {
  // Set motor A direction to forward or backward based on forwardA
  digitalWrite(_ain, forwardA ? HIGH : LOW);

  // Set motor B direction to forward or backward based on forwardB
  digitalWrite(_bin, forwardB ? HIGH : LOW);

  // Set motor A power to the specified speed (0-255)
  analogWrite(_pwma, speedA);

  // Set motor B power to the specified speed (0-255)
  analogWrite(_pwmb, speedB);

  // Wait for the specified duration in milliseconds
  delay(duration);

  // Stop the motors after the duration has passed
  stopMotors();
}
