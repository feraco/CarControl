/*
 * LESSON 12: Advanced Obstacle Course
 * 
 * LESSON OBJECTIVES:
 * - Navigate complex obstacle arrangements
 * - Implement advanced decision-making algorithms
 * - Handle tight spaces and multiple obstacles
 * - Optimize navigation strategy
 * 
 * HOW IT WORKS:
 * Advanced obstacle navigation requires:
 * 1. Better scanning - check multiple angles
 * 2. Smarter decisions - consider multiple factors
 * 3. Recovery strategies - handle getting stuck
 * 4. Adaptive behavior - change strategy based on situation
 * 
 * New concepts:
 * - Multi-point scanning (checking more than just left/center/right)
 * - Stuck detection (robot hasn't made progress)
 * - Escape maneuvers (special moves when trapped)
 * - Path memory (remembering recent decisions)
 */

#include <CarControl.h>

CarControl car(5, 6, 7, 8, 3, 2);

// Advanced configuration
const int SAFE_DISTANCE = 35;
const int CRITICAL_DISTANCE = 20;
const int MOVE_SPEED = 170;
const int SCAN_SPEED = 150;

// Variables for advanced features
int consecutiveTurns = 0;        // Track if we're turning a lot (might be stuck)
unsigned long lastForwardTime = 0;  // Track when we last moved forward

void setup() {
  Serial.begin(9600);
  Serial.println("Lesson 12: Advanced Obstacle Course");
  Serial.println("-----------------------------------");
  
  car.setup();
  car.attachSensorServo(10);
  car.centerServo();
  
  Serial.println("\nADVANCED NAVIGATION READY!");
  Serial.println("Starting in 3 seconds...\n");
  delay(3000);
}

// Function to perform detailed scan
void detailedScan(int &left, int &center, int &right) {
  center = car.getCenterDistance();
  delay(200);
  left = car.getLeftDistance();
  delay(200);
  right = car.getRightDistance();
  delay(200);
  car.centerServo();
  
  Serial.print("[SCAN] L:");
  Serial.print(left);
  Serial.print(" C:");
  Serial.print(center);
  Serial.print(" R:");
  Serial.println(right);
}

// Function to detect if stuck
boolean isStuck() {
  unsigned long timeSinceForward = millis() - lastForwardTime;
  return (timeSinceForward > 5000);  // Stuck if no forward movement for 5 seconds
}

// Function to execute escape maneuver
void escapeManeuver() {
  Serial.println("\n!!! STUCK - EXECUTING ESCAPE !!!");
  
  // Back up
  Serial.println("Backing up...");
  car.moveBackward(MOVE_SPEED, 1000);
  delay(500);
  
  // Turn around
  Serial.println("Turning around...");
  car.turnRight(MOVE_SPEED, 1200);  // More than 180 degrees
  delay(500);
  
  // Move forward a bit
  Serial.println("Moving forward...");
  car.moveForward(MOVE_SPEED, 800);
  delay(500);
  
  // Reset counters
  consecutiveTurns = 0;
  lastForwardTime = millis();
  
  Serial.println("Escape complete!\n");
}

// Improved decision making
void makeNavigationDecision(int left, int center, int right) {
  
  // Check if all paths are blocked
  if(left < CRITICAL_DISTANCE && center < CRITICAL_DISTANCE && right < CRITICAL_DISTANCE) {
    Serial.println("[DECISION] All paths blocked - Escape!");
    escapeManeuver();
    return;
  }
  
  // Check if center is clear
  if(center > SAFE_DISTANCE) {
    Serial.println("[DECISION] Center clear - Forward!");
    car.moveForward(MOVE_SPEED, 400);
    consecutiveTurns = 0;  // Reset turn counter
    lastForwardTime = millis();
    return;
  }
  
  // Center is blocked - need to turn
  // Calculate which side has more space
  int spaceDifference = left - right;
  
  if(spaceDifference > 10) {
    // Left is significantly clearer
    Serial.println("[DECISION] Left is clearer - Turn left");
    car.turnLeft(SCAN_SPEED, 450);
    consecutiveTurns++;
  } else if(spaceDifference < -10) {
    // Right is significantly clearer
    Serial.println("[DECISION] Right is clearer - Turn right");
    car.turnRight(SCAN_SPEED, 450);
    consecutiveTurns++;
  } else {
    // Similar distances - choose the one with more space
    if(left > right) {
      Serial.println("[DECISION] Slight left advantage - Turn left");
      car.turnLeft(SCAN_SPEED, 400);
    } else {
      Serial.println("[DECISION] Slight right advantage - Turn right");
      car.turnRight(SCAN_SPEED, 400);
    }
    consecutiveTurns++;
  }
  
  // Check if we've been turning too much (might be stuck)
  if(consecutiveTurns > 4) {
    Serial.println("[WARNING] Too many turns - may be stuck");
    escapeManeuver();
  }
}

