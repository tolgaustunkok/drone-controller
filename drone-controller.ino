#include <Wire.h>
#include "MotorManager.h"
#include "SensorArray.h"
#include "Wireless.h"
#include "CommandInterpreter.h"
#include "PIDController.h"

Wireless wireless;
SensorArray sensors;
MotorManager motorManager;
CommandInterpreter cmdInterpreter;
PIDController pidControllerRoll;
PIDController pidControllerPitch;
debug_data_t debugData;

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

  pidControllerRoll.initialize(1.3, 0.04, 15.0);
  pidControllerPitch.initialize(1.3, 0.04, 15.0);
}

unsigned long startTime;
float delta = 0.0;

void loop() {
  startTime = millis();
  
  cmdInterpreter.interpret();
  sensors.updatePositionData(delta);

  debugData.sensorData = sensors.getCurrentAngle();
  debugData.altitude = sensors.getAltitude(1014.5);
  debugData.temperature = sensors.getTemperature();

  pidControllerPitch.calculatePID(0.0, sensors.getCurrentAngle().y);
  pidControllerRoll.calculatePID(0.0, sensors.getCurrentAngle().x);
  
  float pidPitch = pidControllerPitch.getPID() * delta;
  float pidRoll = pidControllerRoll.getPID() * delta;

  const int* motorThrusts = motorManager.getThrusts();
  
  debugData.motorThrusts[CW_FRONT] = motorThrusts[CW_FRONT];
  debugData.motorThrusts[CCW_RIGHT] = motorThrusts[CCW_RIGHT];
  debugData.motorThrusts[CW_BACK] = motorThrusts[CW_BACK];
  debugData.motorThrusts[CCW_LEFT] = motorThrusts[CCW_LEFT];

  motorManager.addMotor(CW_FRONT, -pidPitch - pidRoll);
  motorManager.addMotor(CCW_RIGHT, -pidPitch + pidRoll);
  motorManager.addMotor(CW_BACK, pidPitch + pidRoll);
  motorManager.addMotor(CCW_LEFT, pidPitch - pidRoll);
  
  motorManager.runMotors();

  wireless.pumpData(&debugData);
  
  delta = (millis() - startTime) / 1000.0;
}

