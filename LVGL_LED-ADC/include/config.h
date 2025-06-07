#pragma once

// The LED on the core board
constexpr auto CORE_LED_PIN = 48;

// ADC1_1 pin
constexpr auto ADC1_PIN = 1;

// Digital microphone(I2S) pins
constexpr auto DMIC_WS_PIN = 2;
constexpr auto DMIC_SCK_PIN = 3;
constexpr auto DMIC_DAT_PIN = 4;

// Button pins
constexpr auto BUTTON1_PIN = 7;
constexpr auto BUTTON2_PIN = 6;
constexpr auto BUTTON3_PIN = 5;

// Dedicated LED pins
constexpr auto LED1_PIN = 11;
constexpr auto LED2_PIN = 10;
constexpr auto LED3_PIN = 9;
constexpr auto LED4_PIN = 8;

// LED matrix(driven by HT7219) pins
constexpr auto MAT_SCK_PIN = 12;
constexpr auto MAT_DAT_PIN = 13;
constexpr auto MAT_LOAD_PIN = 14;

// Serial RGB LED(WS2812)
constexpr auto RGB_LED_PIN = 45;
constexpr auto RGB_NUM = 4; // Number of RGB LEDs

// IMU module(LSM6DS3) pins
constexpr auto IMU_SDA_PIN = 41;
constexpr auto IMU_SCL_PIN = 42;
constexpr auto IMU_INT_PIN = 15;

// Speaker PA(I2S) pins
constexpr auto SPK_EN_PIN = 16;
constexpr auto SPK_WS_PIN = 17;
constexpr auto SPK_BCK_PIN = 18;
constexpr auto SPK_DAT_PIN = 21;

// LCD display pins are defined in the project configuration file (platformio.ini) as macros