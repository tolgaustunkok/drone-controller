
bool SensorArray::initialize() {
  currentAngle.x = 0.0;
  currentAngle.y = 0.0;
  currentAngle.z = 0.0;
  mpu.init();

  updatePositionData(0.001);
  
  return bme.begin();
}

void SensorArray::updatePositionData(float delta) {
  sensor_data_t accelData, gyroData, accelAngle;
  float avX = 0, avY = 0, avZ = 0;
  
  mpu.read_acc();
  mpu.read_gyro();

  accelData.x = mpu.ax / 16384.0;
  accelData.y = mpu.ay / 16384.0;
  accelData.z = mpu.az / 16384.0;
  
  gyroData.x = mpu.gx / 131.0 - 0.75;
  gyroData.y = mpu.gy / 131.0 - 0.65;
  gyroData.z = mpu.gz / 131.0 - 0.35;

  accelAngle.x = atan(accelData.y / sqrt(pow(accelData.x, 2) + pow(accelData.z, 2))) * RAD2DEG; // pitch
  accelAngle.y = atan(accelData.x / sqrt(pow(accelData.y, 2) + pow(accelData.z, 2))) * RAD2DEG;
  accelAngle.z = atan(sqrt(pow(accelData.x, 2) + pow(accelData.y, 2)) / accelData.z) * RAD2DEG; // roll

  if (initialRun) {
    initialAngle.x = 0.95 * (currentAngle.x + gyroData.x * delta) + 0.05 * accelAngle.x;
    initialAngle.y = 0.95 * (currentAngle.y + gyroData.y * delta) + 0.05 * accelAngle.y;
    initialRun = false;
  }

  currentAngle.x = initialAngle.x - (0.95 * (currentAngle.x + gyroData.x * delta) + 0.05 * accelAngle.x);
  currentAngle.y = initialAngle.y - (0.95 * (currentAngle.y + gyroData.y * delta) + 0.05 * accelAngle.y);

  delay(35);
}

float SensorArray::getAltitude(float currentPressure) {
  return bme.readAltitude(currentPressure);
}

float SensorArray::getTemperature() {
  return bme.readTemperature();
}

const sensor_data_t& SensorArray::getCurrentAngle() {
  return currentAngle;
}

