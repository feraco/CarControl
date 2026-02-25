# Arduino Robot Car - Complete Lesson Plan
## From Beginner to Autonomous Robot Design

---

## Lesson Structure Overview

Each lesson includes:
1. **Lesson Objectives** - What students will learn
2. **Command Introduction** - The new function(s) being taught
3. **How It Works** - Beginner-friendly explanation
4. **Example Code** - Working demonstration
5. **Challenge** - Student practice activity

---

## Lesson Sequence (16 Lessons)

### Module 1: Linear Motion (Lessons 1-3)

**Lesson 01: First Steps - Moving Forward**
- Objective: Make the robot move forward
- Commands: `moveForward(speed, duration)`, `stopMotors()`
- Challenge: Move forward for 3 different distances

**Lesson 02: Going Backward**
- Objective: Make the robot move backward
- Commands: `moveBackward(speed, duration)`
- Challenge: Create a forward-backward dance

**Lesson 03: Linear Motion Challenge**
- Objective: Combine forward and backward movements
- Commands: All linear motion commands
- Challenge: Navigate a straight path with obstacles

---

### Module 2: Rotational Motion (Lessons 4-6)

**Lesson 04: Turning Left and Right**
- Objective: Make the robot turn
- Commands: `turnLeft(speed, duration)`, `turnRight(speed, duration)`
- Challenge: Make a square pattern

**Lesson 05: Advanced Rotation**
- Objective: Master precise turning
- Commands: `turnAround()`, custom turns
- Challenge: Create an octagon pattern

**Lesson 06: Rotation Challenge**
- Objective: Navigate using only turns and forward movement
- Challenge: Navigate a course with multiple waypoints

---

### Module 3: Ultrasonic Sensor (Lessons 7-8)

**Lesson 07: Seeing with Sound**
- Objective: Understand ultrasonic distance sensing
- Commands: `getDistanceToObstacle()`, `checkObstacleInFront()`
- Challenge: Stop before hitting a wall

**Lesson 08: Looking Around**
- Objective: Use the sensor servo to scan
- Commands: `attachSensorServo()`, `lookLeft()`, `lookRight()`, `centerServo()`
- Challenge: Find the clearest path

---

### Module 4: Servo Control (Lessons 9-10)

**Lesson 09: The Robot Claw**
- Objective: Control the claw servo
- Commands: `attachClaw()`, `openClaw()`, `closeClaw()`
- Challenge: Pick up and move an object

**Lesson 10: Obstacle Detection & Avoidance**
- Objective: Combine sensors and movement
- Commands: Multiple sensor readings with movement
- Challenge: Navigate around obstacles

---

### Module 5: Obstacle Courses (Lessons 11-13)

**Lesson 11: Simple Obstacle Course**
- Objective: Navigate using distance sensing
- Challenge: Complete course without touching walls

**Lesson 12: Advanced Obstacle Course**
- Objective: Use scanning and decision making
- Challenge: Navigate complex obstacles

**Lesson 13: Timed Obstacle Course**
- Objective: Optimize navigation
- Challenge: Complete course in fastest time

---

### Module 6: Line Following (Lessons 14-15)

**Lesson 14: Line Sensor Basics**
- Objective: Understand line sensors
- Commands: `initLineSensors()`, `getLineSensorLeft()`, `getLineSensorMiddle()`, `getLineSensorRight()`
- Challenge: Detect and report line position

**Lesson 15: Following the Line**
- Objective: Make robot follow a line
- Commands: `followLine(threshold)`, `followLineMultiSensor(threshold)`
- Challenge: Follow a curved path

---

### Module 7: Autonomous Design (Lessons 16-17)

**Lesson 16: Autonomous Navigation - Part 1**
- Objective: Combine all sensors for autonomous behavior
- Challenge: Create a room-exploring robot

**Lesson 17: Autonomous Design - Part 2**
- Objective: Advanced autonomous behavior
- Challenge: Create a fully autonomous robot that can navigate, avoid obstacles, and follow lines

---

## Hardware Setup Required

- Arduino-compatible robot car with TB6612FNG motor driver
- Motor pins: PWMA(5), PWMB(6), AIN(7), BIN(8), STBY(3)
- Ultrasonic sensor: TRIG(13), ECHO(12)
- Sensor servo: Pin 10
- Claw servo: Pin 11
- Line sensors: A0 (Right), A1 (Middle), A2 (Left)
- RGB LED: Pin 4
- Buzzer: Pin 11 (optional)

---

## Progression Philosophy

1. **Weeks 1-2**: Linear and rotational motion (Lessons 1-6)
2. **Weeks 3-4**: Sensors and servos (Lessons 7-10)
3. **Weeks 5-6**: Obstacle courses (Lessons 11-13)
4. **Weeks 7-8**: Line following (Lessons 14-15)
5. **Weeks 9-10**: Autonomous design project (Lessons 16-17)

---

## Assessment Criteria

- **Completion**: Can student complete the basic example?
- **Understanding**: Can student explain what the code does?
- **Challenge**: Can student modify code to solve the challenge?
- **Creativity**: Does student add unique elements?
- **Troubleshooting**: Can student debug issues?

---

Created: February 2026
Author: GitHub Copilot for WWHS Research
