
void Wireless::pumpData() {
  if (data[0] != '\0') {
    radio.stopListening();
    int len = strlen(data);
    radio.write(data, len);
    radio.startListening();
    memset(data, 0, 32);
    index = 0;
  }
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
  data = new char[32];
  memset(data, 0, 32);
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
  if (index + lengthOfData < 32) {
    strcpy((data + index), otherData);
    index += lengthOfData;
    data[index++] = ',';
  } else {
    tmpData = new char[lengthOfData + 1];
    strcpy(tmpData, otherData);
    pumpData();
    strcpy((data + index), tmpData);
    index += lengthOfData;
    data[index++] = ',';
    delete[] tmpData;
  }
}

Wireless::~Wireless() {
  delete[] data;
}

