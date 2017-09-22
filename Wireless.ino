
void Wireless::pumpData() {
  radio.stopListening();
  int len = strlen(data);
  radio.write(data, len);
  radio.startListening();
  memset(data, 0, 100);
  index = 0;
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
  data = new char[100];
  memset(data, 0, 100);
  index = 0;
  delay(300);
}

void Wireless::getMessage(void* otherData, int sizeOfData) {
  if (radio.available()) {
    radio.read(otherData, sizeOfData);
  }
}

void Wireless::addData(char *otherData) {
  int lengthOfData = strlen(otherData);
  strcpy((data + index), otherData);
  index += lengthOfData;
  data[index++] = ',';
}

Wireless::~Wireless() {
  delete[] data;
}

