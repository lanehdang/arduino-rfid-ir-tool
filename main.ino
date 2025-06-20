//================================================================
//  PROJECT: Arduino RFID & IR Multi-Tool
//  AUTHOR: Le Anh Dang
//  DATE:   21/06/2025
//  VERSION: 1.0
//
//  FILE: main.ino
//
//================================================================

#include "config.h"

//-------------------------------------------------
//        1. GLOBAL VARIABLE DEFINITIONS
//-------------------------------------------------

State currentState = STATE_MAIN_MENU;
MFRC522 rfid(RFID_SS_PIN, RFID_RST_PIN);
IRrecv irReceiver(IR_RECEIVE_PIN);
IRsend irSender; 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

unsigned long lastDebounceTime = 0;
int menuSelection = 0;
decode_results irResults; 
unsigned long lastIRCodeValue = 0; 
int lastIRCodeType = 0;

//-------------------------------------------------
//              2. SETUP FUNCTION
//-------------------------------------------------
void setup() {
    Serial.begin(9600);
    while (!Serial);
    Serial.println("Multi-Tool Starting...");

    Wire.begin();

    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println("System Initialized!");
    display.display();
    delay(1000);

    // Initialize RFID module
    SPI.begin();
    rfid.PCD_Init();
    Serial.println("RFID Reader Initialized.");

    // Initialize IR receiver
    irReceiver.enableIRIn();
    Serial.println("IR Receiver Initialized.");

    // Initialize button pins
    pinMode(BUTTON_UP_PIN, INPUT_PULLUP);
    pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP);
    pinMode(BUTTON_SELECT_PIN, INPUT_PULLUP);
    Serial.println("Buttons Initialized.");

    // Load the last saved IR code from EEPROM
    EEPROM.get(0, lastIRCodeValue);
    EEPROM.get(sizeof(lastIRCodeValue), lastIRCodeType);
    Serial.print("Loaded IR Code from EEPROM: ");
    Serial.println(lastIRCodeValue);
}

//-------------------------------------------------
//                 3. MAIN LOOP
//-------------------------------------------------
void loop() {
    switch (currentState) {
        case STATE_MAIN_MENU:
            handleMainMenu();
            break;
        case STATE_READ_RFID:
            handleReadRfid();
            break;
        case STATE_RECEIVE_IR:
            handleReceiveIr();
            break;
        case STATE_REPLAY_IR:
            handleReplayIr();
            break;
    }
}
