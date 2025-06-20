//================================================================
//  FILE: config.h
//================================================================

#ifndef CONFIG_H
#define CONFIG_H

//-------------------------------------------------
//          1. LIBRARIES & DEFINITIONS
//-------------------------------------------------

// Include base Arduino library
#include <Arduino.h>

// Include project libraries
#include <SPI.h>
#include <MFRC522.h>
#include <IRremote.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>

// Pin Definitions (Adjust to your wiring)
#define RFID_SS_PIN      10   // SPI Slave Select
#define RFID_RST_PIN     9    // RFID Reset Pin
#define IR_RECEIVE_PIN   2    // IR Receiver Input Pin
#define IR_SEND_PIN      3    // PWM pin for IR LED
#define BUTTON_UP_PIN    5
#define BUTTON_DOWN_PIN  6
#define BUTTON_SELECT_PIN 7

// OLED Screen Dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Debounce delay for buttons
#define DEBOUNCE_DELAY 50

//-------------------------------------------------
//              2. STATE ENUMERATION
//-------------------------------------------------
enum State {
    STATE_MAIN_MENU,
    STATE_READ_RFID,
    STATE_RECEIVE_IR,
    STATE_REPLAY_IR,
    STATE_SHOW_INFO
};

//-------------------------------------------------
//        3. GLOBAL VARIABLE DECLARATIONS
//-------------------------------------------------

extern State currentState;
extern MFRC522 rfid;
extern IRrecv irReceiver;
extern IRsend irSender;
extern Adafruit_SSD1306 display;

extern unsigned long lastDebounceTime;
extern int menuSelection;
extern decode_results irResults;
extern unsigned long lastIRCodeValue;
extern int lastIRCodeType;

//-------------------------------------------------
//             4. FUNCTION PROTOTYPES
//-------------------------------------------------

// UI Functions (from ui_functions.cpp)
void handleMainMenu();
void drawMainMenu();
bool checkButton(int buttonPin);

// RFID Functions (from rfid_functions.cpp)
void handleReadRfid();
void displayRfidInfo(byte *buffer, byte bufferSize);

// IR Functions (from ir_functions.cpp)
void handleReceiveIr();
void handleReplayIr();

#endif // CONFIG_H
