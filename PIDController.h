#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

class PIDController {
private:
  float error;
  float prevError;
  float Kp, Ki, Kd;
  float pid;
public:
  void initialize(float Kp, float Ki, float Kd);
  void calculatePID(float desired, float sensor);
  inline void setKp(float Kp) { this->Kp = Kp; }
  inline void setKi(float Ki) { this->Ki = Ki; }
  inline void setKd(float Kd) { this->Kd = Kd; }
  inline float getPID() { return pid; }
};

#endif
