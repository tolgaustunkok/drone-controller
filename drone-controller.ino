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
    while (1);
  }

  motorManager.initialize(8, 7, 6, 5);

  cmdInterpreter.initialize(&wireless, &motorManager, &sensors);
}

float errorX = 0.0, prevErrorX = 0.0;
float errorY = 0.0, prevErrorY = 0.0;

float xKp = 1.3, xKi = 0.04, xKd = 15.0;
float yKp = 1.3, yKi = 0.04, yKd = 15.0;

unsigned long startTime;
float delta = 0.0;

float pRoll, iRoll, dRoll, pidRoll;
float pPitch, iPitch, dPitch, pidPitch;

void loop() {
  startTime = millis();
  cmdInterpreter.interpret();
  sensors.updatePositionData(delta);

  // Error = Desired Value - Angle from IMU
  errorX = 0 - sensors.getCurrentAngle().x;
  errorY = 0 - sensors.getCurrentAngle().y;
  
  pRoll = xKp * errorX * delta;
  iRoll = xKi * (iRoll + errorX) * delta;
  dRoll = xKd * (errorX - prevErrorX) * delta;
  pidRoll = pRoll + iRoll + dRoll;

  pPitch = yKp * errorY * delta;
  iPitch = yKi * (iPitch + errorY) * delta;
  dPitch = yKd * (errorY - prevErrorY) * delta;
  pidPitch = pPitch + iPitch + dPitch;
  
  //wireless.addData(String(pidRoll).c_str());
  //wireless.addData(String(pidPitch).c_str());

  const int* motorThrusts = motorManager.getThrusts();

  motorManager.addMotor(CW_FRONT, -pidPitch - pidRoll);
  motorManager.addMotor(CCW_RIGHT, -pidPitch + pidRoll);
  motorManager.addMotor(CW_BACK, pidPitch + pidRoll);
  motorManager.addMotor(CCW_LEFT, pidPitch - pidRoll);
  
  motorManager.runMotors();

  //wireless.pumpData();

  prevErrorX = errorX;
  prevErrorY = errorY;
  delta = (millis() - startTime) / 1000.0;
}

