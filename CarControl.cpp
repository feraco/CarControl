/*
 * Title: CarControl.cpp
 * Author: Frederick Feraco
 * Affiliation: New York State Master Teacher
 * Description: This library provides functionalities for controlling the movement of a car 
 * robot with an Arduino. This file contains the implementation of the CarControl class.
 */
#include "CarControl.h"

// Constructor function for CarControl class, initializes the motor and sensor pins
CarControl::CarControl(int pwma, int pwmb, int ain, int bin, int stby, int modeSwitch) {
  // Assign the parameter values to the class variables
  _pwma = pwma;
  _pwmb = pwmb;
  _ain = ain;
  _bin = bin;
  _stby = stby;
  _modeSwitch = modeSwitch;
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

// Function to move the car forward for a specified duration
void CarControl::moveForward(int duration) {
  // Set motor direction to forward
  digitalWrite(_ain, HIGH);
  digitalWrite(_bin, HIGH);

  // Set motor power to high
  digitalWrite(_pwma, HIGH);
  digitalWrite(_pwmb, HIGH);

  // Wait for the specified duration
  delay(duration);

  // Stop the motors
  stopMotors();
}

// Function to move the car backward for a specified duration
void CarControl::moveBackward(int duration) {
  // Set motor direction to backward
  digitalWrite(_ain, LOW);
  digitalWrite(_bin, LOW);

  // Set motor power to high
  digitalWrite(_pwma, HIGH);
  digitalWrite(_pwmb, HIGH);

  // Wait for the specified duration
  delay(duration);

  // Stop the motors
  stopMotors();
}

// Function to turn the car left for a specified duration
void CarControl::turnLeft(int duration) {
  // Set motor directions to turn left
  digitalWrite(_ain, LOW);
  digitalWrite(_bin, HIGH);

  // Set motor power to high
  digitalWrite(_pwma, HIGH);
  digitalWrite(_pwmb, HIGH);

  // Wait for the specified duration
  delay(duration);

  // Stop the motors
  stopMotors();
}

// Function to turn the car right for a specified duration
void CarControl::turnRight(int duration) {
  // Set motor directions to turn right
  digitalWrite(_ain, HIGH);
  digitalWrite(_bin, LOW);

  // Set motor power to high
  digitalWrite(_pwma, HIGH);
  digitalWrite(_pwmb, HIGH);

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
  // Turn left for 1 second (adjust duration as needed)
  turnLeft(1000);
}

// Function to move the car forward at reduced speed for a specified duration
void CarControl::moveSlowForward(int duration) {
  // Set motor direction to forward
  digitalWrite(_ain, HIGH);
  digitalWrite(_bin, HIGH);

  // Set motor power to reduced speed (values range from 0 to 255)
  analogWrite(_pwma, 150);
  analogWrite(_pwmb, 150);

  // Wait for the specified duration
  delay(duration);

  // Stop the motors
  stopMotors();
}

// Function to create a custom movement pattern
void CarControl::customMovement(int ainState, int binState, int pwmaPower, int pwmbPower, int duration) {
  // Set custom motor directions
  digitalWrite(_ain, ainState);
  digitalWrite(_bin, binState);

  // Set custom motor power
  analogWrite(_pwma, pwmaPower);
  analogWrite(_pwmb, pwmbPower);

  // Wait for the specified duration
  delay(duration);

  // Stop the motors
  stopMotors();
}
