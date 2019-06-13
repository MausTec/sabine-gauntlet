#include "Transmitter.h"

void Transmitter::Setup() {
  pinMode(TX_E_PIN, OUTPUT);
  digitalWrite(TX_E_PIN, HIGH);
}

void Transmitter::Send(uint8_t address, uint8_t data) {
  SR.Write(data);
  SR.Write(address);
  digitalWrite(TX_E_PIN, LOW);
  delay(100);
  digitalWrite(TX_E_PIN, HIGH);
}

Transmitter TX = Transmitter();