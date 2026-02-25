/*
 * LESSON 10: Obstacle Detection and Avoidance
 * 
 * LESSON OBJECTIVES:
 * - Combine sensor scanning with movement decisions
 * - Create obstacle avoidance behavior
 * - Implement autonomous navigation logic
 * - Use if-else statements for decision making
 * 
 * COMMANDS REVIEW (All the tools you've learned!):
 * - Movement: moveForward(), moveBackward(), turnLeft(), turnRight()
 * - Sensors: getDistanceToObstacle(), getLeftDistance(), getRightDistance(), getCenterDistance()
 * - Servos: attachSensorServo(), lookLeft(), lookRight(), centerServo()
 * - Claw: attachClaw(), openClaw(), closeClaw()
 * - Control: delay(), stopMotors()
 * 
 * HOW IT WORKS:
 * Obstacle avoidance is like walking through a crowded room:
 * 1. Look ahead
 * 2. See an obstacle? 
 * 3. Look left and right
 * 4. Turn toward the clearer path
 * 5. Keep moving
 * 6. Repeat
 * 
 * This is called a "sense-think-act" cycle:
 * - SENSE: Use sensors to gather information
 * - THINK: Make a decision based on that information
 * - ACT: Execute movement based on the decision
 */

#include <CarControl.h>

CarControl car(5, 6, 7, 8, 3, 2);

// Variables to store distances
int centerDist, leftDist, rightDist;
const int SAFE_DISTANCE = 25;  // Minimum safe distance in cm

void setup() {
  Serial.begin(9600);
  Serial.println("Lesson 10: Obstacle Detection and Avoidance");
  Serial.println("-------------------------------------------");
  
  car.setup();
  car.attachSensorServo(10);
  car.centerServo();
  
  Serial.println("\nPlace obstacles around the robot!");
  Serial.println("Watch it navigate around them...\n");
  delay(3000);
}

void loop() {
  // Example 1: Simple obstacle detection
  Serial.println("Example 1: Basic obstacle detection");
  
  centerDist = car.getCenterDistance();
  Serial.print("Distance ahead: ");
  Serial.print(centerDist);
  Serial.println(" cm");
  
  if(centerDist < SAFE_DISTANCE) {
    Serial.println("OBSTACLE DETECTED! Stopping.");
    car.stopMotors();
  } else {
    Serial.println("Path clear, moving forward");
    car.moveForward(150, 500);
  }
  delay(1000);
  
  // Example 2: Avoid and turn
  Serial.println("\nExample 2: Detect and avoid");
  
  centerDist = car.getCenterDistance();
  
  if(centerDist < SAFE_DISTANCE) {
    Serial.println("Obstacle ahead! Scanning alternatives...");
    
    leftDist = car.getLeftDistance();
    rightDist = car.getRightDistance();
    
    Serial.print("Left: ");
    Serial.print(leftDist);
    Serial.print(" cm, Right: ");
    Serial.print(rightDist);
    Serial.println(" cm");
    
    if(leftDist > rightDist) {
      Serial.println("Turning LEFT");
      car.turnLeft(150, 500);
    } else {
      Serial.println("Turning RIGHT");
      car.turnRight(150, 500);
    }
  } else {
    Serial.println("Path clear");
    car.moveForward(150, 500);
  }
  delay(1000);
  
  // Example 3: Continuous navigation
  Serial.println("\nExample 3: 10-second autonomous navigation");
  
  unsigned long startTime = millis();
  while(millis() - startTime < 10000) {  // Run for 10 seconds
    centerDist = car.getCenterDistance();
    
    if(centerDist < SAFE_DISTANCE) {
      // Obstacle detected!
      Serial.println("Obstacle! Checking alternatives...");
      car.stopMotors();
      
      leftDist = car.getLeftDistance();
      rightDist = car.getRightDistance();
      
      if(leftDist > rightDist && leftDist > SAFE_DISTANCE) {
        Serial.println("-> Going left");
        car.turnLeft(150, 500);
      } else if(rightDist > leftDist && rightDist > SAFE_DISTANCE) {
        Serial.println("-> Going right");
        car.turnRight(150, 500);
      } else {
        Serial.println("-> Backing up and turning around");
        car.moveBackward(150, 500);
        delay(300);
        car.turnRight(150, 1000);  // Turn 180 degrees
      }
      
      car.centerServo();  // Recenter sensor
    } else {
      // Path is clear
      car.moveForward(150, 200);
    }
    
    delay(100);  // Small delay between cycles
  }
  
  car.stopMotors();
  Serial.println("Navigation complete!");
  delay(3000);
  
  // Example 4: Smart avoidance with speed adjustment
  Serial.println("\nExample 4: Adaptive speed based on distance");
  
  for(int i = 0; i < 20; i++) {  // Run 20 cycles
    centerDist = car.getCenterDistance();
    
    if(centerDist > 60) {
      Serial.println("Far away - FAST");
      car.moveForward(220, 300);
    } else if(centerDist > 40) {
      Serial.println("Medium distance - MEDIUM SPEED");
      car.moveForward(160, 300);
    } else if(centerDist > SAFE_DISTANCE) {
      Serial.println("Getting close - SLOW");
      car.moveForward(100, 300);
    } else {
      Serial.println("Too close - AVOIDING");
      leftDist = car.getLeftDistance();
      rightDist = car.getRightDistance();
      
      if(leftDist > rightDist) {
        car.turnLeft(150, 500);
      } else {
        car.turnRight(150, 500);
      }
    }
    
    delay(200);
  }
  
  car.stopMotors();
  
  Serial.println("\nAll examples complete! Waiting 5 seconds...\n");
  delay(5000);
}

/*
 * MAIN CHALLENGE: Obstacle Course Navigator
 * 
 * Set up an obstacle course:
 * - Place 5-6 obstacles (boxes, books, bottles) randomly in a space
 * - Mark a start point and a goal point
 * 
 * Your robot must:
 * 1. Navigate from start to goal avoiding all obstacles
 * 2. Never get closer than 20cm to any obstacle
 * 3. Use scanning to choose the best path
 * 4. Run for 30 seconds trying to explore the space
 * 5. Print status messages as it navigates
 * 
 * Requirements:
 * - Use a while loop with millis() for timing
 * - Scan left and right when obstacle detected
 * - Choose the direction with more space
 * - If both directions are blocked, back up and turn around
 * - Recenter sensor after each scan
 * 
 * BONUS CHALLENGES:
 * 1. Keep a count of how many obstacles you've avoided
 * 2. Make the robot beep when it detects an obstacle (if you have buzzer)
 * 3. Add a "stuck detector" - if robot doesn't move forward for
 *    5 seconds, execute special "escape" maneuver
 * 4. Track and print total distance traveled (estimate)
 * 
 * ADVANCED CHALLENGE:
 * Implement a "memory" system:
 * - If robot keeps encountering the same obstacle (distance pattern repeats),
 *   try a different strategy (turn more, back up farther, etc.)
 * - Use variables to track recent decisions
 * 
 * EXPERT CHALLENGE:
 * Create a "wall follower":
 * - Keep the right side at exactly 30cm from wall/obstacle
 * - Follow along walls to navigate around obstacles
 * - This is a common maze-solving technique!
 * 
 * Pseudo-code for wall following:
 * 
 * while(running) {
 *   rightDist = getRightDistance()
 *   if(rightDist > 35) turn slightly right
 *   if(rightDist < 25) turn slightly left
 *   else move forward
 *   
 *   if(obstacle ahead) turn left 90 degrees
 * }
 */
