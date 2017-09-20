
bool SensorArray::initialize() {
  currentAngle.x = 0.0;
  currentAngle.y = 0.0;
  currentAngle.z = 0.0;
  mpu.init();
  return bme.begin();
}

void SensorArray::updatePositionData(float delta) {
  sensor_data_t accelData, gyroData, accelAngle;
  
  mpu.read_acc();
  mpu.read_gyro();

  accelData.x = mpu.ax / 16384.0;
  accelData.y = mpu.ay / 16384.0;
  accelData.z = mpu.az / 16384.0;
  
  gyroData.x = mpu.gx / 131.0;
  gyroData.y = mpu.gy / 131.0;
  gyroData.z = mpu.gz / 131.0;

  accelAngle.x = atan((accelData.y) / sqrt(pow(accelData.x, 2) + pow(accelData.z, 2))) * RAD2DEG; // roll
  accelAngle.y = atan(-1 * accelData.x / sqrt(pow(accelData.y, 2) + pow(accelData.z, 2))) * RAD2DEG; // pitch

  currentAngle.x = 0.98 * (currentAngle.x + gyroData.x * delta) + 0.02 * accelAngle.x;
  currentAngle.y = 0.98 * (currentAngle.y + gyroData.y * delta) + 0.02 * accelAngle.y;
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

