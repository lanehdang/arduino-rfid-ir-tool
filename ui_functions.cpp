//================================================================
//  FILE: ui_functions.cpp
//================================================================

#include "config.h"

const char* menuItems[] = {"Read RFID", "Receive IR", "Replay IR"};
const int menuSize = 3;

//-------------------------------------------------
//              MAIN MENU HANDLER
//-------------------------------------------------
void handleMainMenu() {
    drawMainMenu();

    if (checkButton(BUTTON_UP_PIN)) {
        menuSelection--;
        if (menuSelection < 0) {
            menuSelection = menuSize - 1;
        }
    }

    if (checkButton(BUTTON_DOWN_PIN)) {
        menuSelection++;
        if (menuSelection >= menuSize) {
            menuSelection = 0;
        }
    }

    if (checkButton(BUTTON_SELECT_PIN)) {
        switch (menuSelection) {
            case 0:
                currentState = STATE_READ_RFID;
                break;
            case 1:
                currentState = STATE_RECEIVE_IR;
                break;
            case 2:
                currentState = STATE_REPLAY_IR;
                break;
        }
        // Clear display before entering new state
        display.clearDisplay();
        display.display();
    }
}

//-------------------------------------------------
//              DRAW MAIN MENU
//-------------------------------------------------
void drawMainMenu() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(15, 0);
    display.println("MAIN MENU");
    display.drawFastHLine(0, 18, SCREEN_WIDTH, SSD1306_WHITE);

    display.setTextSize(1);
    for (int i = 0; i < menuSize; i++) {
        display.setCursor(10, 25 + (i * 12));
        if (i == menuSelection) {
            display.print("> ");
        } else {
            display.print("  ");
        }
        display.print(menuItems[i]);
    }
    display.display();
}

//-------------------------------------------------
//              BUTTON CHECK HELPER
//-------------------------------------------------
bool checkButton(int buttonPin) {
    bool pressed = false;
    if (digitalRead(buttonPin) == LOW) {
        if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
            pressed = true;
            lastDebounceTime = millis();
        }
    }
    return pressed;
}
