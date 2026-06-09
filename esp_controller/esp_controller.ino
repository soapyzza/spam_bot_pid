#include <Arduino.h>
#include <BLEGamepadClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h>
// Display pin mapping
#define TFT_CS 10
#define TFT_DC 12
#define TFT_RST 11
#define TFT_MOSI 6
#define TFT_SCLK 7
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
XboxController controller;
bool wasConnected = false;
void setup() {
Serial.begin(115200);
SPI.begin(TFT_SCLK, -1, TFT_MOSI);
tft.begin();
tft.setRotation(3);  // Landscape, flipped
tft.fillScreen(ILI9341_BLACK);
tft.setTextSize(2);
tft.setTextColor(ILI9341_WHITE);
// Static labels
tft.setCursor(10, 10);  tft.print("LX / LY:");
tft.setCursor(10, 30);  tft.print("RX / RY:");
tft.setCursor(10, 50);  tft.print("LT / RT:");
tft.setCursor(10, 70);  tft.print("Buttons:");
tft.setCursor(10, 90);  tft.print("Bumpers:");
tft.setCursor(10, 110); tft.print("D-pad:");
tft.setCursor(10, 130); tft.print("Center:");
tft.setCursor(10, 160); tft.print("Status:");
controller.begin();
}
void loop() {
if (controller.isConnected()) {
XboxControlsEvent e;
controller.read(e);
// Update connection status only if changed
if (!wasConnected) {
tft.fillRect(120, 160, 180, 20, ILI9341_BLACK);
tft.setCursor(120, 160);
tft.setTextColor(ILI9341_GREEN);
tft.print("Connected");
wasConnected = true;
}
// Update analog stick values
tft.fillRect(120, 10, 180, 20, ILI9341_BLACK);
tft.setCursor(120, 10);
tft.setTextColor(ILI9341_WHITE);
tft.printf("%.2f / %.2f", e.leftStickX, e.leftStickY);
tft.fillRect(120, 30, 180, 20, ILI9341_BLACK);
tft.setCursor(120, 30);
tft.printf("%.2f / %.2f", e.rightStickX, e.rightStickY);
// Triggers
tft.fillRect(120, 50, 180, 20, ILI9341_BLACK);
tft.setCursor(120, 50);
tft.printf("%.2f / %.2f", e.leftTrigger, e.rightTrigger);
// Face buttons
tft.fillRect(120, 70, 180, 20, ILI9341_BLACK);
tft.setCursor(120, 70);
if (e.buttonA) tft.print("A ");
if (e.buttonB) tft.print("B ");
if (e.buttonX) tft.print("X ");
if (e.buttonY) tft.print("Y ");
// Bumpers and stick buttons
tft.fillRect(120, 90, 180, 20, ILI9341_BLACK);
tft.setCursor(120, 90);
if (e.leftBumper)      tft.print("LB ");
if (e.rightBumper)     tft.print("RB ");
if (e.leftStickButton) tft.print("LSB ");
if (e.rightStickButton)tft.print("RSB ");
// D-pad
tft.fillRect(120, 110, 180, 20, ILI9341_BLACK);
tft.setCursor(120, 110);
if (e.dpadUp)    tft.print("Up ");
if (e.dpadDown)  tft.print("Down ");
if (e.dpadLeft)  tft.print("Left ");
if (e.dpadRight) tft.print("Right ");
// Center buttons
tft.fillRect(120, 130, 180, 20, ILI9341_BLACK);
tft.setCursor(120, 130);
if (e.shareButton) tft.print("Share ");
if (e.menuButton)  tft.print("Menu ");
if (e.viewButton)  tft.print("View ");
if (e.xboxButton)  tft.print("Xbox ");
} else {
if (wasConnected) {
tft.fillRect(120, 160, 180, 20, ILI9341_BLACK);
tft.setCursor(120, 160);
tft.setTextColor(ILI9341_RED);
tft.print("Controller not connected");
wasConnected = false;
}
}
delay(100);
}