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

9. **Custom Movement**
car.customMovement(forwardA, forwardB, speedA, speedB, duration);
Description: Executes a custom movement pattern.
Parameters:
forwardA: Boolean flag to set motor A's direction.
forwardB: Boolean flag to set motor B's direction.
speedA: Speed setting for motor A (0-255).
speedB: Speed setting for motor B (0-255).
duration: Time for which the movement should last in milliseconds.
Example: car.customMovement(true, false, 200, 150, 2500); will make motor A move forward and motor B move backward, creating a custom motion for the car.
### Examples:

- `BasicMovements.ino`: Demonstrates the basic movements of the car.
- `LoopMovements.ino`: Demonstrates looped sequences of actions.
