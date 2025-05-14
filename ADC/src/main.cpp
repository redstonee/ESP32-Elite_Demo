#include <Arduino.h>
#include "config.h"

const uint32_t ledPins[]{LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN};
constexpr auto LED_NUM = sizeof(ledPins) / sizeof(ledPins[0]);

uint16_t adcValue = 0;

/**
 * @brief Task to blink LEDs in a round-robin fashion
 *
 * @param param Pointer to task parameters (not used)
 * @note This task runs in a loop, blinking each LED in sequence.
 */
void blinkLEDTask(void *param)
{
  auto ledIndex = 0;
  while (1)
  {
    for (auto &pin : ledPins)
    {
      digitalWrite(pin, 0);
    }

    digitalWrite(ledPins[ledIndex], 1);
    ledIndex = (ledIndex + 1) % LED_NUM;

    // Delay for a time based on the ADC value or a minimum of 20ms
    if (adcValue > 20)
      delay(adcValue);
    else
      delay(20);
  }
}

void setup()
{
  // put your setup code here, to run once:

  // Initialize serial communication at 115200 baud rate
  Serial.begin(115200);

  // Set the LED pins as output
  for (auto &pin : ledPins)
  {
    pinMode(pin, OUTPUT);
  }

  // Create a task to blink LEDs
  xTaskCreate(blinkLEDTask, "Blink LED Task", 2048, nullptr, 1, nullptr);
}

void loop()
{
  // put your main code here, to run repeatedly:

  // Read the ADC value from ADC1_PIN, range 0-4095
  adcValue = analogRead(ADC1_PIN);
  // Or read the voltage in millivolts
  auto voltage = analogReadMilliVolts(ADC1_PIN);

  // Print the ADC value and voltage via Serial
  Serial.printf("ADC Value: %u, Voltage: %u mV\n", adcValue, voltage);

  delay(100);
}
