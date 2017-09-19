#ifndef SENSOR_ARRAY_H
#define SENSOR_ARRAY_H

#include <Adafruit_BMP280.h>
#include <MPU9255.h>

typedef struct {
  float x;
  float y;
  float z;
} sensor_data_t;

class SensorArray {
private:
  MPU9255 mpu;
  Adafruit_BMP280 bme;
  sensor_data_t currentAngle;
public:
  bool initialize();
  char* getStatus();
  void updatePositionData(float delta);
  const sensor_data_t& getCurrentAngle();
};

#endif
