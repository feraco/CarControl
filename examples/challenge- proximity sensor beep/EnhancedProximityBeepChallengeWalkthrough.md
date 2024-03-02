
# Proximity Beep Challenge Walkthrough with Science Concepts

In this challenge, you'll learn to program a robot to use a buzzer for indicating the proximity of an object, with the beeping frequency varying based on the distance. This concept is akin to echolocation used by bats or ultrasonic sensors in cars.

## Step 1: Understanding the Setup

- **Robot Components:**
  - **Buzzer:** Emits sound, controlled by turning it on and off.
  - **Distance sensor:** Measures how far an object is.

- **Science Concept:**
  - The distance sensor acts like radar, emitting a signal that reflects back from an object. The time for this reflection is used to calculate distance, illustrating echo or sound wave principles.

## Step 2: Starting with the Code

### Define the Function

- Define a function `proximityAlert`, which is a set of instructions for the robot.

```cpp
void proximityAlert() {
}
```

### Checking the Distance

- Use a loop to continuously measure the distance, storing this in `distance`.

```cpp
while (true) {
  int distance = car.getDistanceToObstacle();
}
```

## Step 3: Making Decisions with If-Else Statements

- Use `if-else` statements to change beeping frequency based on `distance`.

```cpp
if (distance < 20) {
  beepBuzzer(100); // Rapid beeping for close proximity
} else if (distance >= 20 && distance < 40) {
  beepBuzzer(200); // Medium beeping for moderate proximity
} else {
  beepBuzzer(300); // Slow beeping for distant objects
}
```

- **Science Concept:**
  - This process mimics decision-making in the brain, using conditional logic, a core concept in computing and cognitive science.

## Step 4: Creating the beepBuzzer Function

- Define `beepBuzzer` to control the buzzer's sound pattern.

```cpp
void beepBuzzer(int delayTime) {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);
  delay(delayTime);
}
```

- **Science Concept:**
  - Changing the on-off cycle of the buzzer alters sound waves' frequency, demonstrating how vibration frequency affects sound pitch.

## Step 5: Putting It All Together

- Running `proximityAlert` enables the robot to analyze its surroundings and communicate through sound, similar to sonar technology.

## Conclusion and Task

You've integrated sensor input with output actions, learning how robots interact with their environment using principles from physics and electronics.

### Simple Task: Modify the Beep Pattern

**Objective:** Make the beep pattern more intuitive by modifying it.

**Instructions:**
1. Change `beepBuzzer` to produce two quick beeps for objects very close (distance < 20 cm).
2. Vary delay times in the `if-else` statements to differentiate proximity levels clearly.
3. Test your changes to see how the new beep pattern conveys distance information.

By completing this task, you'll enhance the robot's proximity alert system, showcasing how programming adjustments can improve user interaction.
