#ifndef MAIN_PAGE_h
#define MAIN_PAGE_h

#include <freeMemory.h>
#include "RTC.h"

class PMainPage : public Pages {
  uint32_t lastRender = millis();

  void Enter() override {
    UI.AddMenuItem(0, F("Props"));
    UI.AddMenuItem(2, F("Calendar"));
    UI.AddMenuItem(1, F("Config"));

    UI.onMenuClick(select);
  }

	void Render() override {
    UI.Title();
    UI.RenderMenu(16, 16);
//    LCD.DrawGraphic(8, 16, 32, 32, PHOENIX);
    renderDate();
	}

  void Loop() override {
    if ((millis() - lastRender) > 1000) {
      renderDate();

      int free = freeMemory();
      double batteryVolts = (float)analogRead(VBAT_PIN) * (5.0 / 1023.0);
      int bat = round(batteryVolts * 100.0);
      char membat[15];
      sprintf_P(membat, PSTR("%-7d %7d"), free, bat);
      Str.Puts(2, 64-6, membat);

      // Battery Levels:
      // 410+ NO BAT
      // 395+ CHARGING
      // 370- DEAD?

//      Serial.print(free);
//      Serial.print(" bytes free, ");
//      Serial.print(batteryVolts);
//      Serial.println(" VDC");
    }
  }

private:

  long readVcc() {
    long result;
    // Read 1.1V reference against AVcc
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
    delay(2); // Wait for Vref to settle
    ADCSRA |= _BV(ADSC); // Convert
    while (bit_is_set(ADCSRA, ADSC));
    result = ADCL;
    result |= ADCH << 8;
    result = 1126400L / result; // Back-calculate AVcc in mV
    return result;
  }

  static void select(UIMenuItem *c) {
    switch(c->value) {
      case 0:
        Pages::Go(&ThermalPage);
        break;
      case 1:
        Pages::Go(&SettingsPage);
        break;
    }
  }

  void renderDate() {
    lastRender = millis();

    // 08 34 19
    char time[9];
    // 2019 02 31
    char date[11];

    sprintf_P(time, PSTR("%02d:%02d:%02d"), RTC.Hour(), RTC.Minute(), RTC.Second());
    sprintf_P(date, PSTR("%02d/%02d"), RTC.Month(), RTC.Day());

    Str.Puts(2, 2, time, true);
    Str.Puts(78, 2, date, true);
  }
};

#endif