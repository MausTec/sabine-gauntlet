#include <lcd.h>
#include <Pages.h>
#include "Transmitter.h"

void Transmitter::Setup() {
  pinMode(TX_EN_PIN, OUTPUT);
  digitalWrite(TX_EN_PIN, HIGH);
}

void Transmitter::Start(uint8_t address, uint8_t data) {
  UI.Modal(F("Transmitting"));
  SR.Write(~address, reverseBits(data));
  digitalWrite(TX_EN_PIN, LOW);
}

void Transmitter::Stop() {
  digitalWrite(TX_EN_PIN, HIGH);
  Pages::Rerender();
}

void Transmitter::Send(uint8_t address, uint8_t data) {
  Start(address, data);
  delay(TX_EN_TIME);
  Stop();
}

// Private

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