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
// Define notes for the Star Wars theme
#define NOTE_A4  440
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_C4  261
#define NOTE_G4  392
#define NOTE_F5  698
#define NOTE_E5  659
#define NOTE_A5  880
#define NOTE_G5  784
#define NOTE_D5  587
#define NOTE_D4  294
#define NOTE_C5  523
#define NOTE_GS4 415


// Define the duration of notes
int noteDurations[] = {500, 500, 500, 350, 150, 500, 500, 500, 650, 150, 500};

void CarControl::playStarWars() {
    int melody[] = {
        NOTE_A4, NOTE_A4, NOTE_A4, NOTE_F4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_C5, NOTE_A4,
        NOTE_E5, NOTE_E5, NOTE_E5, NOTE_F5, NOTE_C5, NOTE_GS4, NOTE_F4, NOTE_C5, NOTE_A4
    };

    // iterate over the notes of the melody:
    for (int thisNote = 0; thisNote < 18; thisNote++) {
        // to calculate the note duration, take one second divided by the note type.
        // e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(_buzzerPin, melody[thisNote], noteDuration);

        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        // stop the tone playing:
        noTone(_buzzerPin);
    }
}

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

void CarControl::attachBuzzer(int buzzerPin = 11) {
  _buzzerPin = buzzerPin;
  pinMode(_buzzerPin, OUTPUT);
}

void CarControl::beep(int pattern) {
  switch (pattern) {
    case 1:
      singleBeep();
      break;
    case 2:
      doubleBeep();
      break;
    // Additional cases for more patterns...
  }
}

void CarControl::singleBeep() {
  digitalWrite(_buzzerPin, HIGH);
  delay(100); // 100 ms beep
  digitalWrite(_buzzerPin, LOW);
}

void CarControl::doubleBeep() {
  for (int i = 0; i < 2; i++) {
    digitalWrite(_buzzerPin, HIGH);
    delay(100);
    digitalWrite(_buzzerPin, LOW);
    delay(100);
  }
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

int CarControl::getLineSensorLeft() {
    return analogRead(A2); // Left sensor on pin A2
}

int CarControl::getLineSensorMiddle() {
    return analogRead(A1); // Middle sensor on pin A1
}

int CarControl::getLineSensorRight() {
    return analogRead(A0); // Right sensor on pin A0
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
void CarControl::checkObstacleInFront() {
    long distance = ultrasonic.distanceRead();  // Updated function call
    if (distance < 10) {  // Assuming obstacle is considered within 10 cm
        _obstacleInFront = true;
    } else {
        _obstacleInFront = false;
    }
}
float CarControl::getBatteryLevel() {
    int sensorValue = analogRead(_batteryPin); // Read the analog value from battery pin
    float voltage = sensorValue * (5.0 / 1023.0) * ((10 + 1.5) / 1.5); // Convert to voltage
    // Calculate battery percentage
    float batteryPercentage = (voltage - _batteryMinVoltage) / (_batteryMaxVoltage - _batteryMinVoltage) * 100;
    batteryPercentage = constrain(batteryPercentage, 0, 100); // Constrain between 0 to 100%
    return batteryPercentage;
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
  turnLeft(1000, 255);  // Added a second argument for speed
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
