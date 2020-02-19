#include "Settings.h"

void settings::Load() {
  Serial.print("Settings load: ");

  size_t offset = 0;

  EEPROM.get(offset, BacklightBrightness);
  offset += sizeof(BacklightBrightness);
  EEPROM.get(offset, TXAddress);
  offset += sizeof(TXAddress);

  Serial.print(offset);
  Serial.println(" bytes read.");
}

void settings::Save() {
  Serial.println("Settings save: ");

  size_t offset = 0;

  EEPROM.put(offset, BacklightBrightness);
  offset += sizeof(BacklightBrightness);
  EEPROM.put(offset, TXAddress);
  offset += sizeof(TXAddress);

  Serial.print(offset);
  Serial.println(" bytes written.");
}

settings Settings = settings();