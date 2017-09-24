#include <Wire.h>
#include "MotorManager.h"
#include "SensorArray.h"
#include "Wireless.h"
#include "CommandInterpreter.h"

Wireless wireless;
SensorArray sensors;
MotorManager motorManager;
CommandInterpreter cmdInterpreter;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  wireless.initialize();

  if (!sensors.initialize()) {
    Serial.println("Sensors are failed to initialize.");
  }

  motorManager.initialize(8, 7, 6, 5);

  cmdInterpreter.initialize(&wireless, &motorManager, &sensors);
}

float error = 0.0, prevError = 0.0;
float Kp = 1.3, Ki = 0.04, Kd = 15.0;
unsigned long startTime;
float delta = 0.0;

void loop() {
  startTime = millis();
  cmdInterpreter.interpret();
  sensors.updatePositionData(delta);

  // Error = Desired Value - Angle from IMU
  error = 0 - sensors.getCurrentAngle().y;
  
  float pRoll = Kp * error * delta;
  float iRoll = Ki * (iRoll + error) * delta;
  float dRoll = Kd * (error - prevError) * delta;
  float pidRoll = pRoll + iRoll + dRoll;

  wireless.addData(String(pidRoll).c_str());
  
  motorManager.runMotors();

  wireless.pumpData();

  prevError = error;
  delta = (millis() - startTime) / 1000.0;
}

