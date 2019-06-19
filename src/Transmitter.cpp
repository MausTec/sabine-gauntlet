#include "Transmitter.h"

void Transmitter::Setup() {
  pinMode(TX_EN_PIN, OUTPUT);
  digitalWrite(TX_EN_PIN, HIGH);
}

void Transmitter::Send(uint8_t address, uint8_t data) {
  // Address are actually inversed on the receiver board,
  // And data uses the control register which seems to be
  // populated backwards (also inverse???)
  SR.Write(~address, reverseBits(data));
  
  delay(TX_EN_DELAY);
  digitalWrite(TX_EN_PIN, LOW);
  delay(TX_EN_TIME);
  digitalWrite(TX_EN_PIN, HIGH);
}

uint8_t Transmitter::reverseBits(uint8_t data) {
  uint8_t tmp = data;
  uint8_t out = 0;

  for (int i = 0; i < 8; i++) {
    out <<= 1;
    out |= (tmp & 1);
    tmp >>= 1;
  }

  return out;
}

Transmitter TX = Transmitter();