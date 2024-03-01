
## Challenge 5: Room Perimeter Exploration
**Objective:** Write a function that allows the car to explore the perimeter of a room, using the distance sensors to navigate and avoid obstacles.

**Instructions:**
1. Define a function called `exploreRoomPerimeter`.
2. The car should start by moving forward.
3. Continuously check the distance to obstacles. If an obstacle is detected (e.g., the distance is less than 20 cm), the car should stop, turn a certain degree (e.g., 90 degrees) to the right, and continue moving forward.
4. Implement logic so that the car makes adjustments to follow along the walls of the room, maintaining a consistent distance (e.g., between 20 cm and 40 cm from the wall).
5. The car should make a complete loop around the perimeter of the room and stop at its starting position.

Here's a simplified pseudocode structure for the function:

```cpp
void exploreRoomPerimeter() {
  while (not back at starting position) {
    if (distance to obstacle is less than 20 cm) {
      stop the car;
      turn right 90 degrees;
    } else if (distance to obstacle is between 20 cm and 40 cm) {
      adjust the car's path to gently turn away from the wall;
    } else {
      move forward;
    }
  }
  stop the car;
}
```

This challenge integrates multiple concepts you've learned, including distance sensing, conditional logic, and controlling motor movements. It's a great way to practice writing more complex programs that require the car to interact intelligently with its environment.
