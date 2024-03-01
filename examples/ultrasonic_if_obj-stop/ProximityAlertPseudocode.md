
## Challenge 6: Proximity Alert with Beeping Sound - Pseudocode

**Pseudocode:**

```plaintext
FUNCTION proximityAlert
  WHILE true DO
    SET distance = getDistanceToObstacle()

    IF distance < 20 THEN
      CALL beepBuzzer WITH 100 // Short delay for close proximity
    ELSE IF distance >= 20 AND distance < 40 THEN
      CALL beepBuzzer WITH 200 // Medium delay for moderate proximity
    ELSE
      CALL beepBuzzer WITH 300 // Long delay for distant objects
    END IF
  END WHILE
END FUNCTION

FUNCTION beepBuzzer WITH delayTime
  // Turn the buzzer on
  SET BUZZER_PIN to HIGH
  WAIT for 100 milliseconds
  // Turn the buzzer off
  SET BUZZER_PIN to LOW
  WAIT for delayTime
END FUNCTION
```

This pseudocode outlines the logic for the proximity alert system, which uses a buzzer to indicate the distance to an object based on its proximity to the car.
