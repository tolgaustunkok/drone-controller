#ifndef WIRELESS_H
#define WIRELESS_H

#include <RF24.h>
#include <RF24_config.h>
#include "Structs.h"

class Wireless {
  private:
    RF24 radio;
    uint64_t READ_PIPE = 0xF0F0F0F0AALL;
    uint64_t WRITE_PIPE = 0xF0F0F0F0ABLL;
  public:
    Wireless() : radio(9, 10) {}
    void initialize();
    void pumpData(const debug_data_t* debugData);
    void getMessage(void* otherData, int sizeOfData);
};

#endif