void loop() {
  Serial.println("=== ADVANCED OBSTACLE COURSE RUN ===");
  Serial.println("Course duration: 30 seconds\n");
  
  unsigned long startTime = millis();
  lastForwardTime = millis();
  consecutiveTurns = 0;
  int obstaclesNegotiated = 0;
  
  // Main navigation loop - runs for 30 seconds
  while(millis() - startTime < 30000) {
    
    // Check if stuck
    if(isStuck()) {
      Serial.println("\n[STUCK DETECTOR] No forward progress!");
      escapeManeuver();
    }
    
    // Perform detailed scan
    int leftDist, centerDist, rightDist;
    detailedScan(leftDist, centerDist, rightDist);
    
    // Check if we're approaching an obstacle
    if(centerDist < SAFE_DISTANCE) {
      obstaclesNegotiated++;
      Serial.print("[OBSTACLE #");
      Serial.print(obstaclesNegotiated);
      Serial.println("]");
    }
    
    // Make navigation decision
    makeNavigationDecision(leftDist, centerDist, rightDist);
    
    delay(150);  // Small delay between cycles
  }
  
  // Course complete!
  car.stopMotors();
  Serial.println("\n=== COURSE COMPLETE! ===");
  Serial.print("Obstacles negotiated: ");
  Serial.println(obstaclesNegotiated);
  Serial.print("Total turn sequences: ");
  Serial.println(consecutiveTurns);
  Serial.println("\nWaiting 10 seconds before next run...\n");
  delay(10000);
}

/*
 * CHALLENGE: Master the Advanced Course
 * 
 * Course Setup:
 * Create a more challenging course:
 * - 8-10 obstacles in a 2m x 2m area
 * - Include tight spaces (barely enough room to pass)
 * - Create "dead ends" the robot must detect and escape
 * - Add corners and narrow passages
 * 
 * Your Mission:
 * 1. Navigate the complex course for 45 seconds
 * 2. Avoid all obstacles
 * 3. Recover from dead ends automatically
 * 4. Show smooth, intelligent navigation
 * 
 * Required Features:
 * - Stuck detection and escape
 * - Multi-point scanning
 * - Adaptive decision making
 * - Clear status reporting
 * 
 * BONUS CHALLENGES:
 * 1. Add a "confidence score" to each decision:
 *    - High confidence: Big difference between left and right
 *    - Low confidence: Similar distances
 *    - Make smaller, more cautious moves when confidence is low
 * 
 * 2. Implement "momentum":
 *    - If robot has been turning left, slightly prefer continuing left
 *    - This can help navigate around large obstacles
 * 
 * 3. Add speed variation:
 *    - Fast when lots of open space
 *    - Slow when in tight quarters
 *    - Very slow when confidence is low
 * 
 * 4. Create a "map memory":
 *    - Store recent turn directions
 *    - If pattern repeats (stuck in loop), try opposite direction
 * 
 * ADVANCED CHALLENGE:
 * Implement "wall following" mode:
 * - When stuck, switch to wall-following algorithm
 * - Keep right side at constant distance
 * - Follow wall until you find open space
 * - Then switch back to regular navigation
 * 
 * EXPERT CHALLENGE:
 * Create multiple navigation "personalities":
 * 
 * aggressive mode:
 * - High speed
 * - Small safety distance
 * - Quick decisions
 * 
 * cautious mode:
 * - Slow speed
 * - Large safety distance
 * - Multiple scans before decision
 * 
 * explorer mode:
 * - Prefer paths not recently taken
 * - Seek maximum distance readings
 * - Avoid retracing steps
 * 
 * Allow switching between modes or combine them!
 */
