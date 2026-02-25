/*
 * LESSON 13: Line Sensor Basics
 * 
 * LESSON OBJECTIVES:
 * - Understand how line sensors work
 * - Read line sensor values
 * - Detect black lines vs white surfaces
 * - Use sensor threshold values
 * 
 * NEW COMMANDS:
 * - initLineSensors() - Initialize the line sensors (call in setup)
 * 
 * - getLineSensorLeft() - Read left line sensor value
 *   - Returns: Analog value (0-1023)
 *   - Higher value = brighter (white)
 *   - Lower value = darker (black)
 * 
 * - getLineSensorMiddle() - Read middle line sensor value
 * 
 * - getLineSensorRight() - Read right line sensor value
 * 
 * HOW IT WORKS:
 * Line sensors use infrared (IR) light to detect dark lines:
 * 
 * 1. Sensor shines IR light at the ground
 * 2. White surfaces REFLECT lots of light back
 * 3. Black lines ABSORB light (little reflection)
 * 4. Sensor measures how much light returns
 * 
 * The robot has THREE line sensors:
 * - LEFT sensor (A2): Detects line on left side
 * - MIDDLE sensor (A1): Detects line in the center
 * - RIGHT sensor (A0): Detects line on right side
 * 
 * Sensor Values:
 * - On WHITE surface: ~800-1020 (bright, lots of reflection)
 * - On BLACK line: ~0-300 (dark, little reflection)
 * - THRESHOLD: ~500 (middle value to distinguish black from white)
 * 
 * Think of it like your eyes:
 * - Looking at white paper = bright (high value)
 * - Looking at black ink = dark (low value)
 * 
 * Note: Exact values depend on lighting and surface.
 * You'll need to calibrate for your environment!
 */

#include <CarControl.h>

CarControl car(5, 6, 7, 8, 3, 2);

// Threshold value - adjust this for your setup!
// Values BELOW this are considered "on the line"
// Values ABOVE this are considered "off the line"
const int LINE_THRESHOLD = 500;

void setup() {
  Serial.begin(9600);
  Serial.println("Lesson 13: Line Sensor Basics");
  Serial.println("-----------------------------");
  
  car.setup();
  car.initLineSensors();  // Initialize the line sensors
  
  Serial.println("\nLine sensors ready!");
  Serial.println("Place robot over different surfaces...\n");
  Serial.println("Values: Left  | Middle | Right");
  Serial.println("-------------------------------");
  delay(2000);
}

