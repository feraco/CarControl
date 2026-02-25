/*
 * LESSON 14: Line Following
 * 
 * LESSON OBJECTIVES:
 * - Make the robot follow a black line
 * - Implement line-following algorithms
 * - Handle curves and turns in the line
 * - Create smooth, stable line following
 * 
 * NEW COMMANDS:
 * - followLine(threshold) - Built-in line following function
 *   - threshold: Value to distinguish black from white (usually ~500)
 * 
 * - followLineMultiSensor(threshold) - Alternative line following using all 3 sensors
 * 
 * - stopAtLine(threshold) - Stop when line is detected
 * 
 * HOW IT WORKS:
 * Line following uses a simple "correction" algorithm:
 * 
 * 1. If CENTER sensor sees line:
 *    → Robot is aligned → Move forward
 * 
 * 2. If LEFT sensor sees line (CENTER doesn't):
 *    → Robot is too far right → Turn left to correct
 * 
 * 3. If RIGHT sensor sees line (CENTER doesn't):
 *    → Robot is too far left → Turn right to correct
 * 
 * 4. If NO sensors see line:
 *    → Robot is off the line → Stop or search
 * 
 * This creates a "wiggle" behavior - constantly making small
 * corrections to stay on the line. The faster you correct,
 * the less wiggle you'll have!
 * 
 * Think of it like walking on a balance beam:
 * - Feel yourself tilting left? Shift right.
 * - Feel yourself tilting right? Shift left.
 * - Feel balanced? Keep going straight.
 */

#include <CarControl.h>

CarControl car(5, 6, 7, 8, 3, 2);

const int LINE_THRESHOLD = 500;  // Adjust for your setup
const int FOLLOW_SPEED = 140;     // Speed for line following (not too fast!)
const int TURN_SPEED = 120;       // Speed for correction turns

void setup() {
  Serial.begin(9600);
  Serial.println("Lesson 14: Line Following");
  Serial.println("-------------------------");
  
  car.setup();
  car.initLineSensors();
  
  Serial.println("\nCreate a test track:");
  Serial.println("- Use black electrical tape");
  Serial.println("- Make straight line, then gentle curve");
  Serial.println("- Line should be 1.5-2cm wide");
  Serial.println("\nPlace robot on line and watch it follow!\n");
  
  delay(3000);
}

void loop() {
  // Example 1: Using the built-in followLine function
  Serial.println("Example 1: Built-in line following (10 seconds)");
  
  unsigned long startTime = millis();
  while(millis() - startTime < 10000) {
    car.followLine(LINE_THRESHOLD);
    delay(50);  // Small delay for stability
  }
  
  car.stopMotors();
  Serial.println("Example 1 complete\n");
  delay(3000);
  
  // Example 2: Manual line following with status messages
  Serial.println("Example 2: Manual line following with feedback (15 seconds)");
  
  startTime = millis();
  while(millis() - startTime < 15000) {
    int leftValue = car.getLineSensorLeft();
    int middleValue = car.getLineSensorMiddle();
    int rightValue = car.getLineSensorRight();
    
    boolean leftOnLine = (leftValue < LINE_THRESHOLD);
    boolean middleOnLine = (middleValue < LINE_THRESHOLD);
    boolean rightOnLine = (rightValue < LINE_THRESHOLD);
    
    if(middleOnLine) {
      // Line is centered - go straight
      Serial.println("Centered - Forward");
      car.moveForward(FOLLOW_SPEED, 100);
    } else if(leftOnLine) {
      // Line is to the left - turn left
      Serial.println("Line left - Correcting left");
      car.turnLeft(TURN_SPEED, 50);
    } else if(rightOnLine) {
      // Line is to the right - turn right
      Serial.println("Line right - Correcting right");
      car.turnRight(TURN_SPEED, 50);
    } else {
      // No line detected - stop
      Serial.println("Lost line - Stopping");
      car.stopMotors();
      delay(500);
    }
    
    delay(50);
  }
  
  car.stopMotors();
  Serial.println("Example 2 complete\n");
  delay(3000);
  
  // Example 3: Improved line following with smoother corrections
  Serial.println("Example 3: Smooth line following (20 seconds)");
  
  startTime = millis();
  while(millis() - startTime < 20000) {
    int leftValue = car.getLineSensorLeft();
    int middleValue = car.getLineSensorMiddle();
    int rightValue = car.getLineSensorRight();
    
    // Check which sensors see the line
    boolean L = (leftValue < LINE_THRESHOLD);
    boolean M = (middleValue < LINE_THRESHOLD);
    boolean R = (rightValue < LINE_THRESHOLD);
    
    if(M && !L && !R) {
      // Perfect center
      car.moveForward(FOLLOW_SPEED + 20, 80);
    } else if(M && L && !R) {
      // Slight left
      car.moveForward(FOLLOW_SPEED, 60);
      car.turnLeft(TURN_SPEED - 20, 30);
    } else if(M && R && !L) {
      // Slight right
      car.moveForward(FOLLOW_SPEED, 60);
      car.turnRight(TURN_SPEED - 20, 30);
    } else if(L && !M && !R) {
      // Sharp left
      car.turnLeft(TURN_SPEED, 60);
    } else if(R && !M && !L) {
      // Sharp right
      car.turnRight(TURN_SPEED, 60);
    } else if(L && M && R) {
      // All sensors on line (intersection or wide line)
      Serial.println("Intersection!");
      car.moveForward(FOLLOW_SPEED, 100);
    } else {
      // No line
      car.stopMotors();
      delay(100);
    }
    
    delay(30);
  }
  
  car.stopMotors();
  Serial.println("Example 3 complete\n");
  delay(3000);
  
  // Example 4: Line following with obstacle detection
  Serial.println("Example 4: Line follow with obstacle stop (20 seconds)");
  
  car.attachSensorServo(10);
  car.centerServo();
  
  startTime = millis();
  while(millis() - startTime < 20000) {
    // Check for obstacles
    int distance = car.getDistanceToObstacle();
    if(distance < 20) {
      Serial.println("OBSTACLE! Stopping.");
      car.stopMotors();
      delay(2000);
      break;
    }
    
    // Follow the line
    int leftValue = car.getLineSensorLeft();
    int middleValue = car.getLineSensorMiddle();
    int rightValue = car.getLineSensorRight();
    
    if(middleValue < LINE_THRESHOLD) {
      car.moveForward(FOLLOW_SPEED, 80);
    } else if(leftValue < LINE_THRESHOLD) {
      car.turnLeft(TURN_SPEED, 40);
    } else if(rightValue < LINE_THRESHOLD) {
      car.turnRight(TURN_SPEED, 40);
    } else {
      car.stopMotors();
    }
    
    delay(40);
  }
  
  car.stopMotors();
  Serial.println("Example 4 complete\n");
  
  Serial.println("All examples complete! Waiting 10 seconds...\n");
  delay(10000);
}

