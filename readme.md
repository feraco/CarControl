## Controlling the ELEGOO Arduino Smart Car

The Car Control Library provides you with a suite of functions to control the car's movements with ease.

### Functions:

1. **Move Forward**
   - `car.moveForward(speed, duration);`
   - **Description**: Moves the car forward.
   - **Parameters**:
     - `speed`: Speed of the car.
     - `duration`: Duration in milliseconds.
   - **Example**: `car.moveForward(255, 2000);` moves the car forward at maximum speed for 2 seconds.

2. **Move Backward**
   - `car.moveBackward(speed, duration);`
   - **Description**: Moves the car backward.
   - **Parameters**:
     - `speed`: Speed of the car.
     - `duration`: Duration in milliseconds.
   - **Example**: `car.moveBackward(200, 1500);` moves the car backward at speed 200 for 1.5 seconds.

3. **Turn Left**
   - `car.turnLeft(speed, duration);`
   - **Description**: Turns the car left.
   - **Parameters**:
     - `speed`: Speed of the turn.
     - `duration`: Duration in milliseconds.
   - **Example**: `car.turnLeft(180, 1000);` turns the car left at speed 180 for 1 second.

4. **Turn Right**
   - `car.turnRight(speed, duration);`
   - **Description**: Turns the car right.
   - **Parameters**:
     - `speed`: Speed of the turn.
     - `duration`: Duration in milliseconds.
   - **Example**: `car.turnRight(150, 500);` turns the car right at speed 150 for half a second.

5. **Stop Motors**
   - `car.stopMotors();`
   - **Description**: Stops all of the car's motors.
   - **Example**: `car.stopMotors();` stops the car.

6. **Stop Time**
   - `car.stopTime(mS);`
   - **Description**: Places the car in standby for a specified duration.
   - **Parameters**:
     - `mS`: Standby time in milliseconds.
   - **Example**: `car.stopTime(1000);` puts the car in standby for 1 second.

7. **Turn Around**
   - `car.turnAround(speed);`
   - **Description**: Turns the car around 180 degrees.
   - **Parameters**:
     - `speed`: Speed of the turn.
   - **Example**: `car.turnAround(200);` turns the car 180 degrees at speed 200.

8. **Move Slow Forward**
   - `car.moveSlowForward(duration);`
   - **Description**: Moves the car forward at a slow speed.
   - **Parameters**:
     - `duration`: Duration in milliseconds.
   - **Example**: `car.moveSlowForward(3000);` moves the car forward slowly for 3 seconds.

9. **Follow Line**
   - `car.followLine(threshold);`
   - **Description**: Adjusts the car's movement to follow a line based on sensor readings.
   - **Parameters**:
     - `threshold`: Value against which sensor readings are compared to detect the line.
   - **Example**: `car.followLine(1000);` adjusts the car's movement to follow a line, assuming sensor values above 1000 indicate the line's presence.

10. **Stop At Line**
    - `car.stopAtLine(threshold);`
    - **Description**: Stops the car when a line is detected by any sensor.
    - **Parameters**:
      - `threshold`: Value against which sensor readings are compared to detect the line.
    - **Example**: `car.stopAtLine(1000);` stops the car when any sensor detects a line with a value below 1000.

11. **Custom Movement**
    - `car.customMovement(forwardA, forwardB, speedA, speedB, duration);`
    - **Description**: Executes a custom movement pattern.
    - **Parameters**:
      - `forwardA`: Boolean flag to set motor A's direction (forward if `true`, backward if `false`).
      - `forwardB`: Boolean flag to set motor B's direction.
      - `speedA`: Speed setting for motor A (0-255).
      - `speedB`: Speed setting for motor B (0-255).
      - `duration`: Time for which the movement should last in milliseconds.
    - **Example**: `car.customMovement(true, false, 200, 150, 2500);` will make motor A move forward and motor B move backward, creating a custom motion for the car.
    - **Example**: `car.stopAtLine(1000);` stops the car when any sensor detects a line with a value below 1000.


### Ultrasonic Sensor Commands

12. **Check for Obstacle**
    - `car.checkObstacleInFront();`
    - **Description**: Checks if there is an obstacle in front of the car.
    - **Example**: `car.checkObstacleInFront();` updates the `_obstacleInFront` variable based on whether an obstacle is detected.

13. **Get Distance to Obstacle**
    - `car.getDistanceToObstacle();`
    - **Description**: Returns the distance to the nearest obstacle in centimeters.
    - **Example**: `int distance = car.getDistanceToObstacle();` gets the distance to the nearest obstacle.

### Claw Mechanism Commands

14. **Attach Claw**
    - `car.attachClaw(pin);`
    - **Description**: Attaches the claw mechanism to the specified pin.
    - **Parameters**:
      - `pin`: The pin where the servo for the claw is connected.
    - **Example**: `car.attachClaw(9);` attaches the claw servo to pin 9.

