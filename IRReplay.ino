// IRReplay.ino
#include <IRremote.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
extern IRsend irSender;
extern Adafruit_SSD1306 display;
extern State currentState;
extern unsigned long lastIRCode;
extern bool buttonPressedSelect();

IRsend irSender;

void processIRReplay() {
  display.clearDisplay();
  display.setCursor(0,0);
  display.println(F("Replaying IR..."));
  display.display();

  irSender.sendNEC(lastIRCode, 32);
  delay(500);

  display.clearDisplay();
  display.setCursor(0,0);
  display.println(F("Done."));
  display.display();

  if (buttonPressedSelect())
    currentState = STATE_MAIN_MENU;
  delay(500);
}
