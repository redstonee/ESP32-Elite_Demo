#include <Arduino.h>
#include "config.h"

int foo = 0;
/**
 * @brief Handler for button 2 press event
 *
 * This function is called when button 2 is pressed.
 */
void button2Handler()
{
  foo = 0;
  Serial.println("Button 2 pressed!");
}

/**
 * @brief Toggle the core LED
 *
 * @param xTimer The timer handle (unused)
 * @note This function is called by an OS timer to blink the core LED.
 */
void toggleCoreLed(TimerHandle_t)
{
  static bool ledState = false;
  digitalWrite(CORE_LED_PIN, ledState);
  ledState = !ledState;
}

void setup()
{
  // put your setup code here, to run once:

  // Start the serial communication at 115200 baud rate
  Serial.begin(115200);

  // Set the LED pin as output
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);
  pinMode(CORE_LED_PIN, OUTPUT);

  // Set the button pins as input
  pinMode(BUTTON1_PIN, INPUT);
  pinMode(BUTTON2_PIN, INPUT);
  pinMode(BUTTON3_PIN, INPUT);

  // Attach falling edge interrupt to button 2 pin
  attachInterrupt(BUTTON2_PIN, button2Handler, FALLING);

  // Create a timer to blink the core LED every 500ms
  auto ledTimer = xTimerCreate("LED Timer", 500, pdTRUE, nullptr, toggleCoreLed);
  xTimerStart(ledTimer, 0);
}

/**
 * @brief Turn on/off the LEDs based on the value of 'n'.
 *
 * @param n The number of LEDs to turn on (0-4).
 */
void ledShow(int n)
{
  digitalWrite(LED1_PIN, n > 0);
  digitalWrite(LED2_PIN, n > 1);
  digitalWrite(LED3_PIN, n > 2);
  digitalWrite(LED4_PIN, n > 3);
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (!digitalRead(BUTTON1_PIN))
  {
    // Wait for the button to be released
    while (!digitalRead(BUTTON1_PIN))
      delay(10);

    if (foo < 4)
      foo++;
  }

  if (!digitalRead(BUTTON3_PIN))
  {
    // Wait for the button to be released
    while (!digitalRead(BUTTON3_PIN))
      delay(10);

    if (foo > 0)
      foo--;
  }

  // Print the value of 'foo' to the serial monitor
  Serial.print("Value of foo: ");
  Serial.println(foo);

  // Show the value of 'foo' on the LEDs
  ledShow(foo);

  delay(100); // Delay for 1 second
}
