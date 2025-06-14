//================================================================
//          GENERAL CODE FLOW & ARCHITECTURE
//
// This document outlines the software architecture for the
// Arduino RFID & IR Multi-Tool project. The code is structured
// as a state machine to handle different modes of operation cleanly.
//
//================================================================


//-------------------------------------------------
//            1. LIBRARIES & DEFINITIONS
//-------------------------------------------------
#include <SPI.h>          // For RFID communication
#include <MFRC522.h>      // For RFID Reader/Writer
#include <IRremote.h>     // For Infrared communication
#include <Wire.h>         // For I2C communication (OLED)
#include <Adafruit_GFX.h>   // Core graphics library for OLED
#include <Adafruit_SSD1306.h> // Hardware-specific library for OLED
#include <EEPROM.h>       // For saving IR codes permanently

// Pin Definitions (To be decided)
#define RFID_SS_PIN
#define RFID_RST_PIN
#define IR_RECEIVE_PIN
#define IR_SEND_PIN     // PWM pin for IR LED
#define BUTTON_UP_PIN  
#define BUTTON_DOWN_PIN 
#define BUTTON_SELECT_PIN 

//-------------------------------------------------
//       2. GLOBAL VARIABLES & OBJECTS
//-------------------------------------------------

enum State {
    STATE_MAIN_MENU,
    STATE_READ_RFID,
    STATE_RECEIVE_IR,
    STATE_REPLAY_IR,
    STATE_SHOW_INFO // A temporary state to show results
};

State currentState = STATE_MAIN_MENU;

// Hardware Objects
MFRC522 rfid(RFID_SS_PIN, RFID_RST_PIN);
IRrecv irReceiver(IR_RECEIVE_PIN);
IRsend irSender;
Adafruit_SSD1306 display(128, 64, &Wire, -1);

// Global Variables
unsigned long lastDebounceTime = 0;
int menuSelection = 0;
decode_results irResults;
unsigned long lastIRCode = 0;

//-------------------------------------------------
//               3. SETUP FUNCTION
//-------------------------------------------------
void setup() {
    // Start serial communication for debugging purposes

    // Initialize all hardware modules

    // Initialize OLED display

    // Initialize button pins with internal pull-up resistors

    // Load the last saved IR code from EEPROM into our variable
}


//-------------------------------------------------
//                4. MAIN LOOP
//-------------------------------------------------
void loop() {

}


//-------------------------------------------------
//         5. STATE HANDLER FUNCTIONS
// (Each function manages a specific device state)
//-------------------------------------------------

void handleMainMenu() {
    // 1. Draw the menu on the OLED
    // 2. Check for button presses to navigate the menu
    // 3. If the select button is pressed, change the state
}

void handleReadRfid() {
    // 1. Update display
    // 2. Look for new cards
        // 3. If card found, display UID
    // 4. Check for a "back" button press to return to menu
}

void handleReceiveIr() {
    // 1. Update display
    // 2. Check for a decoded IR signal
            // 3. Display the received code
            // 4. Save the code to EEPROM
    // 5. Check for a "back" button press to return to menu
}

void handleReplayIr() {
    // 1. Update Display
    // 2. Send the stored IR code
    // 3. Show confirmation message
}


//-------------------------------------------------
//           6. HELPER/UTILITY FUNCTIONS
//-------------------------------------------------

void drawMainMenu() {
}

