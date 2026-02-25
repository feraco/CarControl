/*
 * LESSON 09: The Robot Claw - Servo Control
 * 
 * LESSON OBJECTIVES:
 * - Control the claw servo motor
 * - Learn to open and close the claw
 * - Pick up and move objects
 * - Combine movement with claw operation
 * 
 * NEW COMMANDS:
 * - attachClaw(pin) - Connect the claw servo (call in setup)
 *   - pin: The Arduino pin connected to the claw servo (usually 11)
 * 
 * - openClaw() - Opens the claw to release or prepare to grab
 * 
 * - closeClaw() - Closes the claw to grab an object
 * 
 * HOW IT WORKS:
 * The claw uses a servo motor just like the sensor servo you
 * learned about in Lesson 08. But instead of rotating a sensor,
 * it opens and closes a gripper.
 * 
 * Servo positions:
 * - 0 degrees = Fully OPEN (wide grip)
 * - 180 degrees = Fully CLOSED (tight grip)
 * - Middle positions = Partially open/closed
 * 
 * Think of it like your hand:
 * - Open hand (fingers wide) = openClaw()
 * - Closed hand (fist) = closeClaw()
 * 
 * To pick up an object:
 * 1. Open the claw
 * 2. Position robot next to object
 * 3. Close the claw around the object
 * 4. Lift (if your claw can do that)
 * 5. Move to new location
 * 6. Open claw to release object
 */

#include <CarControl.h>

CarControl car(5, 6, 7, 8, 3, 2);

void setup() {
  Serial.begin(9600);
  Serial.println("Lesson 09: Robot Claw Control");
  Serial.println("-----------------------------");
  
  car.setup();
  car.attachClaw(11);  // Connect claw servo to pin 11
  
  Serial.println("\nWatch the claw open and close!");
  Serial.println("Place a small object in front of the robot.\n");
}

void loop() {
  // Example 1: Basic claw operation
  Serial.println("Example 1: Opening and closing claw");
  
  Serial.println("Opening claw...");
  car.openClaw();
  delay(2000);  // Wait for servo to move
  
  Serial.println("Closing claw...");
  car.closeClaw();
  delay(2000);
  
  Serial.println("Opening again...");
  car.openClaw();
  delay(2000);
  
  // Example 2: Rapid open/close (testing grip)
  Serial.println("\nExample 2: Rapid grip test");
  for(int i = 0; i < 3; i++) {
    Serial.print("Grip test ");
    Serial.println(i + 1);
    car.closeClaw();
    delay(500);
    car.openClaw();
    delay(500);
  }
  delay(1000);
  
  // Example 3: Pick up sequence
  Serial.println("\nExample 3: Object pickup sequence");
  Serial.println("Step 1: Prepare - open claw");
  car.openClaw();
  delay(1000);
  
  Serial.println("Step 2: Approach object");
  car.moveForward(120, 800);
  delay(500);
  
  Serial.println("Step 3: Grab object!");
  car.closeClaw();
  delay(1500);  // Wait for secure grip
  
  Serial.println("Step 4: Lift and move backward");
  car.moveBackward(120, 1000);
  delay(500);
  
  Serial.println("Step 5: Release object");
  car.openClaw();
  delay(2000);
  
  // Example 4: Move object from point A to point B
  Serial.println("\nExample 4: Moving an object");
  
  Serial.println("Getting ready...");
  car.openClaw();
  delay(1000);
  
  Serial.println("Approaching object at point A");
  car.moveForward(120, 1000);
  delay(500);
  
  Serial.println("Grabbing object");
  car.closeClaw();
  delay(1000);
  
  Serial.println("Backing up");
  car.moveBackward(120, 500);
  delay(500);
  
  Serial.println("Turning to point B");
  car.turnRight(150, 500);
  delay(500);
  
  Serial.println("Moving to point B");
  car.moveForward(120, 1500);
  delay(500);
  
  Serial.println("Placing object at point B");
  car.openClaw();
  delay(1000);
  
  Serial.println("Backing away");
  car.moveBackward(120, 500);
  delay(2000);
  
  // Example 5: Claw control with sensor
  Serial.println("\nExample 5: Smart pickup using sensor");
  
  car.attachSensorServo(10);
  car.centerServo();
  car.openClaw();
  delay(1000);
  
  Serial.println("Moving forward until object detected");
  int distance = car.getDistanceToObstacle();
  
  while(distance > 10) {  // Move until 10cm from object
    car.moveForward(100, 100);
    distance = car.getDistanceToObstacle();
    Serial.print("Distance: ");
    Serial.println(distance);
    delay(100);
  }
  
  Serial.println("Object detected! Stopping and grabbing...");
  car.stopMotors();
  delay(500);
  car.closeClaw();
  delay(1500);
  
  Serial.println("Got it! Moving back");
  car.moveBackward(120, 1000);
  delay(1000);
  
  car.openClaw();
  delay(1000);
  
  Serial.println("\nSequence complete! Waiting 5 seconds...\n");
  delay(5000);
}

/*
 * CHALLENGE: The Object Mover
 * 
 * Set up a simple course:
 * - Place a small object at "Point A" (starting area)
 * - Mark "Point B" about 50cm away
 * 
 * Your robot must:
 * 1. Start with claw open
 * 2. Move to Point A
 * 3. Pick up the object (close claw)
 * 4. Turn 90 degrees
 * 5. Move to Point B
 * 6. Place the object (open claw)
 * 7. Back away from the object
 * 8. Print status messages for each step
 * 
 * Requirements:
 * - Use appropriate delays for servo movement
 * - Print clear status messages
 * - Make smooth, controlled movements
 * - End with claw open
 * 
 * BONUS CHALLENGES:
 * 1. Pick up 3 objects from different locations and stack them
 *    in one location (if objects are stackable)
 * 2. Create a "delivery service" that picks up an object,
 *    delivers it, and returns to the starting position
 * 3. Use the ultrasonic sensor to find the object automatically
 *    (move forward until distance < 15cm, then grab)
 * 
 * ADVANCED CHALLENGE:
 * Create a program that:
 * - Scans left and right to find the nearest object
 * - Turns toward that object
 * - Moves to it using sensor feedback
 * - Picks it up
 * - Turns around
 * - Moves backward for 2 seconds
 * - Releases object
 * 
 * EXPERT CHALLENGE:
 * Create a sorting robot that:
 * - Picks up objects one at a time
 * - Moves them to different locations based on some rule
 *   (e.g., alternating left and right sides)
 * - Handles 4 objects
 * - Returns to center when done
 * 
 * Test objects:
 * - Small lightweight items work best
 * - Try: foam blocks, ping pong balls, small toys
 * - Make sure objects fit in your claw!
 */
