#include <Wire.h>
#include "MotorManager.h"
#include "SensorArray.h"
#include "Wireless.h"
#include "CommandInterpreter.h"
#include "PIDController.h"
#include "Structs.h"

#define INIT_LED 4 // RED
#define INIT_SUCCESS_LED 2 // GREEN
#define RUNNING_LED 3 // BLUE

Wireless wireless;
SensorArray sensors;
MotorManager motorManager;
CommandInterpreter cmdInterpreter;
PIDController pidControllerRoll;
PIDController pidControllerPitch;
debug_data_t debugData;

void setup() {
  pinMode(INIT_LED, OUTPUT);
  pinMode(RUNNING_LED, OUTPUT);
  pinMode(INIT_SUCCESS_LED, OUTPUT);

  digitalWrite(RUNNING_LED, LOW);
  digitalWrite(INIT_LED, HIGH);
  digitalWrite(INIT_SUCCESS_LED, LOW);
  
  Serial.begin(9600);
  Wire.begin();

  wireless.initialize();

  if (!sensors.initialize()) {
    Serial.println("Sensors are failed to initialize. Halted.");
    while (1);
  }

  motorManager.initialize(8, 7, 6, 5);

  cmdInterpreter.initialize(&wireless, &motorManager, &sensors, &pidControllerRoll, &pidControllerPitch);

  //pidControllerRoll.initialize(1.3, 0.04, 15.0);
  //pidControllerPitch.initialize(1.3, 0.04, 15.0);
  pidControllerRoll.initialize(1.2, 0, 0);
  pidControllerPitch.initialize(1.2, 0, 0);
  
  digitalWrite(INIT_LED, LOW);
  digitalWrite(INIT_SUCCESS_LED, HIGH);
}

unsigned long startTime;
float delta = 0.0;
float accum = 0.0;

void loop() {
  startTime = millis();

  if (accum <= 0.5) {
    digitalWrite(RUNNING_LED, HIGH);
  } else if (accum <= 1.0) {
    digitalWrite(RUNNING_LED, LOW);
  } else {
    accum = 0.0;
  }
  
  cmdInterpreter.interpret();
  sensors.updatePositionData(delta);

  debugData.sensorData = sensors.getCurrentAngle();
  debugData.altitude = sensors.getAltitude(1014.5);
  debugData.temperature = sensors.getTemperature();

  pidControllerPitch.calculatePID(0.0, sensors.getCurrentAngle().y);
  pidControllerRoll.calculatePID(0.0, sensors.getCurrentAngle().x);
  
  float pidPitch = pidControllerPitch.getPID();
  float pidRoll = pidControllerRoll.getPID();

  //debugData.pidRoll = pidRoll;
  //debugData.pidPitch = pidPitch;
  debugData.delta = delta;

  for (int i = 0; i < 4; i++) {
    debugData.motorThrusts[i] = motorManager.getThrust(i);
  }

  motorManager.addMotor(CW_FRONT, -pidPitch - pidRoll);
  motorManager.addMotor(CCW_RIGHT, -pidPitch + pidRoll);
  motorManager.addMotor(CW_BACK, pidPitch + pidRoll);
  motorManager.addMotor(CCW_LEFT, pidPitch - pidRoll);
  
  motorManager.runMotors();

  wireless.pumpData(&debugData);

  accum += delta;
  delta = (millis() - startTime) / 1000.0;
}

