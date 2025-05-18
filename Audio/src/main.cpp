#include <Arduino.h>
#include <vector>
#include <Audio.h>

#include "LED.h"
#include "config.h"

inline bool isPressed(int pin)
{
  return digitalRead(pin) == LOW;
}

Audio speaker;

/**
 * @brief Main task for handling audio playback and button events
 *
 * @param param Pointer to task parameters (not used)
 */
void mainTask(void *param)
{
  const std::vector<String> musicFiles{"/music1.mp3", "/music2.mp3", "/music3.mp3"};
  uint8_t currentFileIndex = 0;

  while (1)
  {
    // Read the ADC value from ADC1_PIN, range 0-4095
    auto adcValue = analogRead(ADC1_PIN);
    speaker.setVolume(adcValue / 200); // Scale down to 0-20 and set volume

    if (isPressed(BUTTON1_PIN))
    {
      // Wait for button release
      while (isPressed(BUTTON1_PIN))
        ;

      // Play the previous track
      currentFileIndex = currentFileIndex == 0 ? musicFiles.size() - 1 : currentFileIndex - 1;
      Serial.printf("Previous track: %d\n", currentFileIndex);
      speaker.connecttoFS(SPIFFS, musicFiles[currentFileIndex].c_str());
    }

    if (isPressed(BUTTON3_PIN))
    {
      // Wait for button release
      while (isPressed(BUTTON3_PIN))
        ;

      // Play the next track
      currentFileIndex = (currentFileIndex + 1) % musicFiles.size();
      Serial.printf("Next track: %d\n", currentFileIndex);
      speaker.connecttoFS(SPIFFS, musicFiles[currentFileIndex].c_str());
    }

    if (isPressed(BUTTON2_PIN))
    {
      // Wait for button release
      while (isPressed(BUTTON2_PIN))
        ;

      // Pause/Resume the audio playback
      Serial.println("Paused/Resumed");
      speaker.pauseResume();
    }
    delay(200); // Delay to avoid rapid volume changes
  }
}

/**
 * @brief Callback function for when the audio file ends
 *
 * @param info The name of the audio file that ended
 *
 * @note This function is called automatically by the Audio library when the audio file ends.
 * @note There's no need to call this function manually.
 */
void audio_eof_mp3(const char *info)
{
  auto fileName = String("/") + info;
  speaker.connecttoFS(SPIFFS, fileName.c_str());
  Serial.print("Looping file: ");
  Serial.println(fileName);
}

void setup()
{
  // put your setup code here, to run once:

  // Initialize serial communication at 115200 baud rate
  Serial.begin(115200);

  pinMode(CORE_LED_PIN, OUTPUT);

  // Configure the audio pins
  speaker.setPinout(SPK_BCK_PIN, SPK_WS_PIN, SPK_DAT_PIN);
  pinMode(SPK_EN_PIN, OUTPUT);
  digitalWrite(SPK_EN_PIN, HIGH); // Enable the speaker amplifier

  // There's only one channel, so enable the mono mode
  speaker.forceMono(true);

  // Initialize the SPIFFS filesystem
  if (!SPIFFS.begin())
  {
    while (1)
    {
      digitalWrite(CORE_LED_PIN, HIGH);
      delay(100);
      digitalWrite(CORE_LED_PIN, LOW);
      delay(100);
    }
  }

  // Initialize the buttons
  pinMode(BUTTON1_PIN, INPUT);
  pinMode(BUTTON2_PIN, INPUT);
  pinMode(BUTTON3_PIN, INPUT);

  xTaskCreate(mainTask, "mainTask", 4096, NULL, 1, NULL);

  // Start the LED effect
  LED::begin();
}

void loop()
{
  // put your main code here, to run repeatedly:
  speaker.loop();
}
