
void CommandInterpreter::initialize(const Wireless* w, const MotorManager* m, const SensorArray* s, const PIDController* pidRoll, const PIDController* pidPitch) {
  wireless = w;
  motorManager = m;
  sensors = s;
  this->pidRoll = pidRoll;
  this->pidPitch = pidPitch;
}

void CommandInterpreter::interpret() {
  wireless->getMessage(message, sizeof(char) * 32);

  if (message[0] != 0) {
    numOfTokens = count(message, ' ');
    Serial.println(message);
    
    if (numOfTokens == 1) {
      if (getValue(message, ' ', 0) == "STAT") {
        Serial.println("STAT command received.");
        
      } else if (getValue(message, ' ', 0) == "EXT") {
        Serial.println("Shutting down...");
        motorManager->setAllMotors(0);
      }
    } else if (numOfTokens == 2) {
      if (getValue(message, ' ', 0) == "THR") {
        Serial.println("THR command with 1 parameter received.");
        int thr = getValue(message, ' ', 1).toInt();
        motorManager->setAllMotors(thr);
      }
    } else if (numOfTokens == 3) {
      if (getValue(message, ' ', 0) == "THR") {
        Serial.println("THR command with 2 parameter received.");
        MOTOR_E motor = getValue(message, ' ', 1).toInt();
        int thrust = getValue(message, ' ', 2).toInt();
        motorManager->setMotor(motor, thrust);
      }
    } else if (numOfTokens == 4) {
      if (getValue(message, ' ', 0) == "PID") {
        Serial.println("PID command with 3 parameters received.");
        if (getValue(message, ' ', 2) == "P") {
          if (getValue(message, ' ', 1) == "PITCH") {
            pidPitch->setKp(getValue(message, ' ', 3).toFloat());
          } else {
            pidRoll->setKp(getValue(message, ' ', 3).toFloat());
          }
        } else if (getValue(message, ' ', 2) == "I") {
          if (getValue(message, ' ', 1) == "PITCH") {
            pidPitch->setKi(getValue(message, ' ', 3).toFloat());
          } else {
            pidRoll->setKi(getValue(message, ' ', 3).toFloat());
          }
        } else {
          if (getValue(message, ' ', 1) == "PITCH") {
            pidPitch->setKd(getValue(message, ' ', 3).toFloat());
          } else {
            pidRoll->setKd(getValue(message, ' ', 3).toFloat());
          }
        }
      }
    }
  }

  memset(message, 0, 32);
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
