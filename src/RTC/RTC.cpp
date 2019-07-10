#include "RTC.h"

void rtc::Setup() {
  if (! device.begin()) {
    Serial.println(F("Couldn't find RTC"));
    while (1);
  }

  // Set clock
  if (! device.initialized()) {
    Serial.println(F("RTC is NOT running!"));
    // following line sets the RTC to the date & time this sketch was compiled
    device.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  Serial.println(F("RTC configured."));
}

DateTime rtc::Now() {
  return device.now();
}

uint32_t rtc::Unix() {
  return this->Now().unixtime();
}

uint16_t rtc::Year() {
  return this->Now().year();
}

uint8_t rtc::Month() {
  return this->Now().month();
}

uint8_t rtc::Day() {
  return this->Now().day();
}

uint8_t rtc::Hour() {
  return this->Now().hour();
}

uint8_t rtc::Minute() {
  return this->Now().minute();
}

uint8_t rtc::Second() {
  return this->Now().second();
}

rtc RTC = rtc();