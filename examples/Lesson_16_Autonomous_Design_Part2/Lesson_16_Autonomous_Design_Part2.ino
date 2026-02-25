/*
 * LESSON 16: Autonomous Design - Part 2 (Advanced)
 * 
 * LESSON OBJECTIVES:
 * - Create complex autonomous behaviors
 * - Implement multi-stage missions
 * - Use advanced decision-making
 * - Design complete autonomous systems
 * 
 * ADVANCED CONCEPTS:
 * - State machines with multiple states
 * - Mission planning and execution
 * - Sensor fusion (combining multiple sensors)
 * - Adaptive behavior based on environment
 * - Error recovery and fault tolerance
 * 
 * This lesson shows you how to build truly intelligent robots
 * that can complete complex tasks without human help!
 */

#include <CarControl.h>

CarControl car(5, 6, 7, 8, 3, 2);

// Advanced configuration
const int SAFE_DISTANCE = 35;
const int CLOSE_DISTANCE = 15;
const int LINE_THRESHOLD = 500;
const int CRUISE_SPEED = 170;
const int CAREFUL_SPEED = 100;

// Advanced state machine
enum MissionState {
  INIT,
  SEARCHING,
  APPROACHING_OBJECT,
  GRABBING_OBJECT,
  NAVIGATING_TO_GOAL,
  DELIVERING_OBJECT,
  RETURNING_TO_START,
  MISSION_COMPLETE,
  ERROR_RECOVERY
};

MissionState state = INIT;
int objectsDelivered = 0;
int errorCount = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Lesson 16: Autonomous Design - Part 2");
  Serial.println("-------------------------------------");
  
  car.setup();
  car.initLineSensors();
  car.attachSensorServo(10);
  car.attachClaw(11);
  car.centerServo();
  car.openClaw();
  
  Serial.println("\nADVANCED AUTONOMOUS SYSTEM INITIALIZED");
  Serial.println("======================================\n");
  delay(2000);
}

// Print current state
void printState() {
  Serial.print("[STATE: ");
  switch(state) {
    case INIT: Serial.print("INIT"); break;
    case SEARCHING: Serial.print("SEARCHING"); break;
    case APPROACHING_OBJECT: Serial.print("APPROACHING"); break;
    case GRABBING_OBJECT: Serial.print("GRABBING"); break;
    case NAVIGATING_TO_GOAL: Serial.print("NAVIGATING"); break;
    case DELIVERING_OBJECT: Serial.print("DELIVERING"); break;
    case RETURNING_TO_START: Serial.print("RETURNING"); break;
    case MISSION_COMPLETE: Serial.print("COMPLETE"); break;
    case ERROR_RECOVERY: Serial.print("ERROR_RECOVERY"); break;
  }
  Serial.println("]");
}

// Advanced scanning function
int findBestDirection() {
  Serial.println("  Performing detailed scan...");
  
  int centerDist = car.getCenterDistance();
  delay(300);
  int leftDist = car.getLeftDistance();
  delay(300);
  int rightDist = car.getRightDistance();
  delay(300);
  car.centerServo();
  
  Serial.print("  Scan results: L=");
  Serial.print(leftDist);
  Serial.print(" C=");
  Serial.print(centerDist);
  Serial.print(" R=");
  Serial.println(rightDist);
  
  // Return direction code: 0=left, 1=center, 2=right
  if(centerDist > leftDist && centerDist > rightDist) return 1;
  if(leftDist > rightDist) return 0;
  return 2;
}

// Smart navigation with obstacle avoidance
void navigateToward(int targetDirection) {
  int distance = car.getCenterDistance();
  
  if(distance < SAFE_DISTANCE) {
    // Obstacle in path
    int best = findBestDirection();
    
    if(best == 0) {
      Serial.println("  Avoiding obstacle - turning left");
      car.turnLeft(CRUISE_SPEED, 400);
    } else if(best == 2) {
      Serial.println("  Avoiding obstacle - turning right");
      car.turnRight(CRUISE_SPEED, 400);
    } else {
      Serial.println("  Path ahead clear - proceeding");
      car.moveForward(CRUISE_SPEED, 300);
    }
  } else if(distance > 60) {
    // Clear path - move fast
    Serial.println("  Clear path - cruising");
    car.moveForward(CRUISE_SPEED + 30, 400);
  } else {
    // Normal movement
    car.moveForward(CRUISE_SPEED, 300);
  }
}

