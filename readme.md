# CarControl Library for Arduino

The CarControl library is a custom library designed for controlling a car using an Arduino. It encapsulates the common car movements like moving forward, moving backward, turning left, and turning right into simple function calls.

## Installation

To install this library, download the zip file and unzip it into your Arduino libraries folder. 

1. Download the library as a ZIP file.
2. Open the Arduino IDE.
3. Go to Sketch > Include Library > Add .ZIP Library...
4. Select the downloaded ZIP file.
5. The library will now be available for use in your sketches.

## Usage

First, you must include the library in your sketch.

```cpp
#include "CarControl.h"
Next, create a CarControl object with the following parameters:

PWMA: Controls power to right motor
PWMB: Controls power to left motor
AIN: Controls direction of right motor, HIGH = FORWARD, LOW = REVERSE
BIN: Controls direction of left motor, HIGH = FORWARD, LOW = REVERSE
STBY: Places H-Bridge in standby if LOW, runs if HIGH
modeSwitch: Mode Switch input

CarControl car(PWMA, PWMB, AIN, BIN, STBY, modeSwitch);
Before using the car's movements, you must call the setup function in the setup function of your sketch.


void setup() {
  car.setup();
}
You can then use the following functions to control the car's movements:

car.moveForward(duration): Move the car forward for a specified duration in milliseconds.
car.moveBackward(duration): Move the car backward for a specified duration in milliseconds.
car.turnLeft(duration): Turn the car left for a specified duration in milliseconds.
car.turnRight(duration): Turn the car right for a specified duration in milliseconds.
car.stopMotors(): Stop the car's motors.
car.stopTime(mS): Place the car in standby for a specified duration in milliseconds.
car.turnAround(): Turn the car around 180 degrees.
car.moveSlowForward(duration): Move the car forward at a reduced speed for a specified duration in milliseconds.
car.customMovement(ainState, binState, pwmaPower, pwmbPower, duration): Create a custom movement pattern with specified states and power levels.
Examples

The examples folder contains several example sketches demonstrating how to use the CarControl library:

BasicMovements.ino: Demonstrates the basic movements of the car.
LoopMovements.ino: Demonstrates how to use a for loop to repeat movements.
ButtonControl.ino: Demonstrates how to control the car using a button.
UltrasonicSensor.ino: Demonstrates how to control the car using an ultrasonic sensor.
WhileLoop.ino: Demonstrates how to use a while loop to repeat movements until a condition is met.
Credits

Created by Frederick Feraco, NYS Master Teacher in Coding Robotics.