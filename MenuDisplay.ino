// MenuDisplay.ino
#include <Adafruit_SSD1306.h>
extern Adafruit_SSD1306 display;
extern int menuSelection;

Adafruit_SSD1306 display(128, 64, &Wire, -1);
int menuSelection = 0;

void initDisplay() {
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void drawMainMenu() {
  const char* items[] = { "Read RFID", "Receive IR", "Replay IR" };
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = 0; i < 3; i++) {
    if (i == menuSelection) display.print("> ");
    else                   display.print("  ");
    display.println(items[i]);
  }
  display.display();
}
