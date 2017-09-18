#ifndef SENSOR_ARRAY_H
#define SENSOR_ARRAY_H

#include <Adafruit_BMP280.h>
#include <MPU9255.h>

typedef struct {
  float x;
  float y;
  float z;
} gyro_data_t;

class SensorArray {
  private:
    MPU9255 mpu;
    Adafruit_BMP280 bme;
  public:
    bool initialize();
    gyro_data_t getGyroDPS();
    char* getStatus();
};

#endif
