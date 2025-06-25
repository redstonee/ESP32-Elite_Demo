#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>

constexpr auto MATRIX_LOAD_PIN = 14;
constexpr auto MATRIX_SDA_PIN = 13;
constexpr auto MATRIX_CLK_PIN = 12;

const auto matrixText = "Goodbye, world!";
const auto textLength = strlen(matrixText);

U8G2_MAX7219_8X8_F_4W_HW_SPI mat(U8G2_MIRROR, MATRIX_LOAD_PIN, U8X8_PIN_NONE);

void setup()
{
  // put your setup code here, to run once:

  // Set the pins and initialize the matrix display
  SPI.begin(MATRIX_CLK_PIN, MATRIX_SDA_PIN, MATRIX_SDA_PIN);
  mat.begin();
  mat.clearBuffer();
  mat.setFont(u8g2_font_5x8_mf);
}

void loop()
{
  // put your main code here, to run repeatedly:

  // Let the text scroll
  auto negX = -(textLength * 5);
  for (auto x = 8; x > negX; x--)
  {
    mat.setCursor(x, 7);
    mat.print(matrixText);
    mat.sendBuffer();
    delay(50);
  }
}