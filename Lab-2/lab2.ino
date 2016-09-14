#include <limits.h>
#include <LiquidCrystal.h>
#include <avr/eeprom.h>

class Eeprom {
  public:
    Eeprom(){}
    byte read(unsigned int uiAddress);
    void write(unsigned int uiAddress, unsigned char data);
};

class Button {
  public:
    Button(unsigned short pin);
    bool hasBeenPushed();
  private:
    unsigned short buttonPin;
    unsigned long debounceDelay;
    unsigned long lastDebounceTime;  
};

const unsigned short EEPROM_START_ADDRESS = 0;
const unsigned short MAX = USHRT_MAX;
const unsigned short MIN = 10000;

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}
