#include "CarControl.h"

// Create CarControl object with pin numbers for PWMA, PWMB, AIN, BIN, STBY, and modeSwitch
CarControl car(5, 6, 7, 8, 3, 2);

const int trigPin = 9;  // Define pin number for the trigger pin of ultrasonic sensor
const int echoPin = 10; // Define pin number for the echo pin of ultrasonic sensor

long duration;
int distance;

void setup() {
  car.setup();                 // Call setup function to initialize the car
  pinMode(trigPin, OUTPUT);    // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);     // Sets the echoPin as an INPUT
}

void loop() {
  // While loop example
  while (true) {
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    // Calculating the distance
    distance = duration * 0.034 / 2;

    // Check if the distance is greater than 15 cm
    if (distance > 15) {
      car.moveForward(200);  // Move forward for 200 milliseconds
    } else {
      car.stopMotors();  // Stop the motors
      break;  // Break out of the while loop
    }
  }
}
