#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

#include "Wireless.h"
#include "MotorManager.h"
#include "SensorArray.h"
#include "PIDController.h"

class CommandInterpreter {
private:
  char message[32];
  int numOfTokens;
  Wireless *wireless;
  MotorManager *motorManager;
  SensorArray *sensors;
  PIDController *pidRoll;
  PIDController *pidPitch;
  String getValue(String data, char separator, int index);
  int count(char* message, char delim);
public:
  void initialize(const Wireless* w, const MotorManager* m, const SensorArray* s, const PIDController* pidRoll, const PIDController* pidPitch);
  void interpret();
};

#endif

