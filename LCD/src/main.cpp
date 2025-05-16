#include <Arduino.h>
#include <TFT_eSPI.h>

#include "config.h"
TFT_eSPI screen;

static const uint16_t colors[] = {TFT_NAVY, TFT_DARKGREEN, TFT_DARKCYAN, TFT_MAROON,
                                  TFT_PURPLE, TFT_OLIVE, TFT_LIGHTGREY, TFT_DARKGREY,
                                  TFT_BLUE, TFT_GREEN, TFT_CYAN, TFT_RED, TFT_MAGENTA,
                                  TFT_YELLOW, TFT_WHITE, TFT_ORANGE, TFT_GREENYELLOW, TFT_PINK,
                                  TFT_BROWN, TFT_GOLD, TFT_SILVER, TFT_SKYBLUE, TFT_VIOLET};

constexpr auto N_COLORS = sizeof(colors) / sizeof(colors[0]);

/**
 * @brief Show a number on the screen with a specific background color
 *
 * @param n The number to display
 * @param color The background color
 */
void showNumber(int n, uint16_t color)
{
  screen.fillScreen(color);
  screen.setCursor(10, 10);
  screen.print(n);
}

void setup()
{
  // put your setup code here, to run once:

  // Initialize serial communication at 115200 baud rate
  Serial.begin(115200);

  // Initialize the TFT screen
  screen.init();
  screen.setTextSize(2);
  screen.setCursor(10, 10);
  screen.print("0");

  static uint8_t colorIndex = 0;
  static int n = 0;

  // A lambda function to change the background color
  // and display the current number
  auto changeColor = []()
  {
    colorIndex++;
    if (colorIndex >= N_COLORS)
      colorIndex = 0;

    showNumber(n, colors[colorIndex]);
  };

  // A lambda function to increase the number
  auto increaseNumber = []()
  {
    showNumber(++n, colors[colorIndex]);
  };

  // A lambda function to decrease the number
  auto decreaseNumber = []()
  {
    showNumber(--n, colors[colorIndex]);
  };

  // Attach interrupts to the buttons
  // The functions will be called when the buttons are pressed
  attachInterrupt(BUTTON1_PIN, increaseNumber, FALLING);
  attachInterrupt(BUTTON2_PIN, changeColor, FALLING);
  attachInterrupt(BUTTON3_PIN, decreaseNumber, FALLING);
}

void loop()
{
  // Nothing to do here
  // The interrupts will handle the button presses
  delay(100);
}
