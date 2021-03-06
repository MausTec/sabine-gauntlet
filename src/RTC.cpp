#include "RTC.h"

bool rtc::Setup() {
  if (! device.begin()) {
#ifdef SERIAL_LOG
    Serial.println(F("Couldn't find RTC"));
#endif
    return false;
  }

  // Set clock
  if (! device.initialized()) {
    // following line sets the RTC to the date & time this sketch was compiled
    device.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

#ifdef SERIAL_LOG
  Serial.println(F("RTC configured."));
#endif
  return true;
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

void rtc::SetMinute(int i) {
  DateTime now = Now();
  DateTime next = DateTime(now.year(), now.month(), now.day(), now.hour(), i, now.second());
  device.adjust(next);
}

void rtc::SetHour(int i) {
  DateTime now = Now();
  DateTime next = DateTime(now.year(), now.month(), now.day(), i, now.minute(), now.second());
  device.adjust(next);
}

void rtc::SetDay(int i) {
  DateTime now = Now();
  DateTime next = DateTime(now.year(), now.month(), i, now.hour(), now.minute(), now.second());
  device.adjust(next);
}

void rtc::SetMonth(int i) {
  DateTime now = Now();
  DateTime next = DateTime(now.year(), i, now.day(), now.hour(), now.minute(), now.second());
  device.adjust(next);
}

void rtc::SetYear(int i) {
  DateTime now = Now();
  DateTime next = DateTime(i, now.month(), now.day(), now.hour(), now.minute(), now.second());
  device.adjust(next);
}

rtc RTC = rtc();