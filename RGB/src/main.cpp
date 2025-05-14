#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "config.h"

Adafruit_NeoPixel rgb(RGB_NUM, RGB_LED_PIN, NEO_GRB + NEO_KHZ800);

// Flags to indicate button presses
bool button1Pressed = false;
bool button2Pressed = false;
bool button3Pressed = false;

/**
 * @brief Interrupt handler for button presses
 * 
 * @param args The argument passed to the interrupt handler, which is the pin number of the button here
 */
void buttonHandler(void *args)
{
  // The argument passed is the pin number of the button
  auto pin = reinterpret_cast<int>(args);

  Serial.printf("Button at pin %d pressed!\n", pin);
  switch (pin)
  {
  case BUTTON1_PIN:
    button1Pressed = true;
    break;
  case BUTTON2_PIN:
    button2Pressed = true;
    break;
  case BUTTON3_PIN:
    button3Pressed = true;
    break;

  default:
    break;
  }
}

void setup()
{
  // put your setup code here, to run once:

  // Start the serial communication at 115200 baud rate
  Serial.begin(115200);

  // Initialize the RGB LEDs
  rgb.begin();
  // Set the brightness of the RGB LEDs to 50 (out of 255)
  rgb.setBrightness(50);
  // Fill the RGB LEDs with white color
  rgb.fill(rgb.Color(255, 255, 255), 0, RGB_NUM);
  // Set the first pixel to a color
  rgb.setPixelColor(0, rgb.ColorHSV(0, 255, 255));
  // Show the changes on the RGB LEDs
  rgb.show();

  // Attach interrupt for the buttons, passing the pin number as an argument
  attachInterruptArg(BUTTON1_PIN, buttonHandler, reinterpret_cast<void *>(BUTTON1_PIN), FALLING);
  attachInterruptArg(BUTTON2_PIN, buttonHandler, reinterpret_cast<void *>(BUTTON2_PIN), FALLING);
  attachInterruptArg(BUTTON3_PIN, buttonHandler, reinterpret_cast<void *>(BUTTON3_PIN), FALLING);
}

/**
 * @brief Function to show the RGB LEDs with a specific color
 *
 * @param n The index of the pixel to change color (while the rest are white)
 * @param hue The hue value for the color
 */
void fuckRGB(uint8_t n, uint16_t hue)
{
  // Fill the RGB LEDs with white color
  rgb.fill(rgb.Color(255, 255, 255), 0, RGB_NUM);

  // Set the pixel at index foo to a color
  rgb.setPixelColor(foo, rgb.ColorHSV(0, 255, 255));

  // Show the changes on the RGB LEDs
  rgb.show();
}

int foo = 0;
uint16_t hue = 0;
void loop()
{
  // put your main code here, to run repeatedly:
  if (button2Pressed)
  {
    // Increment foo and wrap around if it exceeds RGB_NUM
    foo = (foo + 1) % RGB_NUM;

    fuckRGB(foo, hue);
    delay(500);
    // Reset the flag
    button1Pressed = false;
  }

  if (button1Pressed)
  {
    // Increment hue (to change color)
    hue += 256;

    fuckRGB(foo, hue);
    delay(500);
    // Reset the flag
    button2Pressed = false;
  }

  if (button3Pressed)
  {
    // Decrement hue (to change color)
    hue -= 256;

    fuckRGB(foo, hue);
    delay(500);
    // Reset the flag
    button3Pressed = false;
  }

  delay(100); // Small delay to avoid blocking the CPU
}
