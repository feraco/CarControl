#include <CarControl.h>
#include <Ultrasonic.h>

// Initialize CarControl object with motor control pins
CarControl car(5, 6, 7, 8, 3, 2);

void setup() {
    // Initialize Serial communication at 9600 baud rate for debugging
    Serial.begin(9600);

    // Attach the claw servo to pin 11
    car.attachClaw(11);

    // Attach the sensor servo (for ultrasonic sensor) to pin 10
    car.attachSensorServo(10);

    // Setup the car control (initialize motor pins, etc.)
    car.setup();
}

void loop() {
    // Make the ultrasonic sensor look left
    car.lookLeft();
    delay(2000); // Wait for 2 seconds for the servo to move and stabilize

    // Make the ultrasonic sensor look right
    car.lookRight();
    delay(2000); // Wait for 2 seconds for the servo to move and stabilize

    // Center the ultrasonic sensor
    car.centerServo();
    delay(2000); // Wait for 2 seconds for the servo to move and stabilize

    // Open the claw
    car.openClaw();
    delay(1000); // Wait for 1 second for the claw to open

    // Close the claw
    car.closeClaw();
    delay(1000); // Wait for 1 second for the claw to close

    // Check the distance to the nearest obstacle
    car.getDistanceToObstacle();
    delay(1000); // Wait for 1 second to get the distance reading

    // Check if there's an obstacle in front
    car.checkObstacleInFront();

    // If the distance to the obstacle is less than 20 cm, stop the motors
    if (car.getDistanceToObstacle() < 20) {
        car.stopMotors();
        return; // Exit the loop function early to avoid further movement
    }

    // Forward movements with increasing duration
    car.moveForward(100, 300); // Move forward for 0.3 seconds
    delay(1000); // Wait for 1 second
    car.moveForward(100, 600); // Move forward for 0.6 seconds
    delay(1000); // Wait for 1 second
    car.moveForward(100, 900); // Move forward for 0.9 seconds
    delay(1000); // Wait for 1 second
    car.moveForward(100, 1200); // Move forward for 1.2 seconds
    delay(1000); // Wait for 1 second
    car.moveForward(100, 1500); // Move forward for 1.5 seconds
    delay(1000); // Wait for 1 second

    // Backward movements with increasing duration
    car.moveBackward(100, 300); // Move backward for 0.3 seconds
    delay(1000); // Wait for 1 second
    // ... Repeat this pattern for each backward movement ...

    // Left turn movements with increasing duration
    car.turnLeft(100, 300); // Turn left for 0.3 seconds
    delay(1000); // Wait for 1 second
    // ... Repeat this pattern for each left turn ...

    // Right turn movements with increasing duration
    car.turnRight(100, 300); // Turn right for 0.3 seconds
    delay(1000); // Wait for 1 second
    // ... Repeat this pattern for each right turn ...
}
