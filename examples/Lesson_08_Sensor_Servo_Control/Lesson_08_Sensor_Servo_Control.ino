/*
 * LESSON 08: Looking Around - Sensor Servo Control
 * 
 * LESSON OBJECTIVES:
 * - Control the sensor servo to look in different directions
 * - Scan the environment for obstacles
 * - Get distance measurements from multiple angles
 * - Make decisions based on sensor scanning
 * 
 * NEW COMMANDS:
 * - attachSensorServo(pin) - Connect the sensor servo (call in setup)
 *   - pin: The Arduino pin connected to the servo (usually 10)
 * 
 * - lookLeft() - Turn sensor to look left (0 degrees)
 * 
 * - lookRight() - Turn sensor to look right (180 degrees)
 * 
 * - centerServo() - Point sensor straight ahead (90 degrees)
 * 
 * - getLeftDistance() - Look left and measure distance
 * - getRightDistance() - Look right and measure distance  
 * - getCenterDistance() - Look center and measure distance
 * 
 * HOW IT WORKS:
 * A servo motor can rotate to specific angles (0° to 180°).
 * Your ultrasonic sensor is mounted on a servo, so it can look:
 * 
 * - Left (0°): Sensor points to the robot's left side
 * - Center (90°): Sensor points straight ahead
 * - Right (180°): Sensor points to the robot's right side
 * 
 * By looking in different directions, your robot can "see" what's
 * around it, just like you turn your head to look around!
 * 
 * This is called SCANNING - looking in multiple directions to
 * build a picture of the environment.
 */

#include <CarControl.h>

CarControl car(5, 6, 7, 8, 3, 2);

void setup() {
  Serial.begin(9600);
  Serial.println("Lesson 08: Sensor Servo Control");
  Serial.println("-------------------------------");
  
  car.setup();
  car.attachSensorServo(10);  // Connect sensor servo to pin 10
  
  Serial.println("\nThe sensor will look around!");
  Serial.println("Watch the servo move...\n");
}

void loop() {
  // Example 1: Basic servo movements
  Serial.println("Example 1: Looking in all directions");
  
  Serial.println("Looking LEFT");
  car.lookLeft();
  delay(1000);  // Wait for servo to move and stabilize
  
  Serial.println("Looking CENTER");
  car.centerServo();
  delay(1000);
  
  Serial.println("Looking RIGHT");
  car.lookRight();
  delay(1000);
  
  Serial.println("Looking CENTER again");
  car.centerServo();
  delay(2000);
  
  // Example 2: Scanning and measuring
  Serial.println("\nExample 2: Scan and measure distances");
  
  car.lookLeft();
  delay(500);
  int leftDist = car.getDistanceToObstacle();
  Serial.print("Left distance: ");
  Serial.print(leftDist);
  Serial.println(" cm");
  
  car.centerServo();
  delay(500);
  int centerDist = car.getDistanceToObstacle();
  Serial.print("Center distance: ");
  Serial.print(centerDist);
  Serial.println(" cm");
  
  car.lookRight();
  delay(500);
  int rightDist = car.getDistanceToObstacle();
  Serial.print("Right distance: ");
  Serial.print(rightDist);
  Serial.println(" cm");
  
  car.centerServo();
  delay(2000);
  
  // Example 3: Finding the clearest path
  Serial.println("\nExample 3: Finding the clearest path");
  
  leftDist = car.getLeftDistance();
  centerDist = car.getCenterDistance();
  rightDist = car.getRightDistance();
  
  Serial.print("Left: ");
  Serial.print(leftDist);
  Serial.print(" cm, Center: ");
  Serial.print(centerDist);
  Serial.print(" cm, Right: ");
  Serial.print(rightDist);
  Serial.println(" cm");
  
  // Find which direction has most space
  if(leftDist > centerDist && leftDist > rightDist) {
    Serial.println("Clearest path: LEFT");
  } else if(rightDist > centerDist && rightDist > leftDist) {
    Serial.println("Clearest path: RIGHT");
  } else {
    Serial.println("Clearest path: CENTER");
  }
  delay(2000);
  
  // Example 4: Scanning sweep
  Serial.println("\nExample 4: Smooth scanning sweep");
  
  Serial.println("Sweeping from left to center to right...");
  car.lookLeft();
  delay(800);
  car.centerServo();
  delay(800);
  car.lookRight();
  delay(800);
  
  Serial.println("Sweeping back from right to center to left...");
  car.centerServo();
  delay(800);
  car.lookLeft();
  delay(800);
  car.centerServo();
  delay(2000);
  
  // Example 5: Making a decision based on scan
  Serial.println("\nExample 5: Decide which way to turn");
  
  leftDist = car.getLeftDistance();
  rightDist = car.getRightDistance();
  
  Serial.print("Comparing: Left=");
  Serial.print(leftDist);
  Serial.print("cm, Right=");
  Serial.print(rightDist);
  Serial.println("cm");
  
  if(leftDist > rightDist) {
    Serial.println("More space on left - turning left");
    car.turnLeft(150, 500);
  } else {
    Serial.println("More space on right - turning right");
    car.turnRight(150, 500);
  }
  
  delay(1000);
  car.centerServo();  // Always recenter when done
  
  Serial.println("\nSequence complete! Waiting 5 seconds...\n");
  delay(5000);
}

/*
 * CHALLENGE: The Path Finder
 * 
 * Create a program that helps your robot find the best path forward:
 * 
 * 1. Scan left, center, and right
 * 2. Print all three distances
 * 3. Determine which direction has the most space
 * 4. If center is clearest, move forward
 * 5. If left is clearest, turn left then move forward
 * 6. If right is clearest, turn right then move forward
 * 7. After moving, scan again
 * 8. Repeat this process 5 times
 * 
 * Requirements:
 * - Print which direction you chose and why
 * - Always recenter the servo after scanning
 * - Move forward for 1 second after each decision
 * - Add appropriate delays for servo movement
 * 
 * BONUS CHALLENGES:
 * 1. Only move if the clearest path has at least 30cm of space
 *    Otherwise, turn around and try again
 * 2. Create a "danger meter":
 *    - If any distance < 15cm, print "DANGER!"
 *    - If any distance < 30cm, print "Caution"
 *    - If all > 50cm, print "All clear!"
 * 3. Make the servo sweep smoothly multiple times and find
 *    the angle with the maximum distance
 * 
 * ADVANCED CHALLENGE:
 * Create an obstacle avoider that:
 * - Moves forward while center distance > 30cm
 * - When obstacle detected, scan left and right
 * - Turn toward the clearer side
 * - Continue moving
 * - Run for 30 seconds
 * 
 * EXPERT CHALLENGE:
 * Create a function that finds the exact best angle:
 * 
 * int findBestAngle() {
 *   // Scan in 5-degree increments from 0 to 180
 *   // Return the angle with the maximum distance
 * }
 * 
 * Hint: You'll need to use the servo write command directly
 * and loop through angles!
 */
