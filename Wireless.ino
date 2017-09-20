
void Wireless::sendInfo(char* message) {
  int len = strlen(message);
  radio.stopListening();
  radio.write(message, len);
  radio.startListening();
  delay(100);
}

void Wireless::initialize() {
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.setAutoAck(1);
  radio.enableAckPayload();
  radio.setRetries(15, 15);
  radio.setPayloadSize(8);
  radio.openReadingPipe(1, READ_PIPE);
  radio.openWritingPipe(WRITE_PIPE);
  radio.startListening();
  delay(300);
}

void Wireless::getMessage(void* data, int sizeOfData) {
  if (radio.available()) {
    radio.read(data, sizeOfData);
  }
}
