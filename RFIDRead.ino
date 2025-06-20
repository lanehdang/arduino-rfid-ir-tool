// RFIDRead.ino
#include <MFRC522.h>
#include <Adafruit_SSD1306.h>
extern MFRC522 rfid;
extern Adafruit_SSD1306 display;
extern State currentState;
extern bool buttonPressedSelect();

MFRC522 rfid(RFID_SS_PIN, RFID_RST_PIN);

void initRFID() {
  SPI.begin();
  rfid.PCD_Init();
}

void processRFID() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  display.clearDisplay();
  display.setCursor(0,0);
  display.print(F("UID: "));
  for (byte i = 0; i < rfid.uid.size; i++) {
    display.print(rfid.uid.uidByte[i], HEX);
  }
  display.display();

  if (buttonPressedSelect())
    currentState = STATE_MAIN_MENU;

  delay(500);  // simple debounce
  rfid.PICC_HaltA();
} 
