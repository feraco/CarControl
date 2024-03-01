
## Challenge 4: Responsive Distance-Based Movement
**Objective:** Write a function that makes the car respond differently based on the distance to an obstacle detected by its sensors.

**Instructions:**
1. Define a function called `responsiveDistanceMovement`.
2. Inside the function, use the `getDistanceToObstacle()` function to get the current distance to the nearest obstacle.
3. Based on the distance, the car should behave differently:
   - If the distance is less than 20 cm, the car should stop.
   - If the distance is between 20 cm and 40 cm, the car should move slowly forward.
   - If the distance is greater than 40 cm, the car should move forward at a regular speed.

```cpp
void responsiveDistanceMovement() {
  int distance = car.getDistanceToObstacle(); // Get the current distance

  if (distance < 20) {
    // If the distance is less than 20 cm, stop the car.
    car.stopMotors();
  } else if (distance >= 20 && distance <= 40) {
    // If the distance is between 20 cm and 40 cm, move slowly.
    car.moveForward(50, 2000); // Adjust speed and duration as needed
  } else {
    // If the distance is greater than 40 cm, move forward at a regular speed.
    car.moveForward(100, 2000); // Adjust speed and duration as needed
  }
}
```

This challenge helps practice using `if`, `else if`, and `else` statements to make conditional decisions based on sensor input, a fundamental skill in robotics for intelligent environment interaction.