void loop() {
  // Example 1: Reading raw sensor values
  Serial.println("\nExample 1: Reading all sensors");
  
  for(int i = 0; i < 10; i++) {
    int leftValue = car.getLineSensorLeft();
    int middleValue = car.getLineSensorMiddle();
    int rightValue = car.getLineSensorRight();
    
    Serial.print("       ");
    Serial.print(leftValue);
    Serial.print("  |  ");
    Serial.print(middleValue);
    Serial.print("  |  ");
    Serial.println(rightValue);
    
    delay(500);
  }
  
  delay(1000);
  
  // Example 2: Detecting line vs no line
  Serial.println("\nExample 2: Line detection (on/off)");
  Serial.println("Move robot over white and black surfaces...\n");
  
  for(int i = 0; i < 10; i++) {
    int leftValue = car.getLineSensorLeft();
    int middleValue = car.getLineSensorMiddle();
    int rightValue = car.getLineSensorRight();
    
    // Check each sensor against threshold
    Serial.print("Left: ");
    if(leftValue < LINE_THRESHOLD) {
      Serial.print("BLACK ");
    } else {
      Serial.print("WHITE ");
    }
    
    Serial.print("| Middle: ");
    if(middleValue < LINE_THRESHOLD) {
      Serial.print("BLACK ");
    } else {
      Serial.print("WHITE ");
    }
    
    Serial.print("| Right: ");
    if(rightValue < LINE_THRESHOLD) {
      Serial.println("BLACK");
    } else {
      Serial.println("WHITE");
    }
    
    delay(500);
  }
  
  delay(1000);
  
  // Example 3: Visualizing sensor readings
  Serial.println("\nExample 3: Sensor visualization");
  Serial.println("(Bar graph - longer = whiter surface)\n");
  
  for(int i = 0; i < 15; i++) {
    int leftValue = car.getLineSensorLeft();
    int middleValue = car.getLineSensorMiddle();
    int rightValue = car.getLineSensorRight();
    
    // Left sensor bar
    Serial.print("L: ");
    for(int j = 0; j < leftValue / 50; j++) {
      Serial.print("█");
    }
    Serial.print(" ");
    Serial.println(leftValue);
    
    // Middle sensor bar
    Serial.print("M: ");
    for(int j = 0; j < middleValue / 50; j++) {
      Serial.print("█");
    }
    Serial.print(" ");
    Serial.println(middleValue);
    
    // Right sensor bar
    Serial.print("R: ");
    for(int j = 0; j < rightValue / 50; j++) {
      Serial.print("█");
    }
    Serial.print(" ");
    Serial.println(rightValue);
    
    Serial.println();
    delay(500);
  }
  
  delay(1000);
  
  // Example 4: Detecting line position
  Serial.println("Example 4: Where is the line?");
  Serial.println("Place a black line under the sensors...\n");
  
  for(int i = 0; i < 15; i++) {
    int leftValue = car.getLineSensorLeft();
    int middleValue = car.getLineSensorMiddle();
    int rightValue = car.getLineSensorRight();
    
    boolean leftOnLine = (leftValue < LINE_THRESHOLD);
    boolean middleOnLine = (middleValue < LINE_THRESHOLD);
    boolean rightOnLine = (rightValue < LINE_THRESHOLD);
    
    Serial.print("Line position: ");
    
    if(middleOnLine && !leftOnLine && !rightOnLine) {
      Serial.println("CENTER ===");
    } else if(leftOnLine && !middleOnLine && !rightOnLine) {
      Serial.println("LEFT <--");
    } else if(rightOnLine && !middleOnLine && !leftOnLine) {
      Serial.println("RIGHT -->");
    } else if(leftOnLine && middleOnLine && !rightOnLine) {
      Serial.println("CENTER-LEFT");
    } else if(rightOnLine && middleOnLine && !leftOnLine) {
      Serial.println("CENTER-RIGHT");
    } else if(leftOnLine && middleOnLine && rightOnLine) {
      Serial.println("ALL (wide line or intersection)");
    } else {
      Serial.println("NONE (off line)");
    }
    
    delay(500);
  }
  
  Serial.println("\nAll examples complete! Waiting 5 seconds...\n");
  delay(5000);
}

/*
 * CHALLENGE: Line Detection Practice
 * 
 * Materials needed:
 * - White paper or poster board (60cm x 100cm)
 * - Black electrical tape (1.5-2cm wide)
 * 
 * Setup:
 * Create a test surface with black tape patterns:
 * 1. A straight line across the middle
 * 2. Lines at different angles
 * 3. A curved line
 * 4. An intersection (perpendicular lines)
 * 
 * Your Mission:
 * Create a program that:
 * 1. Continuously reads all three sensors
 * 2. Prints which sensors detect the black line
 * 3. Describes the line position in words
 * 4. Updates readings 2 times per second
 * 5. Runs for 30 seconds
 * 
 * Requirements:
 * - Clear output format
 * - Accurate line detection
 * - Proper threshold usage
 * - Good timing (not too fast, not too slow)
 * 
 * BONUS CHALLENGES:
 * 1. Calibration function:
 *    Create a function that helps find the right threshold:
 *    - Read sensors on white surface (get max values)
 *    - Read sensors on black line (get min values)
 *    - Calculate threshold as (max + min) / 2
 *    - Print recommended threshold
 * 
 * 2. Edge detection:
 *    Detect when robot moves from white to black or black to white
 *    Print "EDGE DETECTED!" when this happens
 * 
 * 3. Sound effects:
 *    If you have a buzzer, beep when line is detected:
 *    - Different beep patterns for left, center, right
 * 
 * 4. LED indicators:
 *    Use the RGB LED to show line position:
 *    - Red = line on left
 *    - Green = line on center
 *    - Blue = line on right
 * 
 * ADVANCED CHALLENGE:
 * Create a "line width detector":
 * - Measure how many sensors detect the line
 * - Estimate if line is narrow (1 sensor), medium (2 sensors), or wide (3 sensors)
 * - This will help with intersection detection later!
 * 
 * EXPERT CHALLENGE:
 * Implement a data logger:
 * - Collect sensor readings for 60 seconds
 * - Calculate statistics:
 *   * Minimum value seen
 *   * Maximum value seen
 *   * Average value
 *   * Recommended threshold (average of min and max)
 * - Print a summary report
 * 
 * Calibration Tips:
 * - Test in your actual environment (lighting matters!)
 * - Different surfaces may need different thresholds
 * - Higher threshold = more sensitive to lines
 * - Lower threshold = less sensitive
 * - Typical range: 400-600
 */
