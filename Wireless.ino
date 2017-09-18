
void Wireless::sendInfo(char* message) {
  int len = strlen(message);
  radio.stopListening();
  radio.write(message, len);
  radio.startListening();
}

void Wireless::initialize() {
  radio.begin();
  radio.setRetries(15, 15);
  radio.openReadingPipe(1, READ_PIPE);
  radio.openWritingPipe(WRITE_PIPE);
  delay(300);
}

void Wireless::getMessage(void* data, int sizeOfData) {
  if (radio.available()) {
    radio.read(data, sizeOfData);
  }
}
