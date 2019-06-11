#ifndef ShiftRegister_h
#define ShiftRegister_h

#define SR_EN A3
#define SR_DS 12
#define SR_DC 13
#define SR_TGAP 0
#define SR_TSTR 0

class ShiftRegister {
  public:
    void Setup();
    void Write(uint8_t data);

  private:
    void StrobeHigh(int pin);
};

#endif
