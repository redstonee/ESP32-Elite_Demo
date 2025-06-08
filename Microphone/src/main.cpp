#include <Arduino.h>
#include <I2S.h>

#include "config.h"

void setup()
{
    Serial.begin(115200);

    // Configure I2S for digital microphone
    I2S.setAllPins(DMIC_SCK_PIN, DMIC_WS_PIN, DMIC_DAT_PIN, -1, -1);
    I2S.begin(I2S_LEFT_JUSTIFIED_MODE, 16000, 32);

    // Set up the LED pins
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    pinMode(LED3_PIN, OUTPUT);
    pinMode(LED4_PIN, OUTPUT);
}

/**
 * @brief Turn on the LEDs based on the input number.
 *
 * @param n The number of LEDs to turn on (0-4).
 */
void turnOnLED(int n)
{
    digitalWrite(LED4_PIN, n > 0);
    digitalWrite(LED3_PIN, n > 1);
    digitalWrite(LED2_PIN, n > 2);
    digitalWrite(LED1_PIN, n > 3);
}

void loop()
{
    constexpr auto N_SAMPLES = 128;
    int32_t buffer[N_SAMPLES];

    // Read data from the I2S microphone
    auto bytesRead = I2S.read(buffer, sizeof(buffer));
    if (!bytesRead) // No data read
        return;

    // Calculate the mean of the samples
    int32_t mean = 0;
    for (auto sample : buffer)
    {
        mean += sample >> 8; // Scale down the sample value
    }
    mean /= N_SAMPLES;

    // Print the mean value to the serial monitor and you can view it in Teleplot
    Serial.print(">Mic:");
    Serial.println(mean);

    // Turn on LEDs based on the volume
    turnOnLED(abs(mean) / 6000);
}
