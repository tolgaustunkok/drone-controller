
bool SensorArray::initialize() {
  mpu.init();
  return bme.begin();
}

gyro_data_t SensorArray::getGyroDPS() {
  gyro_data_t data;

  mpu.read_gyro();
  data.x = mpu.gx / 131.0;
  data.y = mpu.gy / 131.0;
  data.z = mpu.gz / 131.0;

  return data;
}

char* SensorArray::getStatus() {
  char* stats = new char[30];
  stats[0] = '\0';

  sprintf(stats, "%lf", bme.readAltitude(1013.25));
  strcat(stats, " m");
  
  return stats;
}

