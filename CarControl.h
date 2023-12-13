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

#include "Arduino.h"
#include <Ultrasonic.h>  // Include for Ultrasonic sensor
#include <Servo.h>  // Include the Servo library

class CarControl {
public:
    // Constructor
    CarControl(int pwma, int pwmb, int ain, int bin, int stby, int modeSwitch);

    // Setup and movement functions
    void setup();
    void moveForward(int speed, int duration);
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
    void centerServo():
    // New functionalities
    void checkObstacleInFront(); // Checks if there's an obstacle in front
    int getDistanceToObstacle(); // Measures the distance to an obstacle
    int getValueOfInfraredSensor(); // Reads the value of the infrared sensor
  //  void checkIfCarWasPickedUp(); // Checks if the car was picked up

private:
    // Motor control variables
    int _pwma, _pwmb, _ain, _bin, _stby, _modeSwitch;

    // New private member variables
    bool _obstacleInFront; // Flag for obstacle detection
    //bool _carWasPickedUp; // Flag for detecting if car was picked up

    // Sensor pins (if required, can be adjusted)
    static const int _trigPin = 13;    // Ultrasonic sensor trigger pin
    static const int _echoPin = 12;   // Ultrasonic sensor echo pin
    static const int _irSensorPin = A0; // IR sensor pin

    // Ultrasonic sensor instance
    Ultrasonic _ultrasonic = Ultrasonic(_trigPin, _echoPin);
    Servo _clawServo;  // Servo object for the claw
    int _clawServoPin; // Pin number for the claw servo
};

#endif /* CarControl_h */
