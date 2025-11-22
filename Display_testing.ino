#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_EPD.h>

// ----------------------
// ThinkInk Pin Mapping
// ----------------------
#define EPD_SCK     18
#define EPD_MOSI    23
#define EPD_MISO    19

#define EPD_CS      5
#define EPD_DC      16
#define EPD_RESET   17
#define EPD_BUSY    4

SPIClass vspi(VSPI);

Adafruit_SSD1681 display(
  200, 200,
  EPD_DC, EPD_RESET,
  EPD_CS, -1, EPD_BUSY,
  &vspi
);

// ----------------------
// HARD CODED START TIME
// CHANGE THESE VALUES:
// ----------------------
int hourNow = 12;   // starting hour
int minuteNow = 00; // starting minute

unsigned long lastMinuteCheck = 0;
unsigned long lastDisplayUpdate = 0;

const unsigned long ONE_MINUTE_MS = 60000;

// ----------------------
// Update internal clock
// ----------------------
void updateClock() {
  if (millis() - lastMinuteCheck >= ONE_MINUTE_MS) {
    minuteNow++;
    if (minuteNow >= 60) {
      minuteNow = 0;
      hourNow++;
      if (hourNow >= 24) hourNow = 0;
    }
    lastMinuteCheck = millis();
  }
}

// ----------------------
// Draw Time on E-Ink
// ----------------------
void drawTime()
{
  char timeStr[10];
  sprintf(timeStr, "%02d:%02d", hourNow, minuteNow);

  Serial.print("Updating screen: ");
  Serial.println(timeStr);

  display.clearBuffer();
  display.setRotation(0);
  display.setTextColor(EPD_BLACK);

  display.setTextSize(4);
  display.setCursor(30, 80);
  display.print(timeStr);

  display.display();
}

// ----------------------
// Setup
// ----------------------
void setup() {
  Serial.begin(115200);
  delay(300);

  vspi.begin(EPD_SCK, EPD_MISO, EPD_MOSI, EPD_CS);

  Serial.println("Init display...");
  display.begin();

  // first draw
  drawTime();
  lastDisplayUpdate = millis();
  lastMinuteCheck = millis();
}

// ----------------------
// Loop
// ----------------------
void loop() {
  updateClock();  // advance internal time

  // update display every minute
  if (millis() - lastDisplayUpdate >= ONE_MINUTE_MS) {
    drawTime();
    lastDisplayUpdate = millis();
  }

  delay(50);
}














