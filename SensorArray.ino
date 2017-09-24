
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

  /*for (int i = 0; i < 10; i++) {
    mpu.read_gyro();
    avX += mpu.gx / 131.0 - 0.75;
    avY += mpu.gy / 131.0 - 0.65;
    avZ += mpu.gz / 131.0 - 0.35;
    delay(35);
  }*/

  //gyroData.x = avX / 10.0;
  //gyroData.y = avY / 10.0;
  //gyroData.z = avZ / 10.0;  

  accelAngle.x = atan(accelData.y / sqrt(pow(accelData.x, 2) + pow(accelData.z, 2))) * RAD2DEG; // pitch
  accelAngle.y = atan(accelData.x / sqrt(pow(accelData.y, 2) + pow(accelData.z, 2))) * RAD2DEG;
  accelAngle.z = atan(sqrt(pow(accelData.x, 2) + pow(accelData.y, 2)) / accelData.z) * RAD2DEG; // roll

  if (initialRun) {
    initialAngle.x = 0.05 * (currentAngle.x + gyroData.x * delta) + 0.95 * accelAngle.x;
    initialAngle.y = 0.05 * (currentAngle.y + gyroData.y * delta) + 0.95 * accelAngle.y;
    initialRun = false;
  }

  currentAngle.x = initialAngle.x - (0.02 * (currentAngle.x + gyroData.x * delta) + 0.98 * accelAngle.x);
  currentAngle.y = initialAngle.y - (0.02 * (currentAngle.y + gyroData.y * delta) + 0.98 * accelAngle.y);

  /*Serial.print(String(currentAngle.x) + " ");
  Serial.print(String(currentAngle.y) + " ");
  Serial.println(currentAngle.z);*/

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

