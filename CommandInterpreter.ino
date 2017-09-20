
void CommandInterpreter::initialize(const Wireless& w, const MotorManager& m, const SensorArray& s) {
  wireless = w;
  motorManager = m;
  sensors = s;
}

void CommandInterpreter::interpret() {
  wireless.getMessage(message, sizeof(char) * 50);

  if (message[0] != 0) {
    numOfTokens = count(message, ' ');
    
    if (numOfTokens == 1) {
      if (getValue(message, ' ', 0) == "STAT") {
        float altitude = sensors.getAltitude(1013.90);
        float temperature = sensors.getTemperature();
        const int* motorThrusts = motorManager.getThrusts();
        
        wireless.sendInfo(("Altitude: " + String(altitude)).c_str());
        wireless.sendInfo(("Temperature: " + String(temperature)).c_str());
        wireless.sendInfo(("Motor CW Front: " + String(motorThrusts[CW_FRONT])).c_str());
        wireless.sendInfo(("Motor CW Back: " + String(motorThrusts[CW_BACK])).c_str());
        wireless.sendInfo(("Motor CCW Left: " + String(motorThrusts[CCW_LEFT])).c_str());
        wireless.sendInfo(("Motor CCW Right: " + String(motorThrusts[CCW_RIGHT])).c_str());
      }
    } else if (numOfTokens == 2) {
      if (getValue(message, ' ', 0) == "THR") {
        int thr = getValue(message, ' ', 1).toInt();
        motorManager.setAllMotors(thr);
      }
    } else if (numOfTokens == 3) {
      if (getValue(message, ' ', 0) == "THR") {
        MOTOR_E motor = getValue(message, ' ', 1).toInt();
        int thrust = getValue(message, ' ', 2).toInt();
        motorManager.setMotor(motor, thrust);
      }
    }
  }

  message[0] = 0;
}

String CommandInterpreter::getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

int CommandInterpreter::count(char* message, char delim) {
  int len = strlen(message);
  int c = 1;

  for (int i = 0; i < len; i++) {
    if (message[i] == delim) {
      c++;
    }
  }

  return c;
}
