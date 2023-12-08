#include <CarControl.h>
#include <Ultrasonic.h>
#include <Servo.h>

// ... existing setup for CarControl ...
// Motor control pins
int pwma = 3; // PWM control for motor A
int pwmb = 5; // PWM control for motor B
int ain = 2;  // Direction control for motor A
int bin = 4;  // Direction control for motor B
int stby = 6; // Standby

// Initialize CarControl object
CarControl car(pwma, pwmb, ain, bin, stby, 0); // 0 for modeSwitch if not used

void setup() {
    // ... existing setup code ...

    car.attachClaw(11); // Attach the claw servo to pin 11
}

void loop() {
    // ... existing loop code ...

    car.openClaw();   // Open the claw
    delay(1000);      // Wait for a second
    car.closeClaw();  // Close the claw
    delay(1000);      // Wait for a second
}
