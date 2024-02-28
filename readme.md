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
![](Movecommands.gif)

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
### Additional Functions for CarControl Library Documentation:

9. **Follow Line**
   - **Signature**: `car.followLine(threshold);`
   - **Description**: Adjusts the car's movement to follow a line based on sensor readings.
   - **Parameters**:
     - `threshold`: Value against which sensor readings are compared to detect the line.
   - **Example**: `car.followLine(1000);` adjusts the car's movement to follow a line, assuming sensor values above 1000 indicate the line's presence.

10. **Stop At Line**
    - **Signature**: `car.stopAtLine(threshold);`
    - **Description**: Stops the car when a line is detected by any sensor.
    - **Parameters**:
      - `threshold`: Value against which sensor readings are compared to detect the line.
    - **Example**: `car.stopAtLine(1000);` stops the car when any sensor detects a line with a value below 1000.

#### Implementing Line Following and Stopping

The `followLine` and `stopAtLine` functions are essential for tasks like line following and stopping at specific points. Here's a detailed description of each function's behavior:

**Follow Line**

This function makes the car continuously adjust its direction to stay on a line. The car moves forward if all sensors detect the line. If a sensor detects the line is veering off to one side (indicated by a value lower than the threshold), the car will adjust its direction by turning slightly towards the opposite side. This function is particularly useful in situations where the line may curve or not be perfectly straight.

**Stop At Line**

`stopAtLine` is used for scenarios where the car needs to halt upon encountering a line, such as at an intersection or a designated stopping point. The function checks if any of the line sensors detect a value below the specified threshold, which indicates the presence of a line. Upon detection, the car's motors are stopped, bringing the car to a halt.

Both functions rely on accurate sensor readings and may require calibration of the threshold value based on the specific characteristics of the line and the sensors.

### Custom Movement
- **Signature**: `car.customMovement(forwardA, forwardB, speedA, speedB, duration)`
- **Description**: Executes a custom movement pattern.
- **Parameters**:
  - `forwardA`: Boolean flag to set motor A's direction (forward if `true`, backward if `false`).
  - `forwardB`: Boolean flag to set motor B's direction.
  - `speedA`: Speed setting for motor A (0-255).
  - `speedB`: Speed setting for motor B (0-255).
  - `duration`: Time for which the movement should last in milliseconds.
- **Example**: `car.customMovement(true, false, 200, 150, 2500);` will make motor A move forward and motor B move backward, creating a custom motion for the car.

## Understanding Motor Actions for Movement
#### Ultrasonic Sensor Commands

1. **Check for Obstacle**
   - `car.checkObstacleInFront();`
   - **Description**: Checks if there is an obstacle in front of the car.
   - **Example**: `car.checkObstacleInFront();` updates the `_obstacleInFront` variable based on whether an obstacle is detected.

2. **Get Distance to Obstacle**
   - `car.getDistanceToObstacle();`
   - **Description**: Returns the distance to the nearest obstacle in centimeters.
   - **Example**: `int distance = car.getDistanceToObstacle();` gets the distance to the nearest obstacle.
![](ultrasonic.gif)

#### Claw Mechanism Commands

1. **Attach Claw**
   - `car.attachClaw(pin);`
   - **Description**: Attaches the claw mechanism to the specified pin.
   - **Parameters**:
     - `pin`: The pin where the servo for the claw is connected.
   - **Example**: `car.attachClaw(9);` attaches the claw servo to pin 9.

2. **Open Claw**
   - `car.openClaw();`
   - **Description**: Opens the claw.
   - **Example**: `car.openClaw();` opens the claw.

3. **Close Claw**
   - `car.closeClaw();`
   - **Description**: Closes the claw.
   - **Example**: `car.closeClaw();` closes the claw.
### Get Battery Level

1. ## car.getBatteryLevel();
   - ** Description: Retrieves the current battery level as a percentage.
**Returns: Battery level percentage (0-100%).
**Example: float batteryLevel = car.getBatteryLevel(); gets the current battery level percentage.
Get Battery Voltage

## car.getBatteryVoltage();
** Description: Measures the current battery voltage.
Returns: Battery voltage in volts.
Example: float voltage = car.getBatteryVoltage(); measures and returns the current battery voltage.

