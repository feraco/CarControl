# CarControl Library

An Arduino library for controlling ELEGOO-style smart robot cars. Designed for classroom use, CarControl wraps low-level motor, sensor, and servo operations into simple, readable commands so students can focus on logic and problem-solving instead of wiring details.

**Author:** Frederick Feraco — New York State Master Teacher  
**Version:** 2.1.0  
**License:** Open Source  
**Platform:** Arduino (all architectures)

---

## Table of Contents

- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Installation](#installation)
- [Quick Start](#quick-start)
- [API Reference](#api-reference)
  - [Movement](#movement)
  - [Ultrasonic Sensor](#ultrasonic-sensor)
  - [Servo & Claw](#servo--claw)
  - [Line Sensors](#line-sensors)
  - [Buzzer & Audio](#buzzer--audio)
  - [RGB LED](#rgb-led)
  - [Battery Monitoring](#battery-monitoring)
- [Curriculum (16 Lessons)](#curriculum-16-lessons)
- [Examples](#examples)
- [Pin Reference](#pin-reference)
- [Troubleshooting](#troubleshooting)

---

## Features

- Simple, beginner-friendly API for motor control
- Ultrasonic distance sensing with servo-mounted scanning
- 3-sensor line following and intersection detection
- Claw servo for object manipulation
- RGB LED feedback, buzzer patterns, and Star Wars theme
- Battery level monitoring
- Includes a complete 16-lesson K-12 robotics curriculum

---

## Hardware Requirements

| Component | Details |
|---|---|
| Microcontroller | Arduino Uno / Nano (or ELEGOO board) |
| Motor Driver | TB6612FNG (dual H-bridge) |
| Ultrasonic Sensor | HC-SR04 |
| Line Sensors | 3× IR reflectance (left, middle, right) |
| Servos | Sensor servo + claw servo (standard hobby) |
| RGB LED | NeoPixel-compatible (WS2812) |
| Buzzer | Passive buzzer (optional) |
| Battery | 2S Li-ion pack (6.0–8.4 V) |

---

## Installation

### Arduino IDE (recommended)

1. Download or clone this repository.
2. Copy the `CarControl` folder into your Arduino `libraries` directory:
   - **macOS:** `~/Documents/Arduino/libraries/`
   - **Windows:** `Documents\Arduino\libraries\`
   - **Linux:** `~/Arduino/libraries/`
3. Restart the Arduino IDE.
4. The library should appear under **Sketch → Include Library → CarControl**.

### Dependencies

The following libraries must also be installed (available through the Arduino Library Manager):

- **FastLED** — RGB LED control
- **Ultrasonic** — HC-SR04 sensor
- **Servo** — included with the Arduino IDE

---

## Quick Start

```cpp
#include <CarControl.h>

// Initialize: CarControl(PWMA, PWMB, AIN, BIN, STBY, modeSwitch)
CarControl car(5, 6, 7, 8, 3, 2);

void setup() {
  car.setup();
}

void loop() {
  car.moveForward(200, 2000);  // Drive forward at speed 200 for 2 seconds
  car.stopTime(1000);          // Pause for 1 second
  car.turnRight(180, 600);     // Turn right
  car.stopTime(500);
}
```

Upload this sketch and your car will drive in a repeating rectangular pattern.

---

## API Reference

### Movement

| Function | Description |
|---|---|
| `car.moveForward(speed, duration)` | Drive forward at `speed` (0–255) for `duration` ms |
| `car.moveBackward(speed, duration)` | Drive backward at `speed` for `duration` ms |
| `car.moveSlowForward(duration, speed)` | Drive forward at a low speed for `duration` ms |
| `car.turnLeft(speed, duration)` | Pivot left at `speed` for `duration` ms |
| `car.turnRight(speed, duration)` | Pivot right at `speed` for `duration` ms |
| `car.turnAround()` | Execute a 180-degree turn |
| `car.stopMotors()` | Immediately stop both motors |
| `car.stopTime(ms)` | Hold the car in standby for `ms` milliseconds |
| `car.customMovement(fwdA, fwdB, spdA, spdB, dur)` | Independent control of each motor's direction, speed, and duration |

**Example — Drive a Square:**

```cpp
for (int i = 0; i < 4; i++) {
  car.moveForward(200, 1000);
  car.stopTime(300);
  car.turnRight(180, 600);
  car.stopTime(300);
}
```

---

### Ultrasonic Sensor

The HC-SR04 sensor is wired to pins 13 (trigger) and 12 (echo) by default.

| Function | Description |
|---|---|
| `car.getDistanceToObstacle()` | Returns the distance to the nearest object in centimeters |
| `car.checkObstacleInFront()` | Sets an internal flag if an obstacle is detected |

**Example — Stop Before Hitting a Wall:**

```cpp
int distance = car.getDistanceToObstacle();
if (distance < 15) {
  car.stopMotors();
} else {
  car.moveForward(180, 100);
}
```

---

### Servo & Claw

| Function | Description |
|---|---|
| `car.attachSensorServo(pin)` | Attach the sensor-aiming servo to the specified pin |
| `car.lookLeft()` | Rotate the sensor servo to face left |
| `car.lookRight()` | Rotate the sensor servo to face right |
| `car.centerServo()` | Return the sensor servo to center position |
| `car.getLeftDistance()` | Look left and return the distance reading |
| `car.getRightDistance()` | Look right and return the distance reading |
| `car.getCenterDistance()` | Look center and return the distance reading |
| `car.attachClaw(pin)` | Attach the claw servo to the specified pin |
| `car.openClaw()` | Open the claw |
| `car.closeClaw()` | Close the claw |

**Example — Scan and Decide:**

```cpp
car.attachSensorServo(10);
int leftDist  = car.getLeftDistance();
int rightDist = car.getRightDistance();

if (leftDist > rightDist) {
  car.turnLeft(180, 600);
} else {
  car.turnRight(180, 600);
}
```

---

### Line Sensors

Three IR reflectance sensors are connected to analog pins A0 (right), A1 (middle), and A2 (left).

| Function | Description |
|---|---|
| `car.initLineSensors()` | Initialize the line sensor pins |
| `car.getLineSensorLeft()` | Read the left sensor value |
| `car.getLineSensorMiddle()` | Read the middle sensor value |
| `car.getLineSensorRight()` | Read the right sensor value |
| `car.followLine(threshold)` | Continuously adjust steering to follow a line |
| `car.followLineMultiSensor(threshold)` | Enhanced multi-sensor line following |
| `car.stopAtLine(threshold)` | Stop the car when any sensor detects a line |
| `car.followLineUntilCondition(threshold, duration)` | Follow a line for a set duration |
| `car.followLineAvoidObstacle(threshold, obstacleDist)` | Follow a line while avoiding obstacles |
| `car.intersectionDecision(threshold, decisionFn)` | Call a custom function when an intersection is detected |

> **Note:** The `threshold` value determines what sensor reading counts as "on the line." You may need to calibrate this for your surface. A typical starting value is `500`.

**Example — Basic Line Following:**

```cpp
car.initLineSensors();

void loop() {
  car.followLine(500);
}
```

---

### Buzzer & Audio

| Function | Description |
|---|---|
| `car.attachBuzzer(pin)` | Attach a passive buzzer to the specified pin |
| `car.beep(count)` | Emit the specified number of beeps |
| `car.singleBeep()` | Emit one short beep |
| `car.doubleBeep()` | Emit two quick beeps |
| `car.playStarWars()` | Play the Star Wars theme melody |

---

### RGB LED

A NeoPixel-compatible LED is connected to pin 4.

| Function | Description |
|---|---|
| `car.lightRGBForDuration(color, duration)` | Light the LED with `color` for `duration` ms |

**Example:**

```cpp
car.lightRGBForDuration(CRGB::Green, 2000);  // Green for 2 seconds
car.lightRGBForDuration(CRGB::Red, 1000);    // Red for 1 second
```

---

### Battery Monitoring

| Function | Description |
|---|---|
| `car.getBatteryLevel()` | Returns battery charge as a percentage (0–100%) |

**Example:**

```cpp
float level = car.getBatteryLevel();
Serial.print("Battery: ");
Serial.print(level);
Serial.println("%");
```

---

## Curriculum (16 Lessons)

This repository includes a complete, progressive robotics curriculum designed for students with no prior coding experience. Each lesson builds on the one before it.

| # | Lesson | Topic |
|---|---|---|
| 01 | First Steps — Moving Forward | `moveForward`, `stopTime` |
| 02 | Going Backward | `moveBackward` |
| 03 | Linear Motion Challenge | Combining forward/backward movement |
| 04 | Basic Turning | `turnLeft`, `turnRight` (drive a square) |
| 05 | Advanced Rotation | Polygons, `turnAround` |
| 06 | Rotation Challenge | Waypoint navigation |
| 07 | Ultrasonic Sensor Basics | `getDistanceToObstacle` |
| 08 | Sensor Servo Control | `lookLeft`, `lookRight`, scanning |
| 09 | Claw Servo Control | `openClaw`, `closeClaw` |
| 10 | Obstacle Detection | `if`/`else` with distance readings |
| 11 | Simple Obstacle Course | Pre-programmed course navigation |
| 12 | Advanced Obstacle Course | Stuck detection, retry logic |
| 13 | Line Sensor Basics | `getLineSensorLeft/Middle/Right` |
| 14 | Line Following | `followLine`, `followLineMultiSensor` |
| 15 | Autonomous Design Part 1 | State machines, multi-mode robots |
| 16 | Autonomous Design Part 2 | Final project — full autonomous missions |

**Lesson files:** [`examples/`](examples/) — each lesson is a standalone `.ino` sketch.  
**Expanded lesson guides:** [`docs/`](docs/) — printable Word-ready documents for each lesson.  
**Quick reference card:** [`QUICK_REFERENCE.md`](QUICK_REFERENCE.md)  
**Full teaching guide:** [`COMPLETE_LESSON_GUIDE.md`](COMPLETE_LESSON_GUIDE.md)

---

## Examples

Beyond the curriculum lessons, additional standalone examples are included:

| Example | Description |
|---|---|
| `almostsumo` | Sumo-bot behavior using ultrasonic sensing |
| `basic-movements-with-comments` | Annotated movement demo |
| `demo-commands` | Showcase of all available commands |
| `linefollow` | Standalone line-following sketch |
| `maze-bot` | Maze-solving algorithm |
| `Sensordata` | Print all sensor readings to Serial Monitor |
| `ultrasonic_if_obj-stop` | Stop when an object is detected |
| `clawgrab5cm` | Grab an object within 5 cm |
| `clawopenclose` | Open and close the claw on a loop |
| `Factory-reset` | Restore the car to factory firmware |

---

## Pin Reference

| Function | Pin(s) |
|---|---|
| Motor PWM A | 5 |
| Motor PWM B | 6 |
| Motor Direction AIN | 7 |
| Motor Direction BIN | 8 |
| Motor Standby (STBY) | 3 |
| Mode Switch | 2 |
| Ultrasonic Trigger | 13 |
| Ultrasonic Echo | 12 |
| Sensor Servo | 10 (typical) |
| Claw Servo | 11 (typical) |
| Line Sensor Right | A0 |
| Line Sensor Middle | A1 |
| Line Sensor Left | A2 |
| RGB LED (NeoPixel) | 4 |
| Battery Voltage | A3 |
| Buzzer | 11 (typical) |

---

## Troubleshooting

| Problem | Solution |
|---|---|
| Car doesn't move | Check that the battery pack is switched on and fully charged. Verify motor wiring matches the pin assignments above. |
| Car drifts to one side | The two motors may run at slightly different speeds. Use `customMovement` to fine-tune individual motor speeds. |
| Ultrasonic reads 0 | Ensure the HC-SR04 is connected to pins 13 (trig) and 12 (echo). Check for loose jumper wires. |
| Line following is erratic | Calibrate the `threshold` value for your surface. Print sensor readings with `Serial.println()` to find the right value. |
| Compilation error: "FastLED.h not found" | Install the **FastLED** library via **Sketch → Include Library → Manage Libraries**. |
| Servo jitters or doesn't move | Servos draw significant current. Ensure the battery is above 7 V. Only attach servos you are actively using. |

---

## Contributing

Contributions, bug reports, and lesson improvements are welcome. Please open an issue or submit a pull request on [GitHub](https://github.com/feraco/CarControl).

---

*Built for educators. Powered by curiosity.*
