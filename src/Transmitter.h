#ifndef TRANSMITTER_h
#define TRANSMITTER_h

#define TX_E_PIN 11

#include "Arduino.h"
#include "../ShiftRegister.h"

class Transmitter {
    public:
      void Setup();
      void Send(uint8_t address, uint8_t data);
};

extern Transmitter TX;
#endif