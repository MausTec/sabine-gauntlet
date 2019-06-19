#ifndef TRANSMITTER_h
#define TRANSMITTER_h

#define TX_EN_PIN 7

#define TX_EN_TIME 500
#define TX_EN_DELAY 1000

#include "Arduino.h"
#include "../ShiftRegister.h"

class Transmitter {
    public:
      void Setup();
      void Send(uint8_t address, uint8_t data);

    private:
      uint8_t reverseBits(uint8_t data);
};

extern Transmitter TX;
#endif