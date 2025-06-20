// EEPROMHandler.ino
#include <EEPROM.h>
extern unsigned long lastIRCode;

void loadIRCode() {
  EEPROM.get(0, lastIRCode);
}
