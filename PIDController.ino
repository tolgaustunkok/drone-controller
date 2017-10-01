
void PIDController::calculatePID(float sensor) {
  error = desired - sensor;
  float p = Kp * error;
  float i = Ki * (i + error);
  float d = Kd * (error - prevError);
  pid = p + i + d;
  prevError = error;
}

void PIDController::initialize(float Kp, float Ki, float Kd) {
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;
  error = prevError = desired = 0;
}

