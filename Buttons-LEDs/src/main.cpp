#include <Arduino.h>
#include "config.h"

int foo = 0;
void button2Handler()
{
  foo = 0;
  Serial.println("Button 2 pressed!");
}

void blinkCoreLed(TimerHandle_t)
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
  auto ledTimer = xTimerCreate("LED Timer", 500, pdTRUE, nullptr, blinkCoreLed);
  xTimerStart(ledTimer, 0);
}

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
