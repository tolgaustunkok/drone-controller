#include <Servo.h>

void MotorManager::getStatus() {
  Wireless w;
  w.initialize();

  for (int i = 0; i < 4; i++) {
    char tmpBuffer[10];
    w.sendInfo("Motor Thrust ");
    sprintf(tmpBuffer, "%d: ", i + 1);
    w.sendInfo(tmpBuffer);
    sprintf(tmpBuffer, "%d", thrusts[i]);
    w.sendInfo(tmpBuffer);
  }
}

void MotorManager::setAllMotors(int thrust) {
  int resultantThrust = thrust + 1000;

  if (resultantThrust >= 1000 && resultantThrust <= 1700) {
    for (int i = 0; i < 4; i++) {
      thrusts[i] = resultantThrust;
    }
  }
}

void MotorManager::setMotor(MOTOR_E motor, int thrust) {
  int resultantThrust = thrust + 1000;
  if (resultantThrust >= 1000 && resultantThrust <= 1700) {
    thrusts[motor] = resultantThrust;
  }
}

void MotorManager::initialize(int cw_front_pin, int cw_back_pin, int ccw_left_pin, int ccw_right_pin) {
  motors[CW_FRONT].attach(cw_front_pin);
  motors[CW_BACK].attach(cw_back_pin);
  motors[CCW_LEFT].attach(ccw_left_pin);
  motors[CCW_RIGHT].attach(ccw_right_pin);

  for (int i = 0; i < 4; i++) {
    thrusts[i] = 1000;
  }
}

void MotorManager::runMotors() {
  for (int i = 0; i < 4; i++) {
    motors[i].writeMicroseconds(thrusts[i]);
  }
}
