#ifndef WIRELESS_H
#define WIRELESS_H

#include <RF24.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24_config.h>

class Wireless {
  private:
    RF24 radio;
    uint64_t READ_PIPE = 0xF0F0F0F0AALL;
    uint64_t WRITE_PIPE = 0xF0F0F0F0ABLL;
    char *data;
    int index;
  public:
    Wireless() : radio(9, 10) {}
    ~Wireless();
    void initialize();
    void pumpData();
    void addData(char *otherData);
    void getMessage(void* otherData, int sizeOfData);
};

#endif

