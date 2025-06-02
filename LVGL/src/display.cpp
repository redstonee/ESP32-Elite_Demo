#include <TFT_eSPI.h>
#include <lvgl.h>

#include "display.h"
#include "config.h"

namespace Display
{
    static TFT_eSPI screen;

    /*LVGL draw into this buffer, 1/10 screen size usually works well. The size is in bytes*/
    constexpr auto DRAW_BUF_SIZE = (TFT_WIDTH * TFT_HEIGHT * (LV_COLOR_DEPTH / 8) / 10);
    static uint32_t draw_buf[DRAW_BUF_SIZE / 4];

    /**
     * @brief Custom print function for LVGL logging.
     *
     * @note This function is called by LVGL to print log messages, do not call it manually.
     */
    inline void printLog(lv_log_level_t level, const char *buf)
    {
        LV_UNUSED(level);
        Serial.printf("[%u] LVGL: %s\n", millis(), buf);
    }

    /**
     * @brief Flush the display buffer to the screen.
     *
     * @note This function is called by LVGL to update the display, do not call it manually.
     */
    static void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
    {
        uint32_t w = lv_area_get_width(area);
        uint32_t h = lv_area_get_height(area);

        screen.startWrite();
        screen.setAddrWindow(area->x1, area->y1, w, h);
        screen.pushPixels((uint16_t *)px_map, w * h);
        screen.endWrite();

        lv_disp_flush_ready(disp);
    }

    static lv_key_t lastKeyID;
    static lv_indev_state_t lastKeyState;
    /**
     * @brief Read the keypad status.
     *
     * @note This function is called by LVGL, do not call it manually.
     */
    inline void readKey(lv_indev_t *indev, lv_indev_data_t *data)
    {
        LV_UNUSED(indev);
        data->key = lastKeyID;
        data->state = lastKeyState;
    }

    /**
     * @brief Interrupt handler for button presses.
     *
     * @param args The button pin number passed as an argument.
     * This function reads the button state and sets the lastKeyID and lastKeyState accordingly.
     */
    void buttonHandler(void *args)
    {
        auto pin = (int)args;
        lastKeyState = (digitalRead(pin) == LOW) ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;

        switch (pin)
        {
        case BUTTON1_PIN:
            lastKeyID = LV_KEY_PREV;
            break;

        case BUTTON2_PIN:
            lastKeyID = LV_KEY_ENTER;
            break;

        case BUTTON3_PIN:
            lastKeyID = LV_KEY_NEXT;
            break;
        }
    }

    /**
     * @brief Initialize the display, input device and LVGL.
     *
     * @return lv_indev_t* Pointer to the initialized input device.
     */
    lv_indev_t *init()
    {
        screen.init();
        screen.setRotation(1);
        screen.setSwapBytes(true);

        attachInterruptArg(BUTTON1_PIN, buttonHandler, (void *)BUTTON1_PIN, CHANGE);
        attachInterruptArg(BUTTON2_PIN, buttonHandler, (void *)BUTTON2_PIN, CHANGE);
        attachInterruptArg(BUTTON3_PIN, buttonHandler, (void *)BUTTON3_PIN, CHANGE);

        lv_init();

        /*Set a tick source so that LVGL will know how much time elapsed. */
        lv_tick_set_cb([]
                       { return (uint32_t)millis(); });

        /* register print function for debugging */
        lv_log_register_print_cb(printLog);

        lv_display_t *disp;
        /*Else create a display yourself*/
        disp = lv_display_create(TFT_HEIGHT, TFT_WIDTH);
        lv_display_set_flush_cb(disp, my_disp_flush);
        lv_display_set_buffers(disp, draw_buf, NULL, sizeof(draw_buf), LV_DISPLAY_RENDER_MODE_PARTIAL);

        auto keyPadIndev = lv_indev_create();
        lv_indev_set_type(keyPadIndev, LV_INDEV_TYPE_KEYPAD);
        lv_indev_set_read_cb(keyPadIndev, readKey);

        return keyPadIndev;
    }
} // namespace Display
