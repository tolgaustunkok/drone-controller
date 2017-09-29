int MotorManager::getThrust(MOTOR_E motor) {
  return thrusts[motor];
}

void MotorManager::setAllMotors(int thrust) {
  int resultantThrust = thrust + 1000;

  if (resultantThrust >= 1000 && resultantThrust <= MAX_THRUST) {
    for (int i = 0; i < 4; i++) {
      thrusts[i] = resultantThrust;
    }
  }
}

void MotorManager::setMotor(MOTOR_E motor, int thrust) {
  int resultantThrust = thrust + 1000;
  if (resultantThrust >= 1000 && resultantThrust <= MAX_THRUST) {
    thrusts[motor] = resultantThrust;
  }
}

void MotorManager::addMotor(MOTOR_E motor, int thrust) {
  int resultantThrust = thrust + thrusts[motor];
  if (resultantThrust >= 1000 && resultantThrust <= MAX_THRUST) {
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
