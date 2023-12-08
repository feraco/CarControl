#ifndef CarControl_h
#define CarControl_h

#include "Arduino.h"
#include <Ultrasonic.h>  // Include for Ultrasonic sensor

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
    void moveSlowForward(int duration, int speed);  // Corrected line
    void customMovement(bool forwardA, bool forwardB, int speedA, int speedB, int duration);

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
    static const int _trigPin = 9;    // Ultrasonic sensor trigger pin
    static const int _echoPin = 10;   // Ultrasonic sensor echo pin
    static const int _irSensorPin = A0; // IR sensor pin

    // Ultrasonic sensor instance
    Ultrasonic _ultrasonic = Ultrasonic(_trigPin, _echoPin);
};

#endif /* CarControl_h */
