//
// Created by eiser on 2/21/2020.
//

#include "Arduino.h"
#include "../config.h"
#include "../include/SDCard.h"
#include <SPI.h>
#include <SD.h>
#include <ShiftRegister.h>

File root;

void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

bool SDCard::Setup() {
  pinMode(SD_CS_PIN, OUTPUT);
  digitalWrite(SD_CS_PIN, HIGH);

  if (!SD.begin(SD_CS_PIN)) {
    Serial.println(F("E_NO_SD"));
    SPI.end();
    SR.Setup();
    return false;
  }

  SPI.end();
  SR.Setup();
  return true;
}

SDCard Storage = SDCard();