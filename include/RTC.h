#ifndef RTC_h
#define RTC_h

#include "../../../../../../Arduino/libraries/RTClib/RTClib.h"
#include "Arduino.h"

#define RTC_TYPE RTC_PCF8523

class rtc {
  public:
    bool Setup();
    uint32_t Unix();
    uint16_t Year();
    uint8_t Month();
    uint8_t Day();
    uint8_t Hour();
    uint8_t Minute();
    uint8_t Second();
    DateTime Now();
    //DateTime::DateTime (uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec)


  void SetMinute(int i);

  void SetHour(int i);

  void SetDay(int i);

  void SetMonth(int i);

  void SetYear(int i);

private:
    RTC_TYPE device;
};

extern rtc RTC;
#endif