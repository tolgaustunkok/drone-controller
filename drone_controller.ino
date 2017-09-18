#include <Wire.h>
#include "MotorManager.h"
#include "SensorArray.h"
#include "Wireless.h"
#include "CommandInterpreter.h"

Wireless wireless;
SensorArray sensors;
MotorManager motorManager;
CommandInterpreter cmdInterpreter;

long startTime, delta = 0;

void setup() {
  Wire.begin();

  wireless.initialize();
  wireless.sendInfo("Wireless module initialized.");

  if (!sensors.initialize()) {
    wireless.sendInfo("Barometric pressure sensor (BMP280) failed to initialize.");
  } else {
    wireless.sendInfo("All sensors initialized.");
  }

  motorManager.initialize(8, 7, 6, 5);
  wireless.sendInfo("All motors initialized.");

  cmdInterpreter.initialize(wireless, motorManager, sensors);
  wireless.sendInfo("Command interpreter initialized.");
}

void loop() {
  startTime = millis();

  cmdInterpreter.interpret();
  
  motorManager.runMotors();
  
  delta = millis() - startTime;
}

