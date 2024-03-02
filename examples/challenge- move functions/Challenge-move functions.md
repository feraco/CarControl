
# Detailed Walkthrough for Challenges 1-3

## Challenge 1: Turn Left 90 Degrees Slowly

### Objective:
Program the robot to turn left 90 degrees at a slow pace.

### Steps:
1. **Define the Function:**
   - Create a function named `turnLeft90DegreesSlow` to contain the instructions.

   ```cpp
   void turnLeft90DegreesSlow() {
   }
   ```

2. **Set Motor Speed and Duration:**
   - Use `turnLeft` with a low speed for a slow turn and set the duration to achieve a 90-degree turn.

   ```cpp
   void turnLeft90DegreesSlow() {
     car.turnLeft(50, 1000); // Speed: 50, Duration: 1000 milliseconds
     delay(1000); // Wait for the turn to complete
     car.stopMotors(); // Stop the motors
   }
   ```

## Challenge 2: Turn Right 90 Degrees Slowly

### Objective:
Make the robot turn right 90 degrees at a slow pace.

### Steps:
- Similar to Challenge 1, but use `turnRight` to turn the robot to the right.

## Challenge 3: Turn 180 Degrees Fast

### Objective:
Program the robot to execute a fast 180-degree turn.

### Steps:
1. **Define the Function:**
   - Create `turn180DegreesFast` for this maneuver.

2. **Set Motor Speed and Duration:**
   - Opt for a higher speed and adjust the duration to complete a 180-degree turn quickly.

3. **Stop the Motors:**
   - Ensure the robot ceases movement after the turn.

This walkthrough covers essential programming concepts, including function definition, motor control, and basic robot navigation, providing a practical introduction to robotics.
