#ifndef CarControl_h
#define CarControl_h

#include "Arduino.h"

class CarControl {
public:
    CarControl(int pwma, int pwmb, int ain, int bin, int stby, int modeSwitch);
    void setup();
    void moveForward(int duration);
    void moveBackward(int duration);
    void turnLeft(int duration);
    void turnRight(int duration);
    void stopMotors();
    void stopTime(int mS);
    void turnAround();
    void moveSlowForward(int duration);
    void customMovement(int ainState, int binState, int pwmaPower, int pwmbPower, int duration);

private:
    int _pwma, _pwmb, _ain, _bin, _stby, _modeSwitch;
};

#endif
