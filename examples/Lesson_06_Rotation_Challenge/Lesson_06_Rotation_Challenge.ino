/*
 * LESSON 06: Rotation Challenge - Navigation Mission
 * 
 * LESSON OBJECTIVES:
 * - Apply rotation skills to solve navigation problems
 * - Plan multi-step movement sequences
 * - Navigate to waypoints using turns and forward movement
 * - Develop spatial reasoning and planning skills
 * 
 * COMMANDS REVIEW (Everything you've learned!):
 * - moveForward(speed, duration)
 * - moveBackward(speed, duration)
 * - turnLeft(speed, duration)
 * - turnRight(speed, duration)
 * - turnAround()
 * - stopMotors()
 * - delay(milliseconds)
 * 
 * HOW IT WORKS:
 * Navigation is all about combining movements in the right order.
 * Think of it like giving directions to a friend:
 * "Go straight 2 meters, turn right, go 1 meter, turn left..."
 * 
 * In robotics, we do the same thing, but with precise commands!
 */

#include <CarControl.h>

CarControl car(5, 6, 7, 8, 3, 2);

void setup() {
  Serial.begin(9600);
  Serial.println("Lesson 06: Rotation Challenge");
  Serial.println("-----------------------------");
  
  car.setup();
}

void loop() {
  // Example Mission: The Delivery Route
  Serial.println("MISSION: Delivery Route");
  Serial.println("========================");
  
  // Start at warehouse
  Serial.println("Starting at warehouse...");
  delay(1000);
  
  // Go to delivery point 1
  Serial.println("Route to Delivery Point 1:");
  Serial.println("  - Moving forward");
  car.moveForward(180, 1500);
  delay(500);
  Serial.println("  - Turning right 90°");
  car.turnRight(150, 500);
  delay(500);
  Serial.println("  - Moving forward");
  car.moveForward(180, 1000);
  delay(500);
  
  Serial.println("*** Arrived at Delivery Point 1 ***");
  delay(2000);  // Simulate delivery
  
  // Go to delivery point 2
  Serial.println("Route to Delivery Point 2:");
  Serial.println("  - Turning left 90°");
  car.turnLeft(150, 500);
  delay(500);
  Serial.println("  - Moving forward");
  car.moveForward(180, 1500);
  delay(500);
  Serial.println("  - Turning left 90°");
  car.turnLeft(150, 500);
  delay(500);
  Serial.println("  - Moving forward");
  car.moveForward(180, 1000);
  
  Serial.println("*** Arrived at Delivery Point 2 ***");
  delay(2000);  // Simulate delivery
  
  // Return to warehouse
  Serial.println("Returning to warehouse:");
  Serial.println("  - Turning around");  
  car.turnAround();
  delay(500);
  Serial.println("  - Moving forward");
  car.moveForward(180, 1000);
  delay(500);
  Serial.println("  - Turning right 90°");
  car.turnRight(150, 500);
  delay(500);
  Serial.println("  - Moving forward");
  car.moveForward(180, 1500);
  delay(500);
  Serial.println("  - Turning right 90°");
  car.turnRight(150, 500);
  delay(500);
  Serial.println("  - Moving forward");
  car.moveForward(180, 1000);
  
  Serial.println("\n*** Back at warehouse! ***");
  Serial.println("Mission Complete!\n");
  
  car.stopMotors();
  delay(10000);  // Wait 10 seconds before repeating
}

/*
 * MAIN CHALLENGE: The Waypoint Navigation Course
 * 
 * Set up a course with 4 waypoints arranged like this:
 * 
 *    Start
 *      |
 *      v
 *    [A]--->[B]
 *            |
 *            v
 *    [D]<---[C]
 *      |
 *      v
 *    Finish
 * 
 * Your robot must:
 * 1. Start at the starting position
 * 2. Move forward to waypoint A
 * 3. Turn right and move to waypoint B
 * 4. Turn right and move to waypoint C
 * 5. Turn right and move to waypoint D
 * 6. Turn right and move to finish line
 * 
 * Requirements:
 * - Print which waypoint you're heading to
 * - Pause 2 seconds at each waypoint
 * - Use consistent speeds
 * - Make 90-degree turns
 * - Robot should face the same direction at finish as it started
 * 
 * BONUS CHALLENGES:
 * 1. Make the route in reverse (D -> C -> B -> A)
 * 2. Create a "Figure 8" pattern using two squares
 * 3. Navigate the waypoints using ONLY left turns (no right turns)
 * 4. Add a "pause and beep" at each waypoint (if you have a buzzer)
 * 
 * ADVANCED CHALLENGE: The Maze Navigator
 * 
 * Create a simple maze with walls (books, boxes, tape):
 * - The robot starts at the entrance
 * - It must navigate turns to reach the exit
 * - Use forward movement and 90-degree turns only
 * 
 * Example maze solution:
 * 1. Forward 2 seconds
 * 2. Turn right
 * 3. Forward 1 second
 * 4. Turn left
 * 5. Forward 2 seconds
 * 6. Turn right
 * 7. Forward 1 second - GOAL!
 * 
 * EXPERT CHALLENGE:
 * Create a function that makes your robot navigate a square, but
 * allow the user to specify if it should turn left or right:
 * 
 * void makeSquare(bool turnRight) {
 *   for(int i = 0; i < 4; i++) {
 *     car.moveForward(180, 1000);
 *     delay(300);
 *     if(turnRight) {
 *       car.turnRight(150, 500);
 *     } else {
 *       car.turnLeft(150, 500);
 *     }
 *     delay(300);
 *   }
 * }
 */
