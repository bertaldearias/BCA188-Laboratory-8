
#include <SPI.h>

const int SPI_SCK = 14;
const int SPI_MOSI = 13;
const int SPI_MISO = 26;
const int SPI_CS = 27;

void setup() {
  Serial.begin(115200);

  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, SPI_CS);

  pinMode(SPI_CS, OUTPUT);
  digitalWrite(SPI_CS, HIGH);
}

void loop() {
  static unsigned long lastTransfer = 0;

  if (millis() - lastTransfer >= 1000) {
    lastTransfer = millis();

    SPI.beginTransaction(
      SPISettings(1000000, MSBFIRST, SPI_MODE0)
    );

    digitalWrite(SPI_CS, LOW);

    uint8_t reply = SPI.transfer(0xA5);

    digitalWrite(SPI_CS, HIGH);
    SPI.endTransaction();

    Serial.print("Sent 0xA5, received 0x");

    if (reply < 0x10) {
      Serial.print("0");
    }

    Serial.println(reply, HEX);
  }
}
