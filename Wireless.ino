
void Wireless::pumpData(const debug_data_t* debugData) {
  radio.stopListening();
  int len = sizeof(*debugData);
  radio.write(debugData, len);
  radio.startListening();
}

void Wireless::initialize() {
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.setRetries(15, 15);
  radio.setAutoAck(1);
  radio.openReadingPipe(1, READ_PIPE);
  radio.openWritingPipe(WRITE_PIPE);
  radio.startListening();
  delay(300);
}

void Wireless::getMessage(void* otherData, int sizeOfData) {
  if (radio.available()) {
    radio.read(otherData, sizeOfData);
  }
}

