#include "Settings.h"

void settings::Load() {
#ifdef SERIAL_LOG
  Serial.print("Settings load: ");
#endif

  size_t offset = 0;

  EEPROM.get(offset, BacklightBrightness);
  offset += sizeof(BacklightBrightness);
  EEPROM.get(offset, TXAddress);
  offset += sizeof(TXAddress);

#ifdef SERIAL_LOG
  Serial.print(offset);
  Serial.println(" bytes read.");
#endif
}

void settings::Save() {
#ifdef SERIAL_LOG
  Serial.println("Settings save: ");
#endif

  size_t offset = 0;

  EEPROM.put(offset, BacklightBrightness);
  offset += sizeof(BacklightBrightness);
  EEPROM.put(offset, TXAddress);
  offset += sizeof(TXAddress);

#ifdef SERIAL_LOG
  Serial.print(offset);
  Serial.println(" bytes written.");
#endif
}

settings Settings = settings();