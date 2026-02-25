# Arduino Robot Car - Complete Lesson Guide
## For Teachers and Students
### From First Line of Code to Autonomous Robot Design

---

# Table of Contents

1. Introduction to the Robot Platform
2. Lesson Objectives Overview
3. Complete Command Reference (Beginner Friendly)
4. Detailed Lesson Plans (Lessons 1-16)
5. Assessment Guidelines
6. Troubleshooting Guide

---

# 1. Introduction to the Robot Platform

## What is the Robot Car?

This robot car is a programmable vehicle that can:
- Move forward, backward, and turn
- Sense obstacles using ultrasonic "sound vision"
- See black lines on the ground
- Grab and move objects with a claw
- Make decisions on its own!

## How Does It Work?

The robot has a "brain" (Arduino microcontroller) that runs your code and controls:
- **2 Motors** - Make the wheels spin (forward, backward, or opposite for turning)
- **Ultrasonic Sensor** - Measures distance to objects (like bat echolocation)
- **Line Sensors** - Detect black vs white surfaces
- **2 Servo Motors** - Move the sensor (like turning your head) and control the claw (like your hand)
- **RGB LED** - Changes colors for feedback
- **Buzzer** (optional) - Makes sounds

---

# 2. Lesson Objectives Overview

## Module 1: Linear Motion (Lessons 1-3)
**Goal:** Master basic forward and backward movement

### Lesson 1: First Steps - Moving Forward
- **Objectives:**
  * Set up the Arduino environment
  * Learn the basic code structure (setup and loop)
  * Make the robot move forward
  * Control speed and duration
- **Skills:** Basic programming, sequential thinking
- **Time:** 45 minutes

### Lesson 2: Going Backward
- **Objectives:**
  * Make the robot move backward
  * Combine forward and backward movements
  * Create movement sequences
- **Skills:** Sequencing, timing
- **Time:** 30 minutes

### Lesson 3: Linear Motion Challenge
- **Objectives:**
  * Plan multi-step movement sequences
  * Navigate to specific positions
  * Precision in programming
- **Skills:** Planning, problem-solving, precision
- **Time:** 60 minutes

## Module 2: Rotational Motion (Lessons 4-6)
**Goal:** Master turning and rotation

### Lesson 4: Turning Left and Right
- **Objectives:**
  * Understand how turning works (motors spinning opposite directions)
  * Make the robot turn left and right
  * Combine turning with forward movement
- **Skills:** Spatial reasoning, geometry concepts
- **Time:** 45 minutes

### Lesson 5: Advanced Rotation
- **Objectives:**
  * Make precise angle turns
  * Create complex shapes (hexagon, octagon)
  * Understand angle mathematics
- **Skills:** Geometry, pattern recognition, mathematical thinking
- **Time:** 60 minutes

### Lesson 6: Rotation Challenge
- **Objectives:**
  * Navigate waypoints using turns
  * Plan complex movement paths
  * Solve navigation problems
- **Skills:** Path planning, strategic thinking
- **Time:** 60 minutes

## Module 3: Ultrasonic Sensing (Lessons 7-8)
**Goal:** Use sensors to detect and respond to environment

### Lesson 7: Seeing with Sound
- **Objectives:**
  * Understand ultrasonic sensor operation
  * Measure distances
  * Make decisions based on sensor data
- **Skills:** Conditional logic (if-else), sensor integration
- **Time:** 45 minutes

### Lesson 8: Looking Around - Sensor Servo
- **Objectives:**
  * Control servo motors
  * Scan environment in multiple directions
  * Find optimal paths
- **Skills:** Scanning algorithms, decision making
- **Time:** 45 minutes

## Module 4: Servo Control (Lessons 9-10)
**Goal:** Control servos and combine sensors with movement

### Lesson 9: The Robot Claw
- **Objectives:**
  * Control the claw servo
  * Pick up and move objects
  * Coordinate movement with manipulation
- **Skills:** Task sequencing, coordination
- **Time:** 45 minutes

