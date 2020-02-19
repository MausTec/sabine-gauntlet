#ifndef TRANSMITTER_h
#define TRANSMITTER_h

#include "Arduino.h"
#include "../config.h"
#include "../../../../../../Arduino/libraries/ArduinoThread/Thread.h"
#include "ShiftRegister.h"

#define TX_EN_TIME  1000 // ms
#define TX_EN_DELAY 0   // us

class Transmitter {
    public:
      void Setup();
      void Send(uint8_t address, uint8_t data);
      void Start(uint8_t address, uint8_t data);
      void Stop();

    private:
      uint8_t reverseBits(uint8_t data);
};

extern Transmitter TX;
#endif