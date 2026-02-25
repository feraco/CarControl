/*
 * LESSON 15: Autonomous Robot Design - Part 1
 * 
 * LESSON OBJECTIVES:
 * - Combine all sensors and skills
 * - Create autonomous behaviors
 * - Implement decision-making systems
 * - Design robot "missions"
 * 
 * SKILLS INTEGRATION:
 * This lesson combines everything you've learned:
 * ✓ Linear motion (forward/backward)
 * ✓ Rotation (turning)
 * ✓ Ultrasonic sensing (obstacle detection)
 * ✓ Servo control (scanning, claw)
 * ✓ Line following
 * ✓ Decision making (if-else logic)
 * 
 * HOW IT WORKS:
 * An autonomous robot can:
 * 1. Sense its environment (sensors)
 * 2. Make decisions (your code logic)
 * 3. Take actions (movement)
 * 4. Repeat (continuous loop)
 * 
 * Robot "Behaviors" are like modes:
 * - EXPLORE mode: Wander and avoid obstacles
 * - FOLLOW mode: Follow lines
 * - SEEK mode: Look for objects
 * - FETCH mode: Pick up and deliver objects
 * 
 * You can switch between behaviors based on what the robot senses!
 */

#include <CarControl.h>

CarControl car(5, 6, 7, 8, 3, 2);

// Configuration
const int SAFE_DISTANCE = 30;
const int LINE_THRESHOLD = 500;
const int MOVE_SPEED = 160;

// Behavior states
enum RobotState {
  EXPLORING,
  LINE_FOLLOWING,
  OBJECT_FOUND,
  RETURNING_HOME
};

RobotState currentState = EXPLORING;

void setup() {
  Serial.begin(9600);
  Serial.println("Lesson 15: Autonomous Design - Part 1");
  Serial.println("-------------------------------------");
  
  car.setup();
  car.initLineSensors();
  car.attachSensorServo(10);
  car.attachClaw(11);
  car.centerServo();
  car.openClaw();
  
  Serial.println("\nAUTONOMOUS ROBOT READY!");
  Serial.println("Mission: Explore and navigate\n");
  delay(3000);
}

// Behavior 1: Explore the environment
void exploreBehavior() {
  Serial.println("[MODE: EXPLORING]");
  
  int centerDist = car.getCenterDistance();
  
  if(centerDist < SAFE_DISTANCE) {
    // Obstacle ahead - scan and choose direction
    Serial.println("  Obstacle detected - Scanning...");
    int leftDist = car.getLeftDistance();
    int rightDist = car.getRightDistance();
    car.centerServo();
    
    if(leftDist > rightDist) {
      Serial.println("  Turning left");
      car.turnLeft(MOVE_SPEED, 500);
    } else {
      Serial.println("  Turning right");
      car.turnRight(MOVE_SPEED, 500);
    }
  } else {
    // Path clear - move forward
    Serial.println("  Path clear - Moving forward");
    car.moveForward(MOVE_SPEED, 400);
  }
}

// Behavior 2: Follow a line
void lineFollowBehavior() {
  Serial.println("[MODE: LINE FOLLOWING]");
  
  int leftValue = car.getLineSensorLeft();
  int middleValue = car.getLineSensorMiddle();
  int rightValue = car.getLineSensorRight();
  
  if(middleValue < LINE_THRESHOLD) {
    car.moveForward(140, 100);
  } else if(leftValue < LINE_THRESHOLD) {
    car.turnLeft(120, 50);
  } else if(rightValue < LINE_THRESHOLD) {
    car.turnRight(120, 50);
  } else {
    // Lost the line - switch to exploring
    Serial.println("  Lost line - Switching to EXPLORE mode");
    currentState = EXPLORING;
  }
}

// Behavior 3: Object detected
void objectFoundBehavior() {
  Serial.println("[MODE: OBJECT FOUND]");
  
  Serial.println("  Approaching object...");
  int distance = car.getCenterDistance();
  
  while(distance > 10 && distance < 50) {
    car.moveForward(100, 100);
    distance = car.getCenterDistance();
    Serial.print("  Distance: ");
    Serial.println(distance);
    delay(100);
  }
  
  if(distance <= 10) {
    Serial.println("  Grabbing object!");
    car.stopMotors();
    delay(500);
    car.closeClaw();
    delay(1500);
    
    Serial.println("  Object acquired - Returning home");
    currentState = RETURNING_HOME;
  }
}

// Behavior 4: Return to home
void returnHomeBehavior() {
  Serial.println("[MODE: RETURNING HOME]");
  
  // Simple return: back up and turn around
  Serial.println("  Backing up...");
  car.moveBackward(MOVE_SPEED, 1000);
  delay(500);
  
  Serial.println("  Turning around...");
  car.turnRight(MOVE_SPEED, 1000);
  delay(500);
  
  Serial.println("  Moving to home...");
  car.moveForward(MOVE_SPEED, 2000);
  
  Serial.println("  Releasing object");
  car.openClaw();
  delay(1000);
  
  Serial.println("  Mission complete - Resuming exploration");
  currentState = EXPLORING;
}