### Lesson 10: Obstacle Detection and Avoidance
- **Objectives:**
  * Combine sensors and movement
  * Create autonomous avoidance behavior
  * Implement sense-think-act cycles
- **Skills:** Autonomous behavior, decision trees
- **Time:** 60 minutes

## Module 5: Obstacle Courses (Lessons 11-12)
**Goal:** Navigate complex environments

### Lesson 11: Simple Obstacle Course
- **Objectives:**
  * Navigate through obstacles autonomously
  * Implement reliable navigation algorithms
  * Handle multiple obstacles
- **Skills:** Algorithm development, testing, refinement
- **Time:** 90 minutes

### Lesson 12: Advanced Obstacle Course
- **Objectives:**
  * Navigate tight spaces
  * Implement stuck detection and recovery
  * Optimize navigation strategies
- **Skills:** Advanced algorithms, debugging, optimization
- **Time:** 90 minutes

## Module 6: Line Following (Lessons 13-14)
**Goal:** Follow lines autonomously

### Lesson 13: Line Sensor Basics
- **Objectives:**
  * Understand IR line sensors
  * Read and interpret sensor values
  * Calibrate sensors for environment
- **Skills:** Sensor calibration, data interpretation
- **Time:** 45 minutes

### Lesson 14: Line Following
- **Objectives:**
  * Implement line-following algorithm
  * Handle curves and intersections
  * Create smooth following behavior
- **Skills:** Control algorithms, parameter tuning
- **Time:** 90 minutes

## Module 7: Autonomous Design (Lessons 15-16)
**Goal:** Create complete autonomous systems

### Lesson 15: Autonomous Design - Part 1
- **Objectives:**
  * Combine all skills into autonomous behaviors
  * Implement state machines
  * Create multi-mode robots
- **Skills:** System design, integration, state machines
- **Time:** 120 minutes

### Lesson 16: Autonomous Design - Part 2 (Final Project)
- **Objectives:**
  * Design complete autonomous missions
  * Implement error handling
  * Create sophisticated robot behaviors
- **Skills:** Project design, testing, presentation
- **Time:** 120-180 minutes (may span multiple sessions)

---

# 3. Complete Command Reference
## For Students Who Have Never Coded Before

### Understanding the Basics

**What is a command?**
A command is an instruction you give to the robot. Like telling a friend "walk forward 5 steps", you tell the robot "moveForward(speed, time)".

**What are those numbers in parentheses?**
Those are called "parameters" - they give details about HOW to do the command:
- Speed: How fast (0 = stopped, 255 = maximum)
- Duration: How long in milliseconds (1000 = 1 second)

### Movement Commands

#### moveForward(speed, duration)
**What it does:** Makes the robot drive forward

**How it works:** Both motors spin forward at the same speed, making the wheels roll ahead

**Parameters:**
- `speed`: How fast to go (0-255). Think of it like a gas pedal:
  * 0 = stopped
  * 100 = slow/gentle
  * 180 = medium/normal
  * 255 = maximum speed
- `duration`: How long to move in milliseconds:
  * 1000 = 1 second
  * 2000 = 2 seconds
  * 500 = half a second

**Example:**
```cpp
car.moveForward(150, 2000);  // Move forward at medium speed for 2 seconds
```

**When to use it:**
- Going straight
- Approaching an object
- Following a path

---

#### moveBackward(speed, duration)
**What it does:** Makes the robot drive backward (in reverse)

**How it works:** Both motors spin backward, like a car in reverse gear

**Parameters:** Same as moveForward

**Example:**
```cpp
car.moveBackward(120, 1000);  // Back up slowly for 1 second
```

**When to use it:**
- Backing away from obstacles
- Returning to a previous position
- Parking maneuvers

---

#### turnLeft(speed, duration)
**What it does:** Makes the robot spin/turn to the left (counterclockwise)

**How it works:** 
- Right motor spins FORWARD
- Left motor spins BACKWARD
- This makes the robot spin in place to the left

**Parameters:**
- `speed`: How fast to turn (0-255)
- `duration`: How long to turn (longer = bigger turn angle)
  * ~250ms = 45 degrees (small turn)
  * ~500ms = 90 degrees (quarter turn)
  * ~1000ms = 180 degrees (turn around)

