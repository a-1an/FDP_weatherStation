#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Wire.begin();
  display.begin(i2c_Address, true);
  delay(2000);
  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);
}

void loop() {
  display.clearDisplay();
  
  // display hello world
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Hello, World!");
  
  display.display();
}
