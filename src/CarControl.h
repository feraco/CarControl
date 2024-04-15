/*
 * Title: CarControl.cpp
 * Author: Frederick Feraco
 * Affiliation: New York State Master Teacher
 * Description: This library provides functionalities for controlling the movement of a car
 * robot with an Arduino. This file contains the implementation of the CarControl class.
 */
// Additional includes for sensor readings
#ifndef CarControl_h
#define CarControl_h
#define RIGHT_SENSOR_PIN A0   // Right sensor
#define MIDDLE_SENSOR_PIN A1  // Middle sensor
#define LEFT_SENSOR_PIN A2    // Left sensor
#include "Arduino.h"
#define RGB_LED_PIN 4
#include <FastLED.h>     //
#include <Ultrasonic.h>  // Include for Ultrasonic sensor
#include <Servo.h>  // Include the Servo library
#include "Arduino.h"

class CarControl {
public:
    // Constructor
    CarControl(int pwma, int pwmb, int ain, int bin, int stby, int modeSwitch);
    int getLeftDistance();
        int getRightDistance();
        int getCenterDistance();
    // Setup and movement functions
    void setup();
    void moveForward(int speed, int duration);
    float getBatteryLevel();

    void moveBackward(int speed, int duration);
    void turnLeft(int speed, int duration);
    void turnRight(int speed, int duration);
    void stopMotors();
    void stopTime(int mS);
    void turnAround();
    void attachClaw(int pin);  // Function to attach the servo
    void openClaw();           // Function to open the claw
    void closeClaw();
    void moveSlowForward(int duration, int speed);  // Corrected line
    void customMovement(bool forwardA, bool forwardB, int speedA, int speedB, int duration);
    void lookLeft();              // Function to make the ultrasonic sensor look left
    void lookRight();
    void centerServo();
    void attachSensorServo(int pin);  // New method to attach the sensor servo
    void followLine(int threshold);
    void stopAtLine(int threshold);
    void followLineAvoidObstacle(int threshold, int obstacleDistanceThreshold);
    void intersectionDecision(int threshold, bool detectIntersection());
    void followLineUntilCondition(int threshold, unsigned long duration);
    void initLineSensors(); // Initialize line following sensors
    void followLineMultiSensor(int threshold); // Line following for multiple sensors
    int getLineSensorLeft();
    int getLineSensorMiddle();
    int getLineSensorRight();
    void playStarWars();
 void singleBeep();                 // Single beep pattern
      void doubleBeep();     
    void attachBuzzer(int buzzerPin);  // Attach the buzzer to a pin
    void beep(int pattern);            // Function to control beep patterns
    // New functionalities
    void checkObstacleInFront(); // Checks if there's an obstacle in front
    int getDistanceToObstacle(); // Measures the distance to an obstacle
    int getValueOfInfraredSensor(); // Reads the value of the infrared sensor
  //  void checkIfCarWasPickedUp(); // Checks if the car was picked up
    void lightRGBForDuration(CRGB color, int duration);


private:
    // Motor control variables
    int _pwma, _pwmb, _ain, _bin, _stby, _modeSwitch;
    Servo _sensorServo;  // New servo object for the sensor
    // New private member variables
    bool _obstacleInFront; // Flag for obstacle detection
    //bool _carWasPickedUp; // Flag for detecting if car was picked up
    int _buzzerPin;                    // Pin where the buzzer is attached
                 // Double beep pattern
    // Sensor pins (if required, can be adjusted)
    static const int _trigPin = 13;    // Ultrasonic sensor trigger pin
    static const int _echoPin = 12;   // Ultrasonic sensor echo pin
    static const int _irSensorPin = A0; // IR sensor pin
    int _leftSensorPin, _middleSensorPin, _rightSensorPin; // Pins for the line sensors
    int _redValue, _greenValue, _blueValue;  // Variables to store RGB values
    static const int _batteryPin = A3; // Battery voltage pin
    const float _batteryMaxVoltage = 8.4; // Adjust based on your battery
    const float _batteryMinVoltage = 6.0; // Adjust based on your battery
    // Ultrasonic sensor instance
    Ultrasonic _ultrasonic = Ultrasonic(_trigPin, _echoPin);
    Servo _clawServo;  // Servo object for the claw
    int _clawServoPin; // Pin number for the claw servo
};

#endif /* CarControl_h */
