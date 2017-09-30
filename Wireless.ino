
void Wireless::pumpData(const debug_data_t* debugData) {
  radio.stopListening();
  radio.write(debugData, sizeof(*debugData));
  radio.startListening();
}

void Wireless::initialize() {
  if (!radio.begin()) while (1);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  //radio.setRetries(15, 15); // Reduce timout
  radio.setAutoAck(0);
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