// Precise approach to object
boolean approachObject() {
  Serial.println("  Approaching object precisely...");
  
  int distance = car.getCenterDistance();
  int attempts = 0;
  
  while(distance > 8 && distance < 100 && attempts < 20) {
    if(distance > 20) {
      car.moveForward(CAREFUL_SPEED, 150);
    } else {
      car.moveForward(CAREFUL_SPEED - 30, 80);
    }
    
    distance = car.getCenterDistance();
    Serial.print("  Distance: ");
    Serial.println(distance);
    delay(100);
    attempts++;
  }
  
  return (distance <= 12);  // Success if within 12cm
}

// Follow line to destination
boolean followLineToGoal(unsigned long duration) {
  Serial.println("  Following line to goal...");
  
  unsigned long startTime = millis();
  
  while(millis() - startTime < duration) {
    int leftValue = car.getLineSensorLeft();
    int middleValue = car.getLineSensorMiddle();
    int rightValue = car.getLineSensorRight();
    
    // Check for intersection (goal marker)
    if(leftValue < LINE_THRESHOLD && 
       middleValue < LINE_THRESHOLD && 
       rightValue < LINE_THRESHOLD) {
      Serial.println("  *** INTERSECTION DETECTED - GOAL REACHED! ***");
      return true;
    }
    
    // Regular line following
    if(middleValue < LINE_THRESHOLD) {
      car.moveForward(120, 80);
    } else if(leftValue < LINE_THRESHOLD) {
      car.turnLeft(100, 40);
    } else if(rightValue < LINE_THRESHOLD) {
      car.turnRight(100, 40);
    } else {
      // Lost line
      Serial.println("  Lost line - stopping");
      return false;
    }
    
    delay(50);
  }
  
  return false;  // Timeout
}

void loop() {
  Serial.println("\n=== ADVANCED AUTONOMOUS MISSION ===");
  Serial.println("Mission: Search, Grab, Deliver\n");
  delay(2000);
  
  state = INIT;
  objectsDelivered = 0;
  errorCount = 0;
  
  unsigned long missionStartTime = millis();
  unsigned long missionTimeout = 60000;  // 60 second mission
  
  while(millis() - missionStartTime < missionTimeout && state != MISSION_COMPLETE) {
    
    printState();
    
    switch(state) {
      
      case INIT:
        Serial.println("  Initializing mission...");
        car.openClaw();
        car.centerServo();
        delay(1000);
        state = SEARCHING;
        break;
      
      case SEARCHING:
        Serial.println("  Searching for objects...");
        {
          int centerDist = car.getCenterDistance();
          
          if(centerDist < 25 && centerDist > 5) {
            Serial.println("  *** OBJECT DETECTED! ***");
            state = APPROACHING_OBJECT;
          } else {
            // Navigate while searching
            navigateToward(1);  // Forward
            delay(200);
          }
        }
        break;
      
      case APPROACHING_OBJECT:
        if(approachObject()) {
          Serial.println("  Object reached successfully!");
          state = GRABBING_OBJECT;
        } else {
          Serial.println("  Failed to approach - returning to search");
          errorCount++;
          state = (errorCount > 3) ? ERROR_RECOVERY : SEARCHING;
        }
        break;
      
      case GRABBING_OBJECT:
        Serial.println("  Executing grab sequence...");
        delay(500);
        car.closeClaw();
        delay(1500);
        Serial.println("  Object secured!");
        delay(500);
        car.moveBackward(CAREFUL_SPEED, 500);
        delay(500);
        state = NAVIGATING_TO_GOAL;
        break;
      
      case NAVIGATING_TO_GOAL:
        Serial.println("  Navigating to delivery zone...");
        // Simple strategy: back up, turn, then drive forward
        car.turnLeft(CRUISE_SPEED, 600);
        delay(500);
        car.moveForward(CRUISE_SPEED, 2000);
        state = DELIVERING_OBJECT;
        break;
      
      case DELIVERING_OBJECT:
        Serial.println("  Delivering object...");
        delay(1000);
        car.openClaw();
        delay(1500);
        objectsDelivered++;
        Serial.print("  *** OBJECT DELIVERED! (Count: ");
        Serial.print(objectsDelivered);
        Serial.println(") ***");
        delay(1000);
        
        // Check if mission complete
        if(objectsDelivered >= 1) {
          state = MISSION_COMPLETE;
        } else {
          state = RETURNING_TO_START;
        }
        break;
      
      case RETURNING_TO_START:
        Serial.println("  Returning to search area...");
        car.moveBackward(CRUISE_SPEED, 1500);
        delay(500);
        car.turnRight(CRUISE_SPEED, 600);
        delay(500);
        state = SEARCHING;
        break;
      
      case ERROR_RECOVERY:
        Serial.println("  !!! ERROR RECOVERY MODE !!!");
        Serial.println("  Executing recovery maneuvers...");
        car.moveBackward(CRUISE_SPEED, 1000);
        delay(500);
        car.turnRight(CRUISE_SPEED, 800);
        delay(500);
        errorCount = 0;
        state = SEARCHING;
        break;
      
      case MISSION_COMPLETE:
        Serial.println("  ======================");
        Serial.println("  MISSION ACCOMPLISHED!");
        Serial.println("  ======================");
        Serial.print("  Objects delivered: ");
        Serial.println(objectsDelivered);
        Serial.print("  Mission time: ");
        Serial.print((millis() - missionStartTime) / 1000);
        Serial.println(" seconds");
        car.stopMotors();
        break;
    }
    
    delay(100);
  }
  
  if(state != MISSION_COMPLETE) {
    Serial.println("\n*** MISSION TIMEOUT ***");
    Serial.print("Objects delivered: ");
    Serial.println(objectsDelivered);
  }
  
  car.stopMotors();
  Serial.println("\nWaiting 15 seconds before next mission...\n");
  delay(15000);
}

