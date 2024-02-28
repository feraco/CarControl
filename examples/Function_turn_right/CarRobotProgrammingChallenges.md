
# Car Robot Programming Challenges

## Challenge 1: Turn Left 90 Degrees Slowly
**Objective:** Write a function to turn the car left 90 degrees at a slow speed.

**Instructions:**
1. Define a function called `turnLeft90DegreesSlow`.
2. Inside the function, use the `turnLeft(int speed, int duration)` function to turn the car. Choose a low speed to ensure the turn is slow.
3. Experiment with the duration to achieve exactly 90 degrees. This might require some trial and error.

```cpp
void turnLeft90DegreesSlow() {
  int speed = 50; // Slow speed
  int duration = 1000; // Duration in milliseconds, adjust as needed
  car.turnLeft(speed, duration);
  delay(duration); // Wait to complete the turn
  car.stopMotors(); // Always stop the motors at the end
}
```

## Challenge 2: Turn Right 90 Degrees Slowly
**Objective:** Write a function to turn the car right 90 degrees at a slow speed.

**Instructions:**
1. Follow the same steps as Challenge 1, but use the `turnRight` function.

```cpp
void turnRight90DegreesSlow() {
  int speed = 50; // Slow speed
  int duration = 1000; // Adjust as needed
  car.turnRight(speed, duration);
  delay(duration);
  car.stopMotors();
}
```

## Challenge 3: Turn 180 Degrees Fast
**Objective:** Write a function to make the car turn 180 degrees quickly.

**Instructions:**
1. Define a function called `turn180DegreesFast`.
2. Use either `turnLeft` or `turnRight` with a higher speed.
3. Adjust the duration to achieve a 180-degree turn.

```cpp
void turn180DegreesFast() {
  int speed = 150; // Fast speed
  int duration = 1000; // Adjust as needed for a 180-degree turn
  car.turnRight(speed, duration);
  delay(duration);
  car.stopMotors();
}
```

## Understanding `if`, `else if`, and `while` Loops

### `if` Statement:
Used to perform a block of code if a condition is true.
```cpp
int speed = car.getSpeed();
if (speed > 100) {
  // If speed is greater than 100, do something (like slowing down the car).
  car.setSpeed(100);
}
```

### `else if` and `else` Statements:
Used following an `if` statement to check another condition if the first `if` is false. `else` runs if all previous conditions are false.
```cpp
if (speed > 100) {
  // Slow down the car
} else if (speed < 50) {
  // Speed up the car
} else {
  // Maintain current speed
}
```

### `while` Loop:
Executes a block of code as long as a condition is true. Great for continuous checks.
```cpp
while (car.getDistanceToObstacle() < 20) {
  // If the distance to an obstacle is less than 20 cm, keep turning the car
  car.turnRight(50, 500); // Adjust values as needed
}
```

These programming constructs are incredibly useful for controlling the flow of your code, making decisions, and repeating actions based on conditions. Experiment with these challenges and constructs to become more comfortable with programming your car!
