/*
 * LESSON 11: Simple Obstacle Course
 * 
 * LESSON OBJECTIVES:
 * - Navigate through a structured obstacle course
 * - Combine all movement and sensor skills
 * - Implement reliable navigation algorithms
 * - Handle multiple obstacles strategically
 * 
 * HOW IT WORKS:
 * This lesson puts everything together! You'll create a robot that can:
 * - Navigate through a course with multiple obstacles
 * - Make smart decisions at each obstacle
 * - Complete the course without human intervention
 * 
 * Strategy for obstacle courses:
 * 1. Move forward while path is clear
 * 2. When obstacle detected, STOP
 * 3. Scan left and right
 * 4. Choose the clearer path
 * 5. Turn in that direction
 * 6. Continue moving
 * 
 * Success Tips:
 * - Test in stages - get one behavior working before adding more
 * - Use Serial messages to debug what robot is "thinking"
 * - Adjust SAFE_DISTANCE based on your course
 * - Fine-tune turn angles for your specific robot
 */

#include <CarControl.h>

CarControl car(5, 6, 7, 8, 3, 2);

// Configuration constants - adjust these for your robot!
const int SAFE_DISTANCE = 30;      // Stop if obstacle within this distance (cm)
const int TURN_DURATION = 500;     // How long to turn (ms) - approx 90 degrees
const int MOVE_SPEED = 160;        // Speed for normal movement
const int SCAN_DELAY = 600;        // Wait time after moving sensor (ms)

void setup() {
  Serial.begin(9600);
  Serial.println("Lesson 11: Simple Obstacle Course");
  Serial.println("---------------------------------");
  
  car.setup();
  car.attachSensorServo(10);
  car.centerServo();
  
  Serial.println("\nOBSTACLE COURSE READY!");
  Serial.println("Starting in 3 seconds...\n");
  delay(3000);
}

void loop() {
  Serial.println("=== OBSTACLE COURSE RUN ===");
  Serial.println("Course duration: 20 seconds\n");
  
  unsigned long startTime = millis();
  int obstaclesAvoided = 0;
  
  // Main navigation loop - runs for 20 seconds
  while(millis() - startTime < 20000) {
    
    // Check distance ahead
    int centerDist = car.getCenterDistance();
    Serial.print("Center: ");
    Serial.print(centerDist);
    Serial.print(" cm");
    
    if(centerDist < SAFE_DISTANCE) {
      // OBSTACLE DETECTED!
      Serial.println(" - OBSTACLE!");
      obstaclesAvoided++;
      car.stopMotors();
      delay(300);
      
      // Scan left and right
      Serial.println("Scanning...");
      int leftDist = car.getLeftDistance();
      Serial.print("  Left: ");
      Serial.print(leftDist);
      Serial.println(" cm");
      
      int rightDist = car.getRightDistance();
      Serial.print("  Right: ");
      Serial.print(rightDist);
      Serial.println(" cm");
      
      car.centerServo();  // Recenter sensor
      delay(300);
      
      // Decide which way to turn
      if(leftDist > rightDist && leftDist > SAFE_DISTANCE) {
        Serial.println("Decision: Turn LEFT\n");
        car.turnLeft(MOVE_SPEED, TURN_DURATION);
      } else if(rightDist > leftDist && rightDist > SAFE_DISTANCE) {
        Serial.println("Decision: Turn RIGHT\n");
        car.turnRight(MOVE_SPEED, TURN_DURATION);
      } else if(leftDist < SAFE_DISTANCE && rightDist < SAFE_DISTANCE) {
        // Both sides blocked! Back up and turn around
        Serial.println("Decision: BLOCKED - Turn around\n");
        car.moveBackward(MOVE_SPEED, 800);
        delay(300);
        car.turnRight(MOVE_SPEED, 1000);  // 180 degree turn
      } else {
        // If distances are similar, pick one randomly (left in this case)
        Serial.println("Decision: Similar distances - Turn LEFT\n");
        car.turnLeft(MOVE_SPEED, TURN_DURATION);
      }
      
      delay(300);
      
    } else {
      // Path is clear - keep moving
      Serial.println(" - Clear, moving forward");
      car.moveForward(MOVE_SPEED, 300);
      delay(100);
    }
  }
  
  // Course complete!
  car.stopMotors();
  Serial.println("\n=== COURSE COMPLETE! ===");
  Serial.print("Obstacles avoided: ");
  Serial.println(obstaclesAvoided);
  Serial.println("\nWaiting 10 seconds before next run...\n");
  delay(10000);
}

/*
 * CHALLENGE: Complete the Obstacle Course
 * 
 * Course Setup:
 * Create a rectangular area (about 2m x 2m) and place 4-6 obstacles:
 * - Use boxes, books, bottles, or toys
 * - Vary the sizes and positions
 * - Leave enough space to navigate between them
 * - Mark a start point and finish point
 * 
 * Your Mission:
 * Modify the code above to:
 * 1. Successfully navigate from start to finish
 * 2. Avoid all obstacles without touching them
 * 3. Complete the course in under 30 seconds
 * 4. Print clear status messages
 * 
 * Tuning Tips:
 * - Adjust SAFE_DISTANCE if robot stops too far or too close
 * - Adjust TURN_DURATION if turns are too much or too little
 * - Adjust MOVE_SPEED for faster/slower navigation
 * - Add delays if robot seems "jumpy" or unstable
 * 
 * Success Criteria:
 * - Robot reaches finish area
 * - Zero collisions with obstacles
 * - Smooth, confident movement
 * - Good decision making at each obstacle
 * 
 * BONUS CHALLENGES:
 * 1. Add different speeds based on available space:
 *    - Fast (200) when centerDist > 60cm
 *    - Medium (150) when 40-60cm
 *    - Slow (100) when 30-40cm
 * 
 * 2. Implement a "preferred direction":
 *    - If left and right are similar, always choose left (or right)
 *    - This can help robot navigate more consistently
 * 
 * 3. Add a "progress tracker":
 *    - Estimate distance traveled
 *    - Count number of forward movements
 *    - Print progress every 5 seconds
 * 
 * 4. Create a "safety backup":
 *    - If stuck (not moving forward for 3 seconds), execute escape:
 *    - Back up 1 second, turn 180 degrees, try again
 * 
 * ADVANCED CHALLENGE:
 * Add a "course completion detector":
 * - Place a distinctive object at the finish (specific distance pattern)
 * - When robot detects this pattern, stop and celebrate!
 * - Print "FINISH LINE REACHED!"
 * 
 * EXPERT CHALLENGE:
 * Implement a "smart turning" system:
 * - If obstacle is slightly to the right, make a small right turn
 * - If obstacle is far to the right, make a large right turn
 * - Use the difference between left and right distances to decide turn size
 * 
 * Example:
 * int turnAmount = (rightDist - leftDist) * 5;  // Scale the difference
 * if(turnAmount > 0) {
 *   car.turnRight(MOVE_SPEED, turnAmount);
 * } else {
 *   car.turnLeft(MOVE_SPEED, -turnAmount);
 * }
 */
