# Arduino Robot Car - Quick Reference Card

## Essential Commands (Keep This Handy!)

### Movement
```cpp
car.moveForward(speed, time);      // Go forward
car.moveBackward(speed, time);     // Go backward
car.turnLeft(speed, time);         // Turn left
car.turnRight(speed, time);        // Turn right
car.turnAround();                  // 180° turn
car.stopMotors();                  // Stop all
```

### Distance Sensing
```cpp
int distance = car.getDistanceToObstacle();  // Measure ahead
int left = car.getLeftDistance();            // Look & measure left
int center = car.getCenterDistance();        // Look & measure center  
int right = car.getRightDistance();          // Look & measure right
```

### Sensor Servo
```cpp
car.attachSensorServo(10);         // Setup (in void setup())
car.lookLeft();                    // Turn sensor left
car.lookRight();                   // Turn sensor right
car.centerServo();                 // Point sensor forward
```

### Claw Control
```cpp
car.attachClaw(11);                // Setup (in void setup())
car.openClaw();                    // Open claw
car.closeClaw();                   // Close claw
```

### Line Sensors
```cpp
car.initLineSensors();             // Setup (in void setup())
int L = car.getLineSensorLeft();   // Read left sensor (0-1023)
int M = car.getLineSensorMiddle(); // Read middle sensor
int R = car.getLineSensorRight();  // Read right sensor
car.followLine(threshold);         // Auto line following
```

## Common Patterns

### Check Distance Before Moving
```cpp
int distance = car.getCenterDistance();
if(distance > 30) {
  car.moveForward(150, 1000);
} else {
  Serial.println("Obstacle!");
  car.stopMotors();
}
```

### Scan for Best Path
```cpp
int L = car.getLeftDistance();
int C = car.getCenterDistance();
int R = car.getRightDistance();
car.centerServo();  // Always recenter!

if(C > L && C > R) {
  car.moveForward(150, 500);
} else if(L > R) {
  car.turnLeft(150, 500);
} else {
  car.turnRight(150, 500);
}
```

### Grab Object Sequence
```cpp
car.openClaw();                    // 1. Open
delay(1000);
car.moveForward(100, 800);         // 2. Approach
delay(500);
car.closeClaw();                   // 3. Grab
delay(1500);
car.moveBackward(100, 500);        // 4. Back away
```

### Line Following
```cpp
int threshold = 500;
int L = car.getLineSensorLeft();
int M = car.getLineSensorMiddle();
int R = car.getLineSensorRight();

if(M < threshold) {
  car.moveForward(140, 100);       // Centered - go straight
} else if(L < threshold) {
  car.turnLeft(120, 50);           // Line on left - correct left
} else if(R < threshold) {
  car.turnRight(120, 50);          // Line on right - correct right
}
```

## Typical Values

### Speed
- **Slow/Careful:** 80-120
- **Medium/Normal:** 140-180
- **Fast/Maximum:** 200-255

### Duration (for turns)
- **45° turn:** ~250ms
- **90° turn:** ~500ms
- **180° turn:** ~1000ms
(Adjust for your robot!)

### Line Sensor Threshold
- **Typical:** 500
- **On black line:** 0-300
- **On white surface:** 700-1023
(Calibrate for your lighting!)

### Safe Distance
- **Stop distance:** 20-30cm
- **Slow down:** 40-50cm
- **Full speed:** 60+ cm

## Basic Code Structure

```cpp
#include <CarControl.h>

CarControl car(5, 6, 7, 8, 3, 2);

void setup() {
  Serial.begin(9600);
  car.setup();
  
  // Attach any servos/sensors you'll use:
  car.attachSensorServo(10);
  car.attachClaw(11);
  car.initLineSensors();
}

void loop() {
  // Your robot behavior here
  // This runs over and over
}
```

## Debugging Tips

1. **Print everything!**
   ```cpp
   Serial.println("Doing this now...");
   Serial.print("Distance: ");
   Serial.println(distance);
   ```

2. **Wait after servo commands**
   ```cpp
   car.lookLeft();
   delay(500);  // Let servo reach position!
   ```

3. **Check your threshold**
   ```cpp
   // Print sensor values to find right threshold
   Serial.println(car.getLineSensorMiddle());
   ```

4. **Is it in the right place?**
   - Setup code → void setup()
   - Repeating code → void loop()

5. **Did you attach it?**
   ```cpp
   car.attachSensorServo(10);  // Required before lookLeft/Right!
   car.attachClaw(11);         // Required before open/closeClaw!
   car.initLineSensors();      // Required before reading sensors!
   ```

## Quick Troubleshooting

| Problem | Check |
|---------|-------|
| Robot doesn't move | Batteries? car.setup()? Uploaded? |
| Servo doesn't work | Did you attachSensorServo()? delay()? |
| Wrong sensor values | Calibrate! Print values to check |
| Code uploads but does nothing | Is it in loop() or setup()? |
| Robot moves too fast/slow | Adjust speed parameter |
| Turns too much/little | Adjust duration parameter |

---

Save this file! Print it! Keep it by your computer while coding!

**Pro Tip:** Start with the example code, modify one thing at a time, and test frequently!
