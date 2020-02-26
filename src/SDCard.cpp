//
// Created by eiser on 2/21/2020.
//

#include "Arduino.h"
#include "../config.h"
#include "../include/SDCard.h"
#include <SdFat.h>
#include <UserInterface.h>

bool SDCard::initsd() {
  if (!initialized)
    return false;

  SPI.begin();
  return true;
}

bool SDCard::Setup() {
  pinMode(SD_CS_PIN, OUTPUT);
  digitalWrite(SD_CS_PIN, HIGH);

  if (!sd.begin(SD_CS_PIN, SPI_HALF_SPEED)) {
#ifdef SERIAL_LOG
    Serial.println(F("E_NO_SD"));
    sd.initErrorPrint(&Serial);
#endif
    initialized = false;
    return false;
  } else {
    initialized = true;
  }

  // For some raisin, we need to open and close a file here,
  // otherwise open hangs later??
  SdFile *p = openRoot();
  p->close();

#ifdef SERIAL_LOG
  Serial.println(F("SD_OK"));
#endif
   return true;
}

SdFile* SDCard::open(const char *path) {
  if (!initsd()) {
    return nullptr;
  }

//  auto file = sd.open(path);
#ifdef SERIAL_LOG
//  if (file) {
//    Serial.println(F("FILE_OK"));
//  } else {
//    Serial.println(F("NO_FILE"));
//  }
#endif
//  if (file)
}

SdFile* SDCard::nextFile() {
  if (!initsd()) {
    return nullptr;
  }

  if (file.openNext(sd.vwd(), O_READ)) {
    return &file;
  } else {
    return nullptr;
  }
}

SdFile* SDCard::openRoot() {
  if (!initsd()) {
    return nullptr;
  }

//  sd.vwd()->rewind();
  return nextFile();
}

void SDCard::chdir(char *dirname) {
  if (!initsd()) {
    return;
  }
#ifdef SERIAL_LOG
  Serial.print("chdir: ");
  Serial.println(dirname);
#endif

  if (!sd.vwd()->exists(dirname)) {
#ifdef SERIAL_LOG
    Serial.println("Dir does not exist.");
#endif
    return;
  }

  if (sd.chdir(dirname, true)) {
#ifdef SERIAL_LOG
    Serial.println("chdir complete");
#endif
//    SdFile *p = nextFile();
//    Serial.println("open next file");
//    if (p != nullptr)
//      p->close();
//    Serial.println("and close it?");
  } else {
    // Something bad happened.
    sd.errorPrint();
    initialized = false;
#ifdef SERIAL_LOG
    Serial.println("Uhhh no.");
#endif
  }
}

SDCard Storage = SDCard();