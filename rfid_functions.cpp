//================================================================
//  FILE: rfid_functions.cpp
//================================================================

#include "config.h"

//-------------------------------------------------
//              READ RFID HANDLER
//-------------------------------------------------
void handleReadRfid() {
    // 1. Update display with instructions
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Reading RFID...");
    display.println("Present a card to scan.");
    display.setCursor(0, 40);
    display.println("> Press SELECT to exit");
    display.display();

    // 2. Look for new cards
    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
        displayRfidInfo(rfid.uid.uidByte, rfid.uid.size);
        
        // Halt RFID operations and wait for user to exit
        rfid.PICC_HaltA();
        rfid.PCD_StopCrypto1();
        
        while(true) {
            if (checkButton(BUTTON_SELECT_PIN)) {
                currentState = STATE_MAIN_MENU;
                break;
            }
        }
    }

    // 4. Check for a "back" button press to return to menu
    if (checkButton(BUTTON_SELECT_PIN)) {
        currentState = STATE_MAIN_MENU;
    }
}


//-------------------------------------------------
//              DISPLAY RFID INFO
//-------------------------------------------------
void displayRfidInfo(byte *buffer, byte bufferSize) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println("Card Found!");
    display.setTextSize(1);
    display.setCursor(0, 20);
    display.print("UID: ");
    for (byte i = 0; i < bufferSize; i++) {
        display.print(buffer[i] < 0x10 ? " 0" : " ");
        display.print(buffer[i], HEX);
    }
    display.println();
    display.setCursor(0, 40);
    display.println("> Press SELECT to exit");
    display.display();
}
