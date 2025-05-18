#include <Arduino.h>

#include "config.h"

namespace LED
{
    constexpr uint8_t ledPins[] = {LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN};

    void turnOnLED(uint8_t ledNum)
    {
        for (auto &pin : ledPins)
        {
            digitalWrite(pin, 0);
        }
        digitalWrite(ledPins[ledNum], 1);
    }

    void nextLed(TimerHandle_t)
    {
        static uint8_t n = 0;
        // Blink the LEDs in sequence
        turnOnLED(n++);
        n %= 4;
    }

    void begin()
    {
        for (auto &pin : ledPins)
        {
            pinMode(pin, OUTPUT);
        }

        auto ledTimer = xTimerCreate("LED Timer", pdMS_TO_TICKS(500), true, nullptr, nextLed);
        xTimerStart(ledTimer, 0);
    }

} // namespace LED
