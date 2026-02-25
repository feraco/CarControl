/*
 * LESSON 01: First Steps - Moving Forward
 * 
 * LESSON OBJECTIVES:
 * - Learn how to include the CarControl library
 * - Understand how to create a robot object
 * - Make the robot move forward
 * - Learn to stop the robot
 * 
 * NEW COMMANDS:
 * - moveForward(speed, duration) - Makes the robot move forward
 *   - speed: How fast to move (0-255, where 255 is fastest)
 *   - duration: How long to move in milliseconds (1000 = 1 second)
 * 
 * - stopMotors() - Stops all robot movement
 * 
 * HOW IT WORKS:
 * Think of the robot like a toy car. The moveForward command is like
 * pressing the forward button on a remote control. The speed is how
 * hard you press (gentle or full power), and duration is how long
 * you hold the button down.
 * 
 * The robot has two motors (one for each side). When both motors
 * spin forward at the same speed, the robot moves straight ahead.
 */

// Include the CarControl library - this gives us all the robot commands
#include <CarControl.h>

// Create a robot object called "car"
// The numbers (5, 6, 7, 8, 3, 2) tell the Arduino which pins control the motors
CarControl car(5, 6, 7, 8, 3, 2);

// The setup function runs once when you press reset or power up the robot
void setup() {
  // Start serial communication so we can see messages on the computer
  Serial.begin(9600);
  Serial.println("Lesson 01: Forward Movement");
  Serial.println("---------------------------");
  
  // Initialize the robot - this must be done before any movement
  car.setup();
}

// The loop function runs over and over again forever
void loop() {
  // Example 1: Move forward slowly for 1 second
  Serial.println("Example 1: Slow forward movement");
  car.moveForward(100, 1000);  // speed=100 (slow), duration=1000ms (1 second)
  delay(2000);  // Wait 2 seconds before next movement
  
  // Example 2: Move forward at medium speed for 2 seconds
  Serial.println("Example 2: Medium speed forward");
  car.moveForward(180, 2000);  // speed=180 (medium), duration=2000ms (2 seconds)
  delay(2000);  // Wait 2 seconds
  
  // Example 3: Move forward at maximum speed for 1.5 seconds
  Serial.println("Example 3: Maximum speed forward");
  car.moveForward(255, 1500);  // speed=255 (maximum), duration=1500ms (1.5 seconds)
  delay(2000);  // Wait 2 seconds
  
  // Stop the motors (good practice to make sure robot is stopped)
  Serial.println("Stopping motors");
  car.stopMotors();
  
  // Wait 5 seconds before repeating the entire sequence
  Serial.println("Waiting 5 seconds before repeating...\n");
  delay(5000);
}

/*
 * CHALLENGE:
 * Modify this code to make your robot move forward THREE different distances:
 * 1. Short distance (about 0.5 seconds)
 * 2. Medium distance (about 1.5 seconds)  
 * 3. Long distance (about 3 seconds)
 * 
 * Change the speed for each movement to make them different!
 * Add Serial.println() messages to describe what your robot is doing.
 * 
 * BONUS: Can you make the robot spell out the letter "I" by moving
 * forward, stopping, then forward again?
 */