/*
 * FINAL CHALLENGE: Design Your Own Autonomous Robot
 * 
 * Now it's time to create your own autonomous robot system!
 * 
 * Choose ONE of these missions or create your own:
 * 
 * MISSION 1: Warehouse Robot
 * - Navigate to storage area (follow line)
 * - Find and grab a package (object detection)
 * - Deliver to loading dock (follow different colored line)
 * - Return to storage area
 * - Repeat for 3 packages
 * 
 * MISSION 2: Security Patrol with Response
 * - Patrol defined perimeter (follow path or walls)
 * - Scan for intruders (unexpected obstacles)
 * - When intruder found:
 *   * Approach and investigate
 *   * Flash LED and beep
 *   * Report location via Serial
 *   * Continue patrol
 * - Complete 3 full patrol circuits
 * 
 * MISSION 3: Maze Explorer and Mapper
 * - Navigate through a maze
 * - Use right-wall following algorithm
 * - Find the goal (marked with line intersection)
 * - Remember the path taken
 * - Return to start using same path
 * 
 * MISSION 4: Search and Rescue
 * - Search an area for "survivors" (small objects)
 * - Grab survivors with claw
 * - Deliver to "safe zone" (marked area)
 * - Continue searching until time limit
 * - Report number of survivors rescued
 * 
 * MISSION 5: Create Your Own!
 * Design a unique mission that uses:
 * - At least 4 different sensors/actuators
 * - At least 5 different states
 * - Error handling/recovery
 * - A clear success criteria
 * 
 * Requirements for ALL missions:
 * - Use a state machine with at least 5 states
 * - Include error detection and recovery
 * - Print clear status messages
 * - Complete autonomously (no human intervention)
 * - Handle unexpected obstacles
 * - Have a clear success/failure criteria
 * 
 * Advanced Features to Add:
 * - Mission timer and optimization
 * - Performance scoring
 * - Multiple strategies (A/B testing)
 * - Adaptive behavior based on success rate
 * - Data logging and analysis
 * 
 * Presentation:
 * When complete, prepare to demonstrate:
 * - Your mission objectives
 * - Your robot's strategy
 * - How it handles errors
 * - Live demonstration
 * - Lessons learned and improvements
 * 
 * This is your final project - be creative and ambitious!
 * Use everything you've learned to create something amazing!
 */