void loop() {
  // Example 1: Simple autonomous exploration
  Serial.println("\n=== Mission 1: 20-Second Exploration ===\n");
  
  currentState = EXPLORING;
  unsigned long startTime = millis();
  
  while(millis() - startTime < 20000) {
    exploreBehavior();
    delay(100);
  }
  
  car.stopMotors();
  Serial.println("\nMission 1 complete!\n");
  delay(3000);
  
  // Example 2: Hybrid navigation (explore + line follow)
  Serial.println("=== Mission 2: Hybrid Navigation ===\n");
  Serial.println("Robot will explore until it finds a line,");
  Serial.println("then follow that line!\n");
  delay(2000);
  
  currentState = EXPLORING;
  startTime = millis();
  
  while(millis() - startTime < 30000) {
    // Check if we've found a line
    int middleValue = car.getLineSensorMiddle();
    
    if(middleValue < LINE_THRESHOLD && currentState == EXPLORING) {
      Serial.println("\n*** LINE DETECTED! Switching to line follow mode ***\n");
      currentState = LINE_FOLLOWING;
    }
    
    // Execute current behavior
    if(currentState == EXPLORING) {
      exploreBehavior();
    } else if(currentState == LINE_FOLLOWING) {
      lineFollowBehavior();
    }
    
    delay(50);
  }
  
  car.stopMotors();
  Serial.println("\nMission 2 complete!\n");
  delay(3000);
  
  // Example 3: Room patrol
  Serial.println("=== Mission 3: Room Patrol ===\n");
  Serial.println("Robot will patrol the area, avoiding obstacles");
  Serial.println("and changing direction every 5 seconds\n");
  delay(2000);
  
  startTime = millis();
  unsigned long lastTurnTime = millis();
  
  while(millis() - startTime < 25000) {
    int centerDist = car.getCenterDistance();
    
    // Obstacle avoidance
    if(centerDist < SAFE_DISTANCE) {
      car.stopMotors();
      int leftDist = car.getLeftDistance();
      int rightDist = car.getRightDistance();
      car.centerServo();
      
      if(leftDist > rightDist) {
        car.turnLeft(MOVE_SPEED, 500);
      } else {
        car.turnRight(MOVE_SPEED, 500);
      }
      
      lastTurnTime = millis();
    }
    // Periodic direction change for thorough patrol
    else if(millis() - lastTurnTime > 5000) {
      Serial.println("  Patrol turn");
      car.turnRight(MOVE_SPEED, 300);  // Small turn
      lastTurnTime = millis();
    }
    // Normal movement
    else {
      car.moveForward(MOVE_SPEED, 300);
    }
    
    delay(100);
  }
  
  car.stopMotors();
  Serial.println("\nMission 3 complete!\n");
  
  Serial.println("All missions complete! Waiting 10 seconds...\n");
  delay(10000);
}

/*
 * CHALLENGE: Security Patrol Robot
 * 
 * Create an autonomous security patrol robot that:
 * 
 * 1. Patrols a defined area (2m x 2m)
 * 2. Avoids obstacles automatically
 * 3. When it detects an object closer than 15cm:
 *    - Stop and "investigate" (scan left and right)
 *    - Print "INTRUDER DETECTED!" 
 *    - Back up and continue patrol
 * 4. Changes patrol direction every 10 seconds
 * 5. Runs for 60 seconds total
 * 
 * Requirements:
 * - Uses state machine (different modes)
 * - Smooth obstacle avoidance
 * - Clear status reporting
 * - Doesn't get stuck
 * 
 * BONUS CHALLENGES:
 * 1. Home base:
 *    - Mark a home position with a line
 *    - After 60 seconds, use line following to return home
 *    - Stop when all sensors detect line (at home)
 * 
 * 2. Perimeter patrol:
 *    - Follow walls at a constant distance (wall following)
 *    - Make a complete circuit around the room
 *    - Return to starting position
 * 
 * 3. Intruder response:
 *    - When object detected, approach it slowly
 *    - Stop 10cm away
 *    - Flash RGB LED red
 *    - Beep alarm (if you have buzzer)
 *    - Back away and resume patrol
 * 
 * ADVANCED CHALLENGE:
 * Create a "Fetch and Deliver" robot:
 * - Explore until object found (distance < 15cm)
 * - Approach and grab object with claw
 * - Follow black line to delivery zone
 * - Release object
 * - Return to exploration mode
 * - Repeat for multiple objects
 * 
 * EXPERT CHALLENGE:
 * Implement a "learning" behavior:
 * - Track which areas have obstacles (store in memory)
 * - Avoid previously-found obstacle areas
 * - Build a simple "map" of the environment
 * - Navigate more efficiently on each patrol
 * 
 * Use arrays to store obstacle information:
 * boolean obstacleMap[10];  // Remember 10 obstacle locations
 */
