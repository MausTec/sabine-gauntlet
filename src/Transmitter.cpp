#include "Transmitter.h"

void Transmitter::Setup() {
  pinMode(TX_EN_PIN, OUTPUT);
  digitalWrite(TX_EN_PIN, HIGH);

  // Transmit in background
  txThread = Thread();
  txThread.enabled = false;
  txThread.setInterval(TX_EN_TIME);
  txThread.onRun(runThread);
}

void Transmitter::Send(uint8_t address, uint8_t data) {
  // Address are actually inversed on the receiver board,
  // And data uses the control register which seems to be
  // populated backwards (also inverse???)
  SR.Write(~address, reverseBits(data));
  Serial.print("Transmitting: ");
  Serial.print(address, HEX);
  Serial.print(" - ");
  Serial.println(data, HEX);
  txThread.enabled = true;
}

void Transmitter::DoLoop(void) {
  if (txThread.shouldRun()) {
    txThread.run();
  }
}

static void Transmitter::runThread(void) {
  TX.doBackgroundTask();
}

// Private

void Transmitter::doBackgroundTask(void) {
  if (txEnabled) {
    txEnabled = false;
    digitalWrite(TX_EN_PIN, HIGH);
    txThread.enabled = false;
  } else {
    txEnabled = true;
    digitalWrite(TX_EN_PIN, LOW);
  }
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