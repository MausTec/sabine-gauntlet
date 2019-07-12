#ifndef TRANSMITTER_h
#define TRANSMITTER_h

#define TX_EN_PIN 7

#define TX_EN_TIME  500 // ms
#define TX_EN_DELAY 0   // us

#include "Arduino.h"
#include <Thread.h>
#include "../ShiftRegister.h"

class Transmitter {
    public:
      void Setup();
      void Send(uint8_t address, uint8_t data);
      void DoLoop(void);

    protected:
      void doBackgroundTask(void);

    private:
      static void runThread(void);
      uint8_t reverseBits(uint8_t data);

      // Transmit in background
      Thread txThread;
      bool txEnabled = false;
};

extern Transmitter TX;
#endif