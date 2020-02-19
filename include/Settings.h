#ifndef _Settings_h
#define _Settings_h

#include "Arduino.h"
#include <EEPROM.h>

class settings {
  public:
    void Load();
    void Save();

    uint8_t BacklightBrightness = 128;
    uint8_t TXAddress = 0;
};

extern settings Settings;
#endif