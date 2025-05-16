#pragma once

#include "config.h"

// LCD display pins
#define TFT_MOSI 39
#define TFT_SCLK 40
#define TFT_CS 47
#define TFT_DC 38
#define TFT_RST -1
#define TFT_BL 48             // LED back-light control pin
#define TFT_BACKLIGHT_ON HIGH // Level to turn ON back-light (HIGH or LOW)

// Display settings
#define ST7789_DRIVER
#define SPI_FREQUENCY 27000000
#define TFT_RGB_ORDER TFT_BGR
#define TFT_WIDTH 240
#define TFT_HEIGHT 240
#define LOAD_FONT2