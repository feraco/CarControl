/*
 * LESSON 02: Going Backward
 * 
 * LESSON OBJECTIVES:
 * - Learn to move the robot backward
 * - Understand the difference between forward and backward
 * - Combine forward and backward movements
 * 
 * NEW COMMANDS:
 * - moveBackward(speed, duration) - Makes the robot move backward
 *   - speed: How fast to move backward (0-255)
 *   - duration: How long to move in milliseconds
 * 
 * HOW IT WORKS:
 * Moving backward is just like moving forward, except the motors
 * spin in the opposite direction. Think of it like a car in reverse -
 * same controls, just going the other way!
 * 
 * When you tell the motors to go backward, they spin the opposite
 * direction from forward, making the robot move away from where
 * it's pointing.
 */

#include <CarControl.h>

// Create our robot object
CarControl car(5, 6, 7, 8, 3, 2);

void setup() {
  Serial.begin(9600);
  Serial.println("Lesson 02: Backward Movement");
  Serial.println("----------------------------");
  
  car.setup();
}

void loop() {
  // Example 1: Simple backward movement
  Serial.println("Example 1: Moving backward slowly");
  car.moveBackward(120, 1000);  // Move backward slowly for 1 second
  delay(2000);  // Wait 2 seconds
  
  // Example 2: Forward then backward (like bouncing)
  Serial.println("Example 2: Forward and backward");
  car.moveForward(150, 1000);   // Move forward for 1 second
  delay(500);                    // Brief pause
  car.moveBackward(150, 1000);  // Move backward for 1 second
  delay(2000);
  
  // Example 3: The "Dance" - forward, backward, forward
  Serial.println("Example 3: The Dance!");
  car.moveForward(200, 800);    // Forward
  delay(200);                    // Quick pause
  car.moveBackward(200, 800);   // Backward
  delay(200);
  car.moveForward(200, 800);    // Forward again
  delay(2000);
  
  // Example 4: Different speeds backward
  Serial.println("Example 4: Slow to fast backward");
  car.moveBackward(80, 1000);   // Very slow
  delay(500);
  car.moveBackward(160, 1000);  // Medium
  delay(500);
  car.moveBackward(255, 1000);  // Maximum speed
  
  // Always good to stop at the end
  car.stopMotors();
  
  Serial.println("Sequence complete! Waiting 5 seconds...\n");
  delay(5000);
}

/*
 * CHALLENGE: The Robot Dance
 * 
 * Create a "dance" routine using forward and backward movements!
 * Your dance must include:
 * 1. At least 6 movements (mix of forward and backward)
 * 2. Different speeds (use at least 3 different speed values)
 * 3. Different durations (some quick, some slow)
 * 4. Use delay() to create rhythm in your dance
 * 
 * BONUS CHALLENGES:
 * 1. Make your robot spell the letter "H" by moving forward,
 *    backward to start, forward again
 * 2. Create a dance that lasts exactly 10 seconds
 * 3. Add Serial.println() to print the name of each dance move!
 * 
 * Example dance move names:
 * - "The Shuffle"
 * - "The Moonwalk"  
 * - "The Bounce"
 */
