#include <Arduino.h>
#include <lvgl.h>

#include "display.h"
#include "config.h"

static lv_obj_t *adcBar;

/**
 * @brief Callback function to handle checkbox state changes.
 *
 * @param e Pointer to the event data.
 * @note This function is called when a checkbox is toggled, does not call it manually.
 */
void handleCheckBox(lv_event_t *e)
{
  lv_obj_t *checkbox = lv_event_get_target_obj(e);

  uint32_t pin = (uint32_t)lv_event_get_user_data(e);
  lv_event_code_t code = lv_event_get_code(e);

  if (lv_obj_get_state(checkbox) & LV_STATE_CHECKED)
  {
    digitalWrite(pin, HIGH);
  }
  else
  {
    digitalWrite(pin, LOW);
  }
}

/**
 * @brief Add UI elements to the screen.
 *
 * @param indev Pointer to the input device for the button group.
 */
void buildUI(lv_indev_t *indev)
{
  adcBar = lv_bar_create(lv_screen_active());
  lv_obj_set_size(adcBar, 300, 20);
  lv_obj_align(adcBar, LV_ALIGN_TOP_MID, 0, 10);
  lv_bar_set_range(adcBar, 0, 1 << 12); // 12-bit ADC range

  auto buttonGroup = lv_group_create();
  lv_indev_set_group(indev, buttonGroup);

  lv_obj_set_flex_flow(lv_screen_active(), LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(lv_screen_active(), LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);

  lv_obj_t *foo;
  foo = lv_checkbox_create(lv_screen_active());
  lv_checkbox_set_text(foo, "LED1");
  lv_obj_add_event_cb(foo, handleCheckBox, LV_EVENT_VALUE_CHANGED, (void *)LED1_PIN);
  lv_group_add_obj(buttonGroup, foo);

  foo = lv_checkbox_create(lv_screen_active());
  lv_checkbox_set_text(foo, "LED2");
  lv_obj_add_event_cb(foo, handleCheckBox, LV_EVENT_VALUE_CHANGED, (void *)LED2_PIN);
  lv_group_add_obj(buttonGroup, foo);

  foo = lv_checkbox_create(lv_screen_active());
  lv_checkbox_set_text(foo, "LED3");
  lv_obj_add_event_cb(foo, handleCheckBox, LV_EVENT_VALUE_CHANGED, (void *)LED3_PIN);
  lv_group_add_obj(buttonGroup, foo);

  foo = lv_checkbox_create(lv_screen_active());
  lv_checkbox_set_text(foo, "LED4");
  lv_obj_add_event_cb(foo, handleCheckBox, LV_EVENT_VALUE_CHANGED, (void *)LED4_PIN);
  lv_group_add_obj(buttonGroup, foo);

  lv_obj_update_layout(foo);
}

void setup()
{
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);

  auto keyPad = Display::init();
  buildUI(keyPad);
}

void loop()
{
  lv_bar_set_value(adcBar, analogRead(ADC1_PIN), LV_ANIM_OFF);
  delay(lv_timer_handler()); /* let this time pass */
}
