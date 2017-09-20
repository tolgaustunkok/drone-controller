#ifndef MOTOR_MANAGER_H
#define MOTOR_MANAGER_H

#include <Servo.h>

typedef enum {
  CW_FRONT = 0,
  CW_BACK = 1,
  CCW_LEFT = 2,
  CCW_RIGHT = 3
} MOTOR_E;

class MotorManager {
  private:
    Servo motors[4];
    int thrusts[4];
  public:
    void initialize(int cw_front_pin, int cw_back_pin, int ccw_left_pin, int ccw_right_pin);
    void runMotors();
    void setMotor(MOTOR_E motor, int thrust);
    void setAllMotors(int thrust);
    const int* getThrusts();
};

#endif
