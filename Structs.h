#ifndef STRUCTS_H
#define STRUCTS_H

typedef enum {
  CW_FRONT = 0,
  CW_BACK = 1,
  CCW_LEFT = 2,
  CCW_RIGHT = 3
} MOTOR_E;

typedef struct {
  float x;
  float y;
  float z;
} sensor_data_t;

typedef struct {
  sensor_data_t sensorData;
  float altitude;
  float temperature;
  int motorThrusts[4];
  //float pidRoll;
  //float pidPitch;
  float delta;
} debug_data_t;

#endif
