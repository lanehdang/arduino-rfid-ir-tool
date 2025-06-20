//================================================================
//  FILE: ir_functions.cpp
//================================================================

#include "config.h"

//-------------------------------------------------
//              RECEIVE IR HANDLER
//-------------------------------------------------
void handleReceiveIr() {
    // 1. Update display with instructions
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Receiving IR Signal...");
    display.println("Point remote and press a button.");
    display.setCursor(0, 40);
    display.println("> Press SELECT to exit");
    display.display();

    // 2. Check for a decoded IR signal
    if (irReceiver.decode(&irResults)) {
        display.clearDisplay();
        display.setTextSize(1);
        display.setCursor(0, 0);
        
        if (irResults.value == 0) {
            display.println("Signal too weak.");
        } else {
            // 3. Display the received code
            display.println("IR Code Received!");
            display.setCursor(0, 15);
            display.print("Value: ");
            display.println(irResults.value, HEX);
            display.print("Type: ");
            display.println(irReceiver.getProtocolString(irResults.decode_type));

            // 4. Save the code to global variables and EEPROM
            lastIRCodeValue = irResults.value;
            lastIRCodeType = irResults.decode_type;
            EEPROM.put(0, lastIRCodeValue);
            EEPROM.put(sizeof(lastIRCodeValue), lastIRCodeType);
            display.println("\nCode saved!");
        }
        
        display.display();
        irReceiver.resume(); // Prepare for the next value

        // Wait for user to exit
        delay(2000); // Show message for a couple seconds
        currentState = STATE_MAIN_MENU;
    }

    // 5. Check for a "back" button press to return to menu
    if (checkButton(BUTTON_SELECT_PIN)) {
        currentState = STATE_MAIN_MENU;
    }
}

//-------------------------------------------------
//              REPLAY IR HANDLER
//-------------------------------------------------
void handleReplayIr() {
    // 1. Update Display
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    
    if (lastIRCodeValue == 0) {
        display.println("No IR code in memory.");
        display.println("Use 'Receive IR' first.");
    } else {
        display.println("Sending IR Code...");
        display.setCursor(0, 15);
        display.print("Value: ");
        display.println(lastIRCodeValue, HEX);
        display.display();

        // 2. Send the stored IR code
        irSender.send((decode_type_t)lastIRCodeType, lastIRCodeValue, 0);

        // 3. Show confirmation message
        display.setCursor(0, 30);
        display.println("Signal Sent!");
    }
    
    display.display();
    delay(2000); // Show message for a couple of seconds
    currentState = STATE_MAIN_MENU;
}
