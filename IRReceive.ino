// IRReceive.ino
#include <IRremote.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
extern IRrecv irReceiver;
extern Adafruit_SSD1306 display;
extern State currentState;
extern unsigned long lastIRCode;
extern bool buttonPressedSelect();

IRrecv irReceiver(IR_RECEIVE_PIN);
decode_results irResults;

void initIRReceiver() {
  irReceiver.enableIRIn();
}

void processIRReceive() {
  if (!irReceiver.decode(&irResults)) return;

  lastIRCode = irResults.value;
  EEPROM.put(0, lastIRCode);

  display.clearDisplay();
  display.setCursor(0,0);
  display.print(F("Got IR: 0x"));
  display.println(lastIRCode, HEX);
  display.display();

  irReceiver.resume();
  delay(500);
  currentState = STATE_MAIN_MENU;
}
