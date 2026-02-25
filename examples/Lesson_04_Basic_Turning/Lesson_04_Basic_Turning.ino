/*
 * LESSON 04: Turning Left and Right
 * 
 * LESSON OBJECTIVES:
 * - Learn to turn the robot left and right
 * - Understand how rotation works
 * - Combine turning with forward movement
 * - Create basic navigation patterns
 * 
 * NEW COMMANDS:
 * - turnLeft(speed, duration) - Makes the robot turn left
 *   - speed: How fast to turn (0-255)
 *   - duration: How long to turn in milliseconds
 * 
 * - turnRight(speed, duration) - Makes the robot turn right
 *   - speed: How fast to turn (0-255)
 *   - duration: How long to turn in milliseconds
 * 
 * HOW IT WORKS:
 * Turning works by making the two motors spin in opposite directions.
 * 
 * For a LEFT turn:
 * - Right motor spins FORWARD
 * - Left motor spins BACKWARD
 * - This makes the robot spin counterclockwise (like turning a steering wheel left)
 * 
 * For a RIGHT turn:
 * - Left motor spins FORWARD
 * - Right motor spins BACKWARD
 * - This makes the robot spin clockwise (like turning a steering wheel right)
 * 
 * The longer the duration, the more the robot turns!
 * Duration ≈ 500ms usually makes about a 90-degree turn (depends on your robot)
 */

#include <CarControl.h>

CarControl car(5, 6, 7, 8, 3, 2);

void setup() {
  Serial.begin(9600);
  Serial.println("Lesson 04: Turning Left and Right");
  Serial.println("---------------------------------");
  
  car.setup();
  
  Serial.println("TIP: Watch the robot to see how long it takes");
  Serial.println("     to turn 90 degrees. You'll need this for");
  Serial.println("     the challenge!\n");
}

void loop() {
  // Example 1: Simple left turn
  Serial.println("Example 1: Turning left");
  car.turnLeft(150, 500);  // Turn left for 0.5 seconds
  delay(2000);
  
  // Example 2: Simple right turn
  Serial.println("Example 2: Turning right");
  car.turnRight(150, 500);  // Turn right for 0.5 seconds
  delay(2000);
  
  // Example 3: Forward then turn (changing direction)
  Serial.println("Example 3: Move and turn");
  car.moveForward(180, 1000);  // Move forward
  delay(500);
  car.turnRight(150, 500);      // Turn right
  delay(500);
  car.moveForward(180, 1000);  // Move forward in new direction
  delay(2000);
  
  // Example 4: Making a square (first corner)
  Serial.println("Example 4: First corner of a square");
  car.moveForward(180, 1000);  // Side 1
  delay(300);
  car.turnRight(150, 500);      // Corner
  delay(300);
  car.moveForward(180, 1000);  // Side 2
  delay(2000);
  
  // Example 5: Spin in place
  Serial.println("Example 5: Spinning!");
  car.turnRight(180, 2000);    // Spin right for 2 seconds
  delay(1000);
  car.turnLeft(180, 2000);     // Spin left for 2 seconds
  delay(2000);
  
  // Example 6: Different turn speeds
  Serial.println("Example 6: Fast vs slow turns");
  Serial.println("  Slow turn...");
  car.turnLeft(80, 800);       // Slow turn
  delay(1000);
  Serial.println("  Fast turn!");
  car.turnLeft(220, 500);      // Fast turn
  delay(2000);
  
  car.stopMotors();
  Serial.println("\nSequence complete! Waiting 5 seconds...\n");
  delay(5000);
}

/*
 * CHALLENGE: Make a Square!
 * 
 * Program your robot to drive in a perfect square pattern.
 * A square has 4 equal sides and 4 right-angle (90°) turns.
 * 
 * Steps:
 * 1. Move forward (this is side 1)
 * 2. Turn right 90 degrees
 * 3. Move forward (side 2)
 * 4. Turn right 90 degrees
 * 5. Move forward (side 3)
 * 6. Turn right 90 degrees
 * 7. Move forward (side 4)
 * 8. Turn right 90 degrees (back to start position)
 * 
 * Tips:
 * - All forward movements should be the same duration
 * - All turns should be the same duration
 * - Experiment to find the right turn duration for 90 degrees
 * - Use Serial.println() to label each side
 * 
 * BONUS CHALLENGES:
 * 1. Make a triangle (3 sides, 120-degree turns)
 * 2. Make a rectangle (2 long sides, 2 short sides)
 * 3. Make your robot drive in a square twice!
 * 4. Add a pause at each corner
 * 
 * ADVANCED CHALLENGE:
 * Create a function called makeSquare() that you can call to
 * make a square. Then call it multiple times to make multiple squares!
 * 
 * Example:
 * void makeSquare() {
 *   // Your square code here
 * }
 */
