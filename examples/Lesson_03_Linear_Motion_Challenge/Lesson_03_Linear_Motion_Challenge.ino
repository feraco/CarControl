/*
 * LESSON 03: Linear Motion Challenge
 * 
 * LESSON OBJECTIVES:
 * - Master forward and backward movement
 * - Learn to plan a sequence of movements
 * - Navigate to specific positions
 * - Understand precision in robot programming
 * 
 * COMMANDS REVIEW:
 * - moveForward(speed, duration)
 * - moveBackward(speed, duration)
 * - stopMotors()
 * - delay(milliseconds) - Wait/pause for a time
 * 
 * HOW IT WORKS:
 * Linear motion means moving in straight lines. By combining
 * forward and backward movements with precise timing, you can
 * make your robot navigate to exact positions.
 * 
 * This is like following dance steps - each movement must be
 * timed correctly to end up in the right place!
 */

#include <CarControl.h>

CarControl car(5, 6, 7, 8, 3, 2);

void setup() {
  Serial.begin(9600);
  Serial.println("Lesson 03: Linear Motion Challenge");
  Serial.println("----------------------------------");
  
  car.setup();
}

void loop() {
  // Example Mission: Navigate forward, pause, return to start
  Serial.println("Mission 1: There and Back");
  Serial.println("Step 1: Moving forward to target");
  car.moveForward(180, 2000);  // Go forward 2 seconds
  
  Serial.println("Step 2: Pausing at target");
  delay(1000);  // Wait at target position
  
  Serial.println("Step 3: Returning to start");
  car.moveBackward(180, 2000);  // Return (same speed and time)
  
  Serial.println("Mission 1 complete!\n");
  delay(3000);
  
  // Example Mission: The Three-Point Navigation
  Serial.println("Mission 2: Three-Point Navigation");
  
  Serial.println("Moving to Point 1");
  car.moveForward(150, 1000);
  delay(1000);
  
  Serial.println("Moving to Point 2");
  car.moveForward(150, 1500);
  delay(1000);
  
  Serial.println("Moving to Point 3");
  car.moveForward(150, 1000);
  delay(1000);
  
  Serial.println("Returning to start");
  car.moveBackward(150, 3500);  // Total time back (1000+1500+1000)
  
  Serial.println("Mission 2 complete!\n");
  delay(3000);
  
  // Example Mission: The Precision Test
  Serial.println("Mission 3: Precision Parking");
  
  // Move forward quickly
  car.moveForward(255, 1500);
  delay(500);
  
  // Back up a little
  car.moveBackward(100, 300);
  delay(500);
  
  // Final position adjustment - very slow and precise
  car.moveForward(80, 200);
  
  Serial.println("Parked! Mission 3 complete!\n");
  car.stopMotors();
  
  delay(5000);
}

/*
 * MAIN CHALLENGE: The Obstacle Course
 * 
 * Set up a simple course with markers (tape, cups, or toys):
 * - Start Line
 * - Checkpoint 1 (30cm forward)
 * - Checkpoint 2 (20cm more forward)
 * - Finish Line (40cm more forward)
 * 
 * Your robot must:
 * 1. Move from Start to Checkpoint 1 (pause 1 second)
 * 2. Move from Checkpoint 1 to Checkpoint 2 (pause 1 second)  
 * 3. Move from Checkpoint 2 to Finish Line (pause 2 seconds)
 * 4. Return to Start Line using backward movement
 * 
 * Requirements:
 * - Use different speeds for each segment
 * - Add Serial.println() messages for each checkpoint
 * - Stop precisely at each checkpoint
 * - Return exactly to start position
 * 
 * BONUS CHALLENGES:
 * 1. Make the robot "park" by approaching the finish line
 *    fast, then slow down for precise positioning
 * 2. Add a "countdown" using delays and Serial messages
 *    before the robot starts (3... 2... 1... GO!)
 * 3. Calculate the total distance traveled and print it
 * 
 * ADVANCED CHALLENGE:
 * Create a delivery mission where the robot:
 * - Starts at a "warehouse"
 * - Moves forward to "delivery point 1" (pause)
 * - Backs up and moves forward to "delivery point 2" (pause)
 * - Returns to warehouse
 */
