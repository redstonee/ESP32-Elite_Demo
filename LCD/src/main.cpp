#include <Arduino.h>
#include <TFT_eSPI.h>

#include "config.h"
TFT_eSPI screen;

static const uint16_t colors[] = {TFT_NAVY, TFT_DARKGREEN, TFT_DARKCYAN, TFT_MAROON,
                                  TFT_PURPLE, TFT_OLIVE, TFT_LIGHTGREY, TFT_DARKGREY,
                                  TFT_BLUE, TFT_GREEN, TFT_CYAN, TFT_RED, TFT_MAGENTA,
                                  TFT_YELLOW, TFT_ORANGE, TFT_GREENYELLOW, TFT_PINK, TFT_WHITE,
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
  screen.setTextColor(TFT_BLACK, color); // Set text color to white with the background color
  screen.setCursor(10, 10);
  screen.print(n);
}

void setup()
{
  // put your setup code here, to run once:

  // Initialize the TFT screen
  screen.init();
  screen.setRotation(1);        // Set the rotation of the screen
  screen.fillScreen(colors[0]); // Fill the screen with the first color
  
  screen.setTextFont(2);
  screen.setTextColor(TFT_BLACK, colors[0]);
  screen.setTextSize(2);
  screen.setCursor(10, 10);
  screen.print("0");

  pinMode(BUTTON1_PIN, INPUT);
  pinMode(BUTTON2_PIN, INPUT);
  pinMode(BUTTON3_PIN, INPUT);
}

/**
 * @brief Check if a button is pressed
 *
 * @param pin The pin number of the button
 * @return true if the button is pressed, false otherwise
 */
inline bool isPressed(uint8_t pin)
{
  // Buttons are active low, so we check if the pin reads LOW
  return digitalRead(pin) == LOW;
}

void loop()
{
  static uint8_t colorIndex = 0;
  static int n = 0;

  // Check if any button was pressed and handle the corresponding action
  if (isPressed(BUTTON1_PIN))
  {
    showNumber(++n, colors[colorIndex]);

    while (isPressed(BUTTON1_PIN))
    {
      delay(10); // Wait for the button to be released
    }
  }

  if (isPressed(BUTTON2_PIN))
  {
    colorIndex++;
    if (colorIndex >= N_COLORS)
      colorIndex = 0;

    showNumber(n, colors[colorIndex]);

    while (isPressed(BUTTON2_PIN))
    {
      delay(10); // Wait for the button to be released
    }
  }

  if (isPressed(BUTTON3_PIN))
  {
    showNumber(--n, colors[colorIndex]);

    while (isPressed(BUTTON3_PIN))
    {
      delay(10); // Wait for the button to be released
    }
  }

  delay(100);
}
