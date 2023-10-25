#ifndef CarControl_h
#define CarControl_h

#include "Arduino.h"

class CarControl {
public:
    CarControl(int pwma, int pwmb, int ain, int bin, int stby, int modeSwitch);
    void setup();
    void moveForward(int speed, int duration);
    void moveBackward(int speed, int duration);
    void turnLeft(int speed, int duration);
    void turnRight(int speed, int duration);
    void stopMotors();
    void stopTime(int mS);
    void turnAround();
    void CarControl::moveSlowForward(int duration, int speed) {
    void customMovement(int ainState, int binState, int pwmaPower, int pwmbPower, int duration);

private:
    void setMotorSpeed(int speed);
    int _pwma, _pwmb, _ain, _bin, _stby, _modeSwitch;
};

#endif