/*
 * CHALLENGE: Create a Line-Following Track
 * 
 * Track Setup:
 * Use black electrical tape on white poster board or floor:
 * 
 * 1. Straight section (50cm)
 * 2. Gentle curve to the right
 * 3. Straight section (30cm)
 * 4. Gentle curve to the left
 * 5. Straight section to finish (40cm)
 * 
 * Your Mission:
 * Create a program that:
 * 1. Follows the entire track smoothly
 * 2. Handles both curves without losing the line
 * 3. Stops at the end of the track
 * 4. Prints status every 2 seconds (distance traveled, position, etc.)
 * 5. Completes track in under 30 seconds
 * 
 * Success Criteria:
 * - Follows line without going off
 * - Smooth movement (minimal wiggling)
 * - Handles curves well
 * - Reaches the end
 * 
 * Tuning Tips:
 * - If robot wiggles too much: Reduce turn duration or speed
 * - If robot loses line on curves: Increase turn amount
 * - If robot goes too slow: Increase FOLLOW_SPEED
 * - If robot overshoots: Decrease speeds
 * 
 * BONUS CHALLENGES:
 * 1. Speed variation:
 *    - Fast on straight sections
 *    - Slow on curves
 *    - Detect straight vs curve by: if making corrections = curve
 * 
 * 2. Add an intersection:
 *    - When all 3 sensors see line, it's an intersection
 *    - Decide: go straight, turn left, or turn right
 *    - Print "INTERSECTION DETECTED!"
 * 
 * 3. Lap counter:
 *    - Make the track a closed loop
 *    - Count how many times robot completes the loop
 *    - Use intersection as lap marker
 * 
 * 4. LED indicators:
 *    - Green LED when centered
 *    - Red LED when correcting left
 *    - Blue LED when correcting right
 * 
 * ADVANCED CHALLENGE:
 * Implement PID-style control for ultra-smooth following:
 * 
 * Calculate "error" (how far from center):
 * - If left sensor triggers: error = -1
 * - If center triggers: error = 0
 * - If right sensor triggers: error = +1
 * 
 * Make correction proportional to error:
 * - Small error = small correction
 * - Large error = large correction
 * 
 * This creates very smooth following!
 * 
 * EXPERT CHALLENGE:
 * Create a "line maze solver":
 * - At each intersection, try right first
 * - If right leads to dead end, try straight
 * - If straight leads to dead end, try left
 * - Remember which paths were tried
 * - Find the path through the maze!
 * 
 * Advanced track features to try:
 * - Sharp 90-degree turns
 * - S-curves
 * - Multiple intersections
 * - Gaps in the line (robot must continue straight)
 * - Different line widths
 */
