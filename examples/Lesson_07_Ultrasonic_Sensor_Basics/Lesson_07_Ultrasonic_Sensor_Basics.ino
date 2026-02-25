/*
 * LESSON 07: Seeing with Sound - Ultrasonic Sensor Basics
 * 
 * LESSON OBJECTIVES:
 * - Understand how ultrasonic sensors work
 * - Learn to measure distance to objects
 * - Use sensor data to make decisions
 * - Create obstacle detection programs
 * 
 * NEW COMMANDS:
 * - getDistanceToObstacle() - Returns distance to nearest object in centimeters
 *   - Returns: A number representing distance in cm (e.g., 25 means 25cm away)
 * 
 * - checkObstacleInFront() - Updates obstacle detection status
 *   - This checks if something is within 10cm
 * 
 * HOW IT WORKS:
 * An ultrasonic sensor works like a bat using echolocation!
 * 
 * 1. The sensor sends out a sound wave (too high for humans to hear)
 * 2. The sound bounces off objects and returns
 * 3. The sensor measures how long it took to return
 * 4. Using the speed of sound, it calculates the distance
 * 
 * Think of it like shouting in a canyon - the echo tells you how
 * far away the wall is. Closer walls = faster echo. Far walls = slower echo.
 * 
 * The sensor is on the FRONT of your robot, so it measures what's ahead.
 * 
 * Distance values:
 * - 0-5 cm: Very close! About to hit!
 * - 5-20 cm: Close, need to be careful
 * - 20-50 cm: Moderate distance
 * - 50+ cm: Far away or nothing detected
 */

#include <CarControl.h>

CarControl car(5, 6, 7, 8, 3, 2);

void setup() {
  Serial.begin(9600);
  Serial.println("Lesson 07: Ultrasonic Sensor Basics");
  Serial.println("-----------------------------------");
  
  car.setup();
  car.attachSensorServo(10);  // Attach the sensor servo
  car.centerServo();           // Make sure sensor faces forward
  
  Serial.println("\nHold objects in front of the sensor!");
  Serial.println("Watch the distance change...\n");
}

void loop() {
  // Example 1: Simple distance reading
  Serial.println("Example 1: Reading distance");
  int distance = car.getDistanceToObstacle();
  Serial.print("Distance to object: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(1000);
  
  // Example 2: Describing the distance
  distance = car.getDistanceToObstacle();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm - ");
  
  if(distance < 10) {
    Serial.println("VERY CLOSE!");
  } else if(distance < 30) {
    Serial.println("Close");
  } else if(distance < 60) {
    Serial.println("Medium distance");
  } else {
    Serial.println("Far away or nothing detected");
  }
  delay(1000);
  
  // Example 3: Stopping before hitting a wall
  Serial.println("\nExample 3: Stop before hitting wall");
  Serial.println("Moving forward slowly...");
  
  distance = car.getDistanceToObstacle();
  while(distance > 15) {  // Keep going while distance > 15cm
    car.moveForward(120, 100);  // Move in small increments
    distance = car.getDistanceToObstacle();
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(100);
  }
  
  Serial.println("STOP! Object detected!");
  car.stopMotors();
  delay(3000);
  
  // Example 4: Move backward if too close
  Serial.println("\nExample 4: Backing up if too close");
  distance = car.getDistanceToObstacle();
  Serial.print("Current distance: ");
  Serial.println(distance);
  
  if(distance < 20) {
    Serial.println("Too close! Backing up...");
    car.moveBackward(150, 1000);
    delay(500);
    distance = car.getDistanceToObstacle();
    Serial.print("New distance: ");
    Serial.println(distance);
  } else {
    Serial.println("Distance is safe.");
  }
  delay(2000);
  
  // Example 5: Continuous monitoring
  Serial.println("\nExample 5: Continuous distance monitoring");
  for(int i = 0; i < 10; i++) {
    distance = car.getDistanceToObstacle();
    
    // Create a simple "bar graph" with asterisks
    Serial.print(distance);
    Serial.print(" cm |");
    for(int j = 0; j < distance && j < 50; j++) {
      Serial.print("*");
    }
    Serial.println();
    delay(500);
  }
  
  Serial.println("\nSequence complete! Waiting 5 seconds...\n");
  delay(5000);
}

/*
 * CHALLENGE: Smart Wall Stopper
 * 
 * Create a program that:
 * 1. Moves the robot forward at medium speed
 * 2. Constantly checks the distance ahead
 * 3. When an object is detected at 20cm or less, STOP
 * 4. Print "Object detected at X cm - STOPPING!"
 * 5. Wait 2 seconds
 * 6. Back up until the object is 40cm away
 * 7. Print "Safe distance reached"
 * 8. Stop and wait 5 seconds
 * 9. Repeat
 * 
 * Requirements:
 * - Use a while loop to keep checking distance while moving
 * - Print the distance every 0.5 seconds
 * - Stop immediately when object is within 20cm
 * - Use backward movement to reach 40cm distance
 * 
 * BONUS CHALLENGES:
 * 1. Make the robot slow down when it's within 30cm
 *    (fast when far, slow when close)
 * 2. Create a "parking assist" that beeps faster as you get closer
 *    (if you have a buzzer - use delay between beeps)
 * 3. Print a warning at 50cm, 30cm, and 20cm
 * 
 * ADVANCED CHALLENGE:
 * Create a "Distance Keeper" that maintains exactly 25cm from a wall:
 * - If distance > 27cm, move forward a little
 * - If distance < 23cm, move backward a little
 * - If distance is 23-27cm, stay still
 * - Run for 30 seconds, constantly adjusting
 * 
 * EXPERT CHALLENGE:
 * Create a function that approaches an object slowly and stops
 * exactly 10cm away:
 * 
 * void approachObject(int targetDistance) {
 *   // Your code here
 *   // Hint: Move forward in small steps, checking distance each time
 *   // Slow down as you get closer!
 * }
 */
