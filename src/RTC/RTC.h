#ifndef RTC_h
#define RTC_h

#include <RTClib.h>
#include "Arduino.h"

#define RTC_TYPE RTC_PCF8523

class rtc {
  public:
    void Setup(void);
    uint32_t Unix(void);
    uint16_t Year(void);
    uint8_t Month(void);
    uint8_t Day(void);
    uint8_t Hour(void);
    uint8_t Minute(void);
    uint8_t Second(void);
    DateTime Now(void);
    //DateTime::DateTime (uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec)


  private:
    RTC_TYPE device;
};

extern rtc RTC;
#endif