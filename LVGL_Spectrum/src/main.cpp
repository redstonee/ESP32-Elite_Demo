#include <Arduino.h>
#include <I2S.h>
#include <lvgl.h>
#include <ArduinoFFT.h>

#include "display.h"
#include "config.h"

constexpr auto N_SAMPLES = 64;      // Number of samples for FFT
constexpr auto SAMPLE_RATE = 16000; // Sample rate in Hz

static float fftReal[N_SAMPLES]; // Real part of the FFT
static float fftImag[N_SAMPLES]; // Imaginary part of the FFT
static bool fftReady = false;    // Flag to indicate if FFT is ready

static lv_obj_t *chart;
static int chartData[N_SAMPLES / 2];

void fftTask(void *arg)
{
  ArduinoFFT<float> fft(fftReal, fftImag, N_SAMPLES, SAMPLE_RATE);

  int32_t micBuffer[N_SAMPLES];
  while (true)
  {
    // Read data from the I2S microphone
    auto bytesRead = I2S.read(micBuffer, sizeof(micBuffer));
    if (bytesRead)
    {
      // Copy the samples to the FFT input
      for (size_t i = 0; i < N_SAMPLES; i++)
      {
        fftReal[i] = micBuffer[i] >> 8; // Scale down and copy
        fftImag[i] = 0.0f;              // Imaginary part is zero for real input
      }

      // Perform FFT
      fft.dcRemoval();
      fft.windowing(FFTWindow::Hamming, FFTDirection::Forward);
      fft.compute(FFTDirection::Forward);
      fft.complexToMagnitude();
      fftReady = true;
    }
    delay(10); // Delay to avoid busy-waiting
  }
}

void setup()
{
  Serial.begin(115200);
  Display::init();

  // Configure I2S for digital microphone
  I2S.setAllPins(DMIC_SCK_PIN, DMIC_WS_PIN, DMIC_DAT_PIN, -1, -1);
  I2S.begin(I2S_LEFT_JUSTIFIED_MODE, SAMPLE_RATE, 32);

  // Create a layout for the chart and scale
  lv_obj_t *layout = lv_obj_create(lv_screen_active());
  lv_obj_remove_style_all(layout);
  lv_obj_set_size(layout, 280, 160);
  lv_obj_set_flex_flow(layout, LV_FLEX_FLOW_COLUMN);
  lv_obj_center(layout);

  // Create a chart to display FFT results
  chart = lv_chart_create(layout);
  lv_obj_set_width(chart, lv_pct(100));
  lv_chart_set_point_count(chart, N_SAMPLES / 2);
  lv_chart_set_type(chart, LV_CHART_TYPE_BAR);
  lv_obj_set_flex_grow(chart, 1);

  // Set the data source for the chart
  auto dataSeries = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_PRIMARY_Y);
  lv_chart_set_ext_y_array(chart, dataSeries, chartData);

  // Add a scale to the chart to display frequency ticks
  auto chartScale = lv_scale_create(layout);
  lv_scale_set_mode(chartScale, LV_SCALE_MODE_HORIZONTAL_BOTTOM);
  lv_obj_set_size(chartScale, lv_pct(100), 20);
  lv_scale_set_range(chartScale, 0, SAMPLE_RATE / 2);
  lv_scale_set_total_tick_count(chartScale, 5);
  lv_scale_set_major_tick_every(chartScale, 1);
  lv_obj_set_style_pad_hor(chartScale, lv_chart_get_first_point_center_offset(chart), 0);

  xTaskCreate(fftTask, "FFT Task", 8192, NULL, 2, NULL);
}

void loop()
{
  // Update the chart with the FFT results
  if (fftReady)
  {

    for (size_t i = 0; i < N_SAMPLES / 2; i++)
    {
      chartData[i] = fftReal[i] / 5000; // Scale down the FFT results for display
    }
    lv_chart_refresh(chart);
    fftReady = false;
  }
  // Handle LVGL tasks
  lv_timer_handler();
  delay(5);
}
