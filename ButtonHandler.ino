// ButtonHandler.ino
extern int menuSelection;
extern State currentState;
extern bool buttonPressedUp();
extern bool buttonPressedDown();
extern bool buttonPressedSelect();

void initButtons() {
  pinMode(BUTTON_UP_PIN,     INPUT_PULLUP);
  pinMode(BUTTON_DOWN_PIN,   INPUT_PULLUP);
  pinMode(BUTTON_SELECT_PIN, INPUT_PULLUP);
}

bool buttonPressedUp()     { return digitalRead(BUTTON_UP_PIN)   == LOW; }
bool buttonPressedDown()   { return digitalRead(BUTTON_DOWN_PIN) == LOW; }
bool buttonPressedSelect() { return digitalRead(BUTTON_SELECT_PIN)== LOW; }

void readButtons() {
  if (buttonPressedUp()) {
    menuSelection = max(0, menuSelection - 1);
    delay(150);
  }
  if (buttonPressedDown()) {
    menuSelection = min(2, menuSelection + 1);
    delay(150);
  }
  if (buttonPressedSelect()) {
    currentState = (State)(STATE_MAIN_MENU + 1 + menuSelection);
    delay(150);
  }
}
