#include <Arduino.h>

#define LED_PIN 48

void setup()
{
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT); // Set the LED pin as an output
  Serial.begin(115200);     // Start the serial communication at 115200 baud rate
}

int a = 0;
void loop()
{
  // put your main code here, to run repeatedly:
  digitalWrite(LED_PIN, 1); // Turn the LED on
  delay(100);               // Wait for 100 milliseconds
  digitalWrite(LED_PIN, 0); // Turn the LED off
  delay(100);
  digitalWrite(LED_PIN, 1);
  delay(100);
  digitalWrite(LED_PIN, 0);
  delay(500);
  
  a++;                                                             // Increment the counter
  auto timeNow = millis();                                         // Get the current time in milliseconds since the board started
  Serial.printf("[%u] Already run for %d loops!!!\n", timeNow, a); // Print some shit to the serial port

  if (Serial.available())
  {
    String str;
    while (Serial.available())
    {
      char c = Serial.read();
      str += c;
    }
    Serial.println("Received: " + str);
  }
}
