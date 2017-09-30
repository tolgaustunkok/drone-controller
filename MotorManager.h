#ifndef MOTOR_MANAGER_H
#define MOTOR_MANAGER_H

#include <Servo.h>
#include "Structs.h"

class MotorManager {
  private:
    const int MAX_THRUST = 1400;
    Servo motors[4];
    int thrusts[4];
  public:
    void initialize(int cw_front_pin, int cw_back_pin, int ccw_left_pin, int ccw_right_pin);
    void runMotors();
    void setMotor(MOTOR_E motor, int thrust);
    void addMotor(MOTOR_E motor, int thrust);
    void setAllMotors(int thrust);
    int getThrust(MOTOR_E motor);
};

#endif