15. **Open Claw**
    - `car.openClaw();`
    - **Description**: Opens the claw.
    - **Example**: `car.openClaw();` opens the claw.

16. **Close Claw**
    - `car.closeClaw();`
    - **Description**: Closes the claw.
    - **Example**: `car.closeClaw();` closes the claw.

### Get Battery Level

17. **Get Battery Level**
    - `car.getBatteryLevel();`
    - **Description**: Retrieves the current battery level as a percentage.
    - **Returns**: Battery level percentage (0-100%).
    - **Example**: `float batteryLevel = car.getBatteryLevel();` gets the current battery level percentage.

### Get Battery Voltage

18. **Get Battery Voltage**
    - `car.getBatteryVoltage();`
    - **Description**: Measures the current battery voltage.
    - **Returns**: Battery voltage in volts.
    - **Example**: `float voltage = car.getBatteryVoltage();` measures and returns the current battery voltage.
19. **playStarWars()**
    - **Description**: Plays the Star Wars theme tune using a buzzer attached to the car.
    - **Example Usage**: `car.playStarWars();`

20. **attachBuzzer(int pin)**
    - **Description**: Attaches a buzzer to a specified pin for audio output.
    - **Parameters**: `pin` - The pin number where the buzzer is connected.
    - **Example Usage**: `car.attachBuzzer(10);`

21. **beep(int count), singleBeep(), doubleBeep()**
    - **Description**: Controls buzzer patterns to emit single, double, or a specified number of beeps.
    - **Example Usage**:
        - `car.beep(1);` // Emits a single beep.
        - `car.singleBeep();` // Emits a single beep.
        - `car.doubleBeep();` // Emits two beeps in quick succession.

22. **attachSensorServo(int pin)**
    - **Description**: Attaches a servo motor to a pin for moving sensors, like ultrasonic or infrared, to scan the environment.
    - **Parameters**: `pin` - The pin number where the servo motor is connected.
    - **Example Usage**: `car.attachSensorServo(9);`

23. **lookLeft(), lookRight(), centerServo()**
    - **Description**: Controls the servo's position to turn sensors left, right, or bring them to the center.
    - **Example Usage**: `car.lookLeft();` // Turns the sensor left.

24. **lightRGBForDuration(CRGB color, int duration)**
    - **Description**: Lights an RGB LED with a specified color for a set duration.
    - **Parameters**:
        - `color`: The color to set the LED.
        - `duration`: How long the LED should be lit (in milliseconds).
    - **Example Usage**: `car.lightRGBForDuration(CRGB::Red, 1000);` // Lights up red for 1 second.

25. **getLineSensorLeft(), getLineSensorMiddle(), getLineSensorRight()**
    - **Description**: Retrieves line sensor readings from the left, middle, or right sensor.
    - **Example Usage**: `int leftValue = car.getLineSensorLeft();` // Gets left sensor reading.

26. **getLeftDistance(), getRightDistance(), getCenterDistance()**
    - **Description**: Gets distance readings from the left, right, or center distance sensors.
    - **Example Usage**: `int distance = car.getLeftDistance();` // Gets distance from the left sensor.

27. **followLineMultiSensor(int threshold)**
    - **Description**: Enhanced line following functionality using multiple sensors.
    - **Parameters**: `threshold` - The sensor value threshold for detecting the line.
    - **Example Usage**: `car.followLineMultiSensor(500);`

28. **followLineUntilCondition(int threshold, unsigned long duration)**
    - **Description**: Follows a line for a specified duration or until a condition is met.
    - **Parameters**:
        - `threshold`: The sensor value threshold for detecting the line.
        - `duration`: How long to follow the line (in milliseconds).
    - **Example Usage**: `car.followLineUntilCondition(500, 10000);` // Follows for 10 seconds.

29. **intersectionDecision(int threshold, bool (*decisionFunction)())**
    - **Description**: Makes decisions at intersections during line following based on a user-defined function.
    - **Parameters**:
        - `threshold`: The sensor value threshold for detecting the line.
        - `decisionFunction`: A pointer to a function that determines the action at intersections.
    - **Example Usage**: `car.intersectionDecision(500, detectIntersection);` // Uses a custom function to decide at intersections.

30. **initLineSensors()**
    - **Description**: Initializes the pins for the line sensors.
    - **Example Usage**: `car.initLineSensors();`

31. **customMovement(bool forward, bool backward, int speedLeft, int speedRight, int duration)**
    - **Description**: Allows for custom movement patterns by specifying directions and speeds for each motor.
    - **Parameters**:
        - `forward`: Set to true to move forward.
        - `backward`: Set to true to move backward.
        - `speedLeft`: Speed for the left motor.
        - `speedRight`: Speed for the right motor.
    - **Example Usage**: `car.customMovement(true, false, 200, 150, 2500);`
