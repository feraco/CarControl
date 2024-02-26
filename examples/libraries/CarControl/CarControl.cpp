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
#define TRIG_PIN 13
#define ECHO_PIN 12
#include <FastLED.h>

// Define the number of LEDs and the data pin for the RGB LED
#define NUM_LEDS 1
#define DATA_PIN 4

CRGB leds[NUM_LEDS];// Initialize the ultrasonic sensor
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
  //   _carWasPickedUp = false;
   // myServo.attach(SERVO_PIN);
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    centerServo();
}


void CarControl::attachClaw(int pin) {
    _clawServoPin = pin;
    _clawServo.attach(_clawServoPin); // Attach the servo to the specified pin
}

void CarControl::openClaw() {
    _clawServo.write(0); // Replace 0 with the angle that corresponds to the open position
}

void CarControl::closeClaw() {
    _clawServo.write(180); // Replace 180 with the angle that corresponds to the closed position
}
// Setup function to initialize the IO pins
void CarControl::setup() {
  // Set the motor and standby pins as OUTPUT
  pinMode(_pwma, OUTPUT);
  pinMode(_pwmb, OUTPUT);
  pinMode(_bin, OUTPUT);
  pinMode(_ain, OUTPUT);
  pinMode(_stby, OUTPUT);
    FastLED.setBrightness(50);  // Set initial brightness

  // Set the motor pins to LOW and standby pin to HIGH
  digitalWrite(_pwma, LOW);
  digitalWrite(_stby, HIGH);
}
int CarControl::getLeftDistance() {
    lookLeft();  // Assuming you have a method to position the servo left
    delay(500);
    return getDistanceToObstacle();  // Assuming you have a method to get distance
}

int CarControl::getRightDistance() {
    lookRight(); // Assuming you have a method to position the servo right
    delay(500);
    return getDistanceToObstacle();  // Assuming you have a method to get distance
}

int CarControl::getCenterDistance() {
    centerServo(); // Assuming you have a method to position the servo center
    delay(500);
    return getDistanceToObstacle();  // Assuming you have a method to get distance
}
// Function to check for an obstacle in front
bool CarControl::checkObstacleInFront() {
    long distance = _ultrasonic.distanceRead();  // Get the distance reading
    if (distance < 10) {  // Assuming obstacle is considered within 10 cm
        _obstacleInFront = true;
    } else {
        _obstacleInFront = false;
    }
    return _obstacleInFront; // Return the obstacle status as a bool
}



// Function to get the distance to the nearest obstacle
int CarControl::getDistanceToObstacle() {
    return ultrasonic.distanceRead();  // Updated function call
}

// Function to read the value of the infrared sensor
int CarControl::getValueOfInfraredSensor() {
  return analogRead(IR_SENSOR_PIN);  // Read and return the value from IR sensor
}
void CarControl::attachSensorServo(int pin) {
    _sensorServo.attach(pin); // Attach the sensor servo to the specified pin
}
// Function to make the servo look left
void CarControl::lookLeft() {
    _sensorServo.write(0); // Adjust this angle as needed for your setup
}

void CarControl::lookRight() {
    _sensorServo.write(180); // Adjust this angle as needed for your setup
}
void CarControl::lightRGBForDuration(CRGB color, int duration) {
  leds[0] = color;
  FastLED.show();
  delay(duration);
  leds[0] = CRGB::Black; // Turn off the LED after the duration
  FastLED.show();
}
void CarControl::centerServo() {
    _sensorServo.write(90); // Assuming 90 degrees is the center position
}
// Function to move the car forward for a specified duration with speed
void CarControl::moveForward(int speed, int duration) {
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
void CarControl::moveBackward(int speed, int duration) {
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
void CarControl::turnRight(int speed, int duration) {
  // Set motor directions to turn right (opposite of left turn)
  digitalWrite(_ain, LOW);  // Motor A forward
  digitalWrite(_bin, HIGH); // Motor B backward

  // Set motor power to the specified speed
  analogWrite(_pwma, speed);
  analogWrite(_pwmb, speed);

  // Wait for the specified duration
  delay(duration);

  // Stop the motors
  stopMotors();
}

void CarControl::initLineSensors() {
    _rightSensorPin = RIGHT_SENSOR_PIN;
    _middleSensorPin = MIDDLE_SENSOR_PIN;
    _leftSensorPin = LEFT_SENSOR_PIN;
    pinMode(_rightSensorPin, INPUT);
    pinMode(_middleSensorPin, INPUT);
    pinMode(_leftSensorPin, INPUT);
}

void CarControl::followLineMultiSensor(int threshold) {
    int rightValue = analogRead(_rightSensorPin);
    int middleValue = analogRead(_middleSensorPin);
    int leftValue = analogRead(_leftSensorPin);

    if (middleValue < threshold) {
        moveForward(200, 100); // Move forward if line is under middle sensor
    } else if (rightValue < threshold) {
        turnLeft(200, 100); // Turn left if line is under right sensor
    } else if (leftValue < threshold) {
        turnRight(200, 100); // Turn right if line is under left sensor
    } else {
        stopMotors(); // Stop if no line is detected
    }
}

void CarControl::followLine(int threshold) {
    int leftValue = analogRead(_leftSensorPin);
    int middleValue = analogRead(_middleSensorPin);
    int rightValue = analogRead(_rightSensorPin);

    if (leftValue > threshold && middleValue > threshold && rightValue > threshold) {
        // All sensors are on the line
        moveForward(200, 100); // Adjust speed and duration as needed
    } else {
        // Adjust the direction based on which sensor is off the line
        if (leftValue <= threshold) {
            // Left sensor is off the line, turn right
            turnRight(150, 20); // Adjust turn speed and duration
        } else if (rightValue <= threshold) {
            // Right sensor is off the line, turn left
            turnLeft(150, 20); // Adjust turn speed and duration
        }
        // Add additional logic here if needed, e.g., for the middle sensor
    }
}




void CarControl::stopAtLine(int threshold) {
    int leftValue = analogRead(_leftSensorPin);
    int middleValue = analogRead(_middleSensorPin);
    int rightValue = analogRead(_rightSensorPin);

    if ( middleValue < threshold ) {
        stopMotors(); // Stop when a line is detected by any sensor
    }
}


void CarControl::followLineAvoidObstacle(int threshold, int obstacleDistanceThreshold) {
    if (getDistanceToObstacle() < obstacleDistanceThreshold) {
        turnRight(200, 500); // Turn right to avoid obstacle
    } else {
        followLine(threshold); // Continue following the line
    }
}


void CarControl::intersectionDecision(int threshold, bool (*detectIntersection)()) {
    if (detectIntersection()) {
        turnRight(200, 500); // Execute a turn at the intersection
    } else {
        followLine(threshold); // Continue following the line
    }
}

void CarControl::followLineUntilCondition(int threshold, unsigned long duration) {
    unsigned long startTime = millis();
    while (millis() - startTime < duration) {
        followLine(threshold); // Follow line for the specified duration
    }
    stopMotors();
}







// Function to turn the car right for a specified duration with speed
void CarControl::turnLeft(int speed, int duration) {
  // Set motor directions to turn right
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
  turnLeft(255, 400);  // Added a second argument for speed
}


// Function to move the car forward at reduced speed for a specified duration with speed
void CarControl::moveSlowForward(int speed, int duration) {
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
