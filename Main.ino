// Main.ino
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <IRremote.h>
#include <MFRC522.h>
#include <EEPROM.h>

// Pin defs
#define RFID_SS_PIN       10
#define RFID_RST_PIN      9
#define IR_RECEIVE_PIN    2
#define IR_SEND_PIN       3
#define BUTTON_UP_PIN     4
#define BUTTON_DOWN_PIN   5
#define BUTTON_SELECT_PIN 6

// States
enum State {
  STATE_MAIN_MENU,
  STATE_READ_RFID,
  STATE_RECEIVE_IR,
  STATE_REPLAY_IR
};
State currentState = STATE_MAIN_MENU;

// Shared globals
extern int menuSelection;
extern unsigned long lastIRCode;

// Hardware objects 
extern Adafruit_SSD1306 display;
extern MFRC522 rfid;
extern IRrecv irReceiver;
extern IRsend irSender;

// Module init/process prototypes
void initDisplay();
void drawMainMenu();
void initButtons();
void readButtons();
void initRFID();
void processRFID();
void initIRReceiver();
void processIRReceive();
void processIRReplay();
void loadIRCode();

void setup() {
  Serial.begin(115200);
  initDisplay();
  initButtons();
  initRFID();
  initIRReceiver();
  loadIRCode();
}

void loop() {
  drawMainMenu();
  readButtons();

  switch (currentState) {
    case STATE_READ_RFID:    processRFID();      break;
    case STATE_RECEIVE_IR:   processIRReceive(); break;
    case STATE_REPLAY_IR:    processIRReplay();  break;
    default: /* stay in menu */                break;
  }
}
