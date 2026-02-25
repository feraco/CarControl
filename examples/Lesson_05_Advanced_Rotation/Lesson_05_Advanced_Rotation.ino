/*
 * LESSON 05: Advanced Rotation
 * 
 * LESSON OBJECTIVES:
 * - Master precise turning angles
 * - Learn the turnAround() command
 * - Create complex navigation patterns
 * - Understand the relationship between duration and angle
 * 
 * NEW COMMANDS:
 * - turnAround() - Makes the robot turn 180 degrees
 * 
 * COMMANDS REVIEW:
 * - turnLeft(speed, duration)
 * - turnRight(speed, duration)
 * 
 * HOW IT WORKS:
 * The turnAround() function is a special command that makes your
 * robot do a 180-degree turn (half circle). This is useful when
 * you want to face the opposite direction.
 * 
 * Different turn durations create different angles:
 * - Short duration (250ms) ≈ 45 degrees (1/8 circle)
 * - Medium duration (500ms) ≈ 90 degrees (1/4 circle)
 * - Long duration (1000ms) ≈ 180 degrees (1/2 circle)
 * - Very long (2000ms) ≈ 360 degrees (full circle)
 * 
 * Note: These are approximate! Each robot is slightly different.
 * You need to experiment to find exact values for YOUR robot.
 */

#include <CarControl.h>

CarControl car(5, 6, 7, 8, 3, 2);

void setup() {
  Serial.begin(9600);
  Serial.println("Lesson 05: Advanced Rotation");
  Serial.println("----------------------------");
  
  car.setup();
}

void loop() {
  // Example 1: Using turnAround()
  Serial.println("Example 1: Turn around (180 degrees)");
  car.moveForward(180, 1000);  // Move forward
  delay(500);
  car.turnAround();            // Turn 180 degrees
  delay(500);
  car.moveForward(180, 1000);  // Move back to start
  delay(2000);
  
  // Example 2: Making a hexagon (6 sides)
  Serial.println("Example 2: Hexagon pattern");
  // A hexagon needs 60-degree turns (360÷6 = 60)
  // If 500ms = 90 degrees, then 60 degrees ≈ 333ms
  for(int i = 0; i < 6; i++) {
    Serial.print("  Side ");
    Serial.println(i + 1);
    car.moveForward(150, 800);   // Move forward
    delay(200);
    car.turnRight(150, 333);     // Turn 60 degrees
    delay(200);
  }
  delay(2000);
  
  // Example 3: The Star Pattern
  Serial.println("Example 3: Star pattern (5 points)");
  // Star needs 144-degree turns (5 points)
  for(int i = 0; i < 5; i++) {
    car.moveForward(180, 1000);
    delay(200);
    car.turnRight(150, 800);  // 144 degrees ≈ 800ms
    delay(200);
  }
  delay(2000);
  
  // Example 4: Precise angle turns
  Serial.println("Example 4: Precise angle demonstration");
  Serial.println("  45-degree turn");
  car.turnRight(150, 250);   // 45 degrees
  delay(1000);
  Serial.println("  90-degree turn");
  car.turnRight(150, 500);   // 90 degrees (now at 135 total)
  delay(1000);
  Serial.println("  Turning back to start");
  car.turnLeft(150, 750);    // 135 degrees back
  delay(2000);
  
  // Example 5: The Octagon (8 sides)
  Serial.println("Example 5: Octagon pattern");
  // Octagon needs 45-degree turns (360÷8 = 45)
  for(int i = 0; i < 8; i++) {
    car.moveForward(150, 600);
    delay(100);
    car.turnRight(150, 250);  // 45 degrees
    delay(100);
  }
  delay(2000);
  
  car.stopMotors();
  Serial.println("\nSequence complete! Waiting 5 seconds...\n");
  delay(5000);
}

/*
 * CHALLENGE: Create an Octagon
 * 
 * An octagon has 8 equal sides and 8 equal angles.
 * Each turn is 45 degrees (360 ÷ 8 = 45).
 * 
 * Your mission:
 * 1. Make your robot drive in a perfect octagon
 * 2. All 8 sides must be equal length
 * 3. All 8 turns must be 45 degrees
 * 4. Robot should end where it started, facing the same direction
 * 
 * Requirements:
 * - Use a for loop to repeat the pattern 8 times
 * - Print which side you're on (1-8)
 * - Add appropriate delays between movements
 * 
 * BONUS CHALLENGES:
 * 1. Create a Pentagon (5 sides, 72-degree turns)
 * 2. Create a function to draw ANY shape:
 *    void drawShape(int numSides) {
 *      // Calculate turn angle
 *      // Use loop to draw the shape
 *    }
 * 3. Make the robot draw an octagon, then turn around,
 *    then draw another octagon going the opposite direction
 * 
 * ADVANCED CHALLENGE:
 * Create a "Flower Pattern":
 * - Draw a small square
 * - Turn 45 degrees
 * - Draw another small square  
 * - Repeat to make 8 squares in a flower pattern
 * 
 * MATH CONNECTION:
 * The turn angle for any regular polygon is: 360 ÷ number of sides
 * - Triangle: 360 ÷ 3 = 120 degrees
 * - Square: 360 ÷ 4 = 90 degrees
 * - Pentagon: 360 ÷ 5 = 72 degrees
 * - Hexagon: 360 ÷ 6 = 60 degrees
 * - Octagon: 360 ÷ 8 = 45 degrees
 */