**Example:**
```cpp
car.turnLeft(150, 500);  // Turn left 90 degrees at medium speed
```

**When to use it:**
- Changing direction
- Avoiding obstacles on the right
- Making shapes (squares, hexagons, etc.)

---

#### turnRight(speed, duration)
**What it does:** Makes the robot spin/turn to the right (clockwise)

**How it works:**
- Left motor spins FORWARD
- Right motor spins BACKWARD
- This makes the robot spin in place to the right

**Parameters:** Same as turnLeft

**Example:**
```cpp
car.turnRight(150, 500);  // Turn right 90 degrees
```

---

#### turnAround()
**What it does:** Makes the robot turn 180 degrees (half circle)

**How it works:** Automatically turns left for the right amount of time to spin halfway around

**Parameters:** None (it's automatic!)

**Example:**
```cpp
car.turnAround();  // Turn to face the opposite direction
```

**When to use it:**
- Going back the way you came
- Escaping dead ends
- Changing direction completely

---

#### stopMotors()
**What it does:** Stops all robot movement immediately

**How it works:** Cuts power to both motors

**Parameters:** None

**Example:**
```cpp
car.stopMotors();  // Stop right now!
```

**When to use it:**
- End of a movement sequence
- When obstacle detected
- Emergency stop
- Before changing direction

---

### Sensor Commands

#### getDistanceToObstacle()
**What it does:** Measures how far away the nearest object is in front of the robot

**How it works:** 
1. Sends out an ultrasonic sound (too high pitched for humans to hear)
2. Listens for the echo bouncing back
3. Calculates distance based on how long the echo took
4. Returns distance in centimeters

**Parameters:** None

**Returns:** A number representing distance in centimeters
- 10 = object is 10cm away (very close!)
- 50 = object is 50cm away (medium distance)
- 100+ = object is far away or not detected

**Example:**
```cpp
int distance = car.getDistanceToObstacle();  // Measure distance
Serial.print("Distance: ");
Serial.print(distance);
Serial.println(" cm");

if(distance < 20) {
  Serial.println("Too close! Stopping!");
  car.stopMotors();
}
```

**When to use it:**
- Before moving forward
- To avoid hitting walls
- To find objects
- To stop at the right distance

---

#### getCenterDistance()
**What it does:** Points sensor straight ahead and measures distance

**How it works:** Moves servo to center position (90°), waits for it to stabilize, then measures distance

**Example:**
```cpp
int ahead = car.getCenterDistance();  // Look straight and measure
```

---

#### getLeftDistance()
**What it does:** Points sensor to the left and measures distance

**How it works:** Moves servo to left position (0°), waits, then measures

**Example:**
```cpp
int leftDist = car.getLeftDistance();  // Look left and measure
```

---

#### getRightDistance()
**What it does:** Points sensor to the right and measures distance

**How it works:** Moves servo to right position (180°), waits, then measures

**Example:**
```cpp
int rightDist = car.getRightDistance();  // Look right and measure
```

**When to use all three:**
```cpp
// Scan to find the clearest path
int left = car.getLeftDistance();
int center = car.getCenterDistance();
int right = car.getRightDistance();

if(center > left && center > right) {
  Serial.println("Go straight!");
} else if(left > right) {
  Serial.println("Turn left!");  
} else {
  Serial.println("Turn right!");
}
```

---

### Servo Commands

#### attachSensorServo(pin)
**What it does:** Connects the sensor servo motor to the Arduino

**How it works:** Sets up communication between Arduino and the servo

**Parameters:**
- `pin`: Which Arduino pin the servo is connected to (usually 10)

**Example:**
```cpp
void setup() {
  car.attachSensorServo(10);  // Connect servo on pin 10
}
```

**When to use it:** ONCE in setup() before using any servo commands

---

#### lookLeft()
**What it does:** Turns the ultrasonic sensor to look to the left

**How it works:** Rotates servo to 0 degrees (left position)

**Example:**
```cpp
car.lookLeft();  // Turn sensor left
delay(500);       // Wait for servo to move
// Now you can measure distance to the left
```

---

#### lookRight()
**What it does:** Turns the ultrasonic sensor to look to the right

**How it works:** Rotates servo to 180 degrees (right position)

**Example:**
```cpp
car.lookRight();  // Turn sensor right
delay(500);        // Wait for servo to move
```

---

#### centerServo()
**What it does:** Points the ultrasonic sensor straight ahead

**How it works:** Rotates servo to 90 degrees (center position)

**Example:**
```cpp
car.centerServo();  // Point sensor forward
```

**Important:** Always center the servo when done scanning! This ensures the sensor points forward when the robot moves.

---

#### attachClaw(pin)
**What it does:** Connects the claw servo motor to the Arduino

**Parameters:**
- `pin`: Which Arduino pin the claw is connected to (usually 11)

**Example:**
```cpp
void setup() {
  car.attachClaw(11);  // Connect claw on pin 11
}
```

---

#### openClaw()
**What it does:** Opens the claw to release or prepare to grab

**How it works:** Moves claw servo to 0 degrees (open position)

**Example:**
```cpp
car.openClaw();   // Open the claw
delay(1000);      // Wait for it to open
```

---

#### closeClaw()
**What it does:** Closes the claw to grab an object

**How it works:** Moves claw servo to 180 degrees (closed position)

**Example:**
```cpp
car.closeClaw();  // Close the claw
delay(1000);      // Wait for it to close
```

**Complete grab sequence:**
```cpp
car.openClaw();              // 1. Open claw
delay(1000);
car.moveForward(100, 800);   // 2. Approach object
delay(500);
car.closeClaw();             // 3. Grab object
delay(1500);
car.moveBackward(100, 500);  // 4. Back away with object
```

---

### Line Sensor Commands

#### initLineSensors()
**What it does:** Sets up the line sensors for use

**How it works:** Configures the Arduino pins for the three line sensors

**Example:**
```cpp
void setup() {
  car.initLineSensors();  // Initialize line sensors
}
```

**When to use it:** ONCE in setup() before reading line sensors

---

#### getLineSensorLeft()
**What it does:** Reads the left line sensor value

**How it works:** Measures how much light reflects back from the surface

**Returns:** A number from 0 to 1023
- LOW (0-300): On a BLACK line (dark, absorbs light)
- HIGH (700-1023): On WHITE surface (bright, reflects light)
- MEDIUM (300-700): Edge of line or gray surface

**Example:**
```cpp
int leftValue = car.getLineSensorLeft();
Serial.print("Left sensor: ");
Serial.println(leftValue);

if(leftValue < 500) {
  Serial.println("On black line!");
} else {
  Serial.println("On white surface");
}
```

---

#### getLineSensorMiddle()
**What it does:** Reads the middle line sensor value

**Returns:** Same as getLineSensorLeft (0-1023)

---

#### getLineSensorRight()
**What it does:** Reads the right line sensor value

**Returns:** Same as getLineSensorLeft (0-1023)

---

#### followLine(threshold)
**What it does:** Makes the robot follow a black line automatically

**How it works:**
- If center sensor sees line → go straight
- If left sensor sees line → turn left
- If right sensor sees line → turn right

**Parameters:**
- `threshold`: Value to distinguish black from white (usually 500)
  * Values BELOW threshold = on the line (black)
  * Values ABOVE threshold = off the line (white)

**Example:**
```cpp
car.followLine(500);  // Follow line using threshold of 500
```

**When to use it:** In a loop to continuously follow a line

```cpp
void loop() {
  car.followLine(500);
  delay(50);  // Small delay for stability
}
```

---

### Other Useful Commands

#### delay(milliseconds)
**What it does:** Makes the robot wait/pause

**How it works:** Stops executing code for the specified time

**Parameters:**
- `milliseconds`: How long to wait
  * 1000 = 1 second
  * 500 = 0.5 seconds
  * 100 = 0.1 seconds

**Example:**
```cpp
car.moveForward(100, 1000);  // Move forward
delay(2000);                  // Wait 2 seconds
car.moveBackward(100, 1000);  // Move backward
```

**When to use it:**
- Between movements
- After servo commands (let servo reach position)
- To create timing/rhythm
- To pause and observe

---

#### Serial.println()
**What it does:** Prints messages to the computer screen

**How it works:** Sends text through the USB cable to show in Arduino Serial Monitor

**Example:**
```cpp
Serial.println("Robot is starting!");
Serial.println("Moving forward...");
Serial.print("Distance: ");
Serial.println(distance);
```

**When to use it:**
- Debugging (seeing what robot is thinking)
- Status messages
- Showing sensor values
- Understanding what code is doing

---

### Setup Structure

Every Arduino program has two main parts:

#### setup()
**Runs ONCE when robot starts**

Put initialization here:
```cpp
void setup() {
  Serial.begin(9600);           // Start serial communication
  car.setup();                  // Initialize robot
  car.attachSensorServo(10);    // Connect servos
  car.attachClaw(11);
  car.initLineSensors();        // Initialize sensors
  
  Serial.println("Ready!");
}
```

#### loop()
**Runs OVER and OVER forever**

Put your robot behavior here:
```cpp
void loop() {
  // This code runs repeatedly
  car.moveForward(150, 1000);
  delay(500);
  car.turnRight(150, 500);
  delay(500);
  // When this ends, it starts over from the top
}
```

---

# 4. Teaching Tips and Strategies

## Scaffolding Student Learning

### For Complete Beginners:
1. **Start with modification, not creation**
   - Provide working code
   - Ask students to change ONE parameter
   - Example: "Change the speed from 150 to 200 and see what happens"

2. **Use physical analogies**
   - delay() is like counting "1 Mississippi, 2 Mississippi"
   - Speed is like a gas pedal
   - Sensors are like your eyes and ears

3. **Make it concrete**
   - Print everything: Serial.println("Doing this now!")
   - Use real measurements: "Move forward 30cm" not "for 1000ms"
   - Physical markers: tape on floor, objects to navigate

### Debugging Strategies for Students:

**Teach the "Is it...?" checklist:**
1. Is it uploaded? (Did you click upload?)
2. Is it powered? (Batteries charged?)
3. Is it in setup or loop? (Setup runs once, loop repeats)
4. Did you wait? (delay after servo commands?)
5. What do sensors say? (Print the values!)

**Common Issues:**
- **Robot doesn't move:** Check batteries, check car.setup() is called
- **Servo doesn't work:** Did you attach it? Did you wait (delay)?
- **Values seem wrong:** Calibrate! Different environments need different thresholds
- **Code uploads but nothing happens:** Is the code in loop() or setup()?

---

# 5. Assessment Rubric

## For Each Lesson

### Basic Completion (Meets Expectations)
- [ ] Robot performs the required task
- [ ] Code is uploaded and runs
- [ ] Student can explain what the code does
- [ ] Includes appropriate Serial.println() messages

### Challenge Completion (Exceeds Expectations)
- [ ] Completed the bonus challenge
- [ ] Added unique features
- [ ] Code is well-commented
- [ ] Demonstrates understanding through modifications

### Mastery Indicators
- [ ] Helps other students debug
- [ ] Extends the challenge creatively
- [ ] Explains WHY code works, not just WHAT it does
- [ ] Can troubleshoot independently

---

# 6. Hardware Setup Guide

## Required Components:
- Arduino-compatible robot car chassis
- TB6612FNG motor driver
- 2x DC motors
- Ultrasonic sensor (HC-SR04)
- 3x IR line sensors
- 2x Servo motors (for sensor pan and claw)
- Robot claw gripper
- RGB LED (WS2812/NeoPixel)
- Buzzer (optional)
- Battery pack (7.4V recommended)

## Pin Connections:
```
Motors:
  PWMA: Pin 5
  PWMB: Pin 6
  AIN: Pin 7
  BIN: Pin 8
  STBY: Pin 3

Ultrasonic Sensor:
  TRIG: Pin 13
  ECHO: Pin 12

Servos:
  Sensor Servo: Pin 10
  Claw Servo: Pin 11

Line Sensors:
  Left: Pin A2
  Middle: Pin A1
  Right: Pin A0

Other:
  RGB LED: Pin 4
  Buzzer: Pin 11 (optional)
  Battery Monitor: Pin A3
```

---

# 7. Lesson Materials Checklist

## For Each Lesson Session:

### Lesson 1-6 (Motion):
- [ ] Open floor space (2m x 2m minimum)
- [ ] Measuring tape
- [ ] Tape markers for waypoints
- [ ] Charged batteries (spares!)

### Lesson 7-12 (Sensors & Obstacles):
- [ ] Cardboard boxes (various sizes)
- [ ] Books or blocks
- [ ] Measuring tape
- [ ] Tape for marking safe zones

### Lesson 13-14 (Line Following):
- [ ] White poster board or floor space
- [ ] Black electrical tape (1.5-2cm wide)
- [ ] Pre-made tracks (straight, curved, intersection)
- [ ] Bright overhead lighting

### Lesson 15-16 (Autonomous):
- [ ] Obstacle course setup
- [ ] Line tracks
- [ ] Small objects for grabbing (foam blocks, ping pong balls)
- [ ] Goal markers
- [ ] Timer

---

# 8. Extension Projects

After completing all lessons, students can tackle these advanced projects:

1. **Sumo Robot**
   - Two robots compete to push each other out of a ring
   - Uses line sensors for ring boundary
   - Uses ultrasonic to find opponent

2. **Maze Solver**
   - Navigate unknown maze
   - Find the goal (marked with line)
   - Remember and return via shortest path

3. **Line Following Race**
   - Follow complex track as fast as possible
   - Optimize for speed vs stability
   - Handle intersections with decision logic

4. **Warehouse Robot**
   - Multiple pick-up points
   - Deliver to correct drop-off zones
   - Use color coding or distance markers

5. **Autonomous Exploration**
   - Map an unknown space
   - Avoid obstacles
   - Return to home base
   - Report findings

---

# 9. Standards Alignment

These lessons align with:

**Next Generation Science Standards (NGSS):**
- MS-ETS1-1: Define criteria and constraints for design
- MS-ETS1-2: Evaluate competing design solutions
- MS-ETS1-3: Analyze data from tests
- MS-ETS1-4: Develop models to test solutions

**CSTA Computer Science Standards:**
- 2-AP-13: Decompose problems into sub-problems
- 2-AP-16: Incorporate existing code into programs
- 2-AP-17: Systematically test and refine programs
- 3A-AP-13: Create prototypes using algorithms
- 3A-AP-16: Design and iteratively develop programs
- 3A-AP-18: Explain security measures

**Common Core Math:**
- CCSS.Math.Practice.MP1: Make sense of problems
- CCSS.Math.Practice.MP2: Reason abstractly
- CCSS.Math.Practice.MP5: Use appropriate tools

---

# 10. Vocabulary List

**Algorithm:** Step-by-step instructions to solve a problem
**Autonomous:** Operating independently without human control
**Calibration:** Adjusting sensors for accurate readings
**Conditional:** Code that runs only if a condition is true (if/else)
**Debug:** Finding and fixing errors in code
**Duration:** How long something lasts (in milliseconds)
**Function:** Reusable block of code that does one task
**Loop:** Code that repeats over and over
**Parameter:** Information passed to a function (inside parentheses)
**Sensor:** Device that detects physical properties (distance, light, etc.)
**Servo:** Motor that rotates to specific angles
**State Machine:** System with different modes/states
**Threshold:** Value that triggers a decision (above/below)
**Variable:** Container that stores a value that can change

---

**Created:** February 2026
**For:** WWHS Research - Arduino Robotics Program
**By:** GitHub Copilot Educational Assistant

**License:** This material is provided for educational use. Please credit the source when sharing or adapting.

---

*End of Comprehensive Lesson Guide*
*Total Lesson Time: Approximately 20-24 hours of instruction*
*Suitable for: Middle School through High School*
*Prerequisites: None - designed for complete beginners*
