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
    static void flushScreen(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
    {
        uint32_t w = lv_area_get_width(area);
        uint32_t h = lv_area_get_height(area);

        screen.startWrite();
        screen.setAddrWindow(area->x1, area->y1, w, h);
        screen.pushPixels((uint16_t *)px_map, w * h);
        screen.endWrite();

        lv_disp_flush_ready(disp);
    }

    /**
     * @brief Initialize the display, input device and LVGL.
     *
     * @return lv_indev_t* Pointer to the initialized input device.
     */
    void init()
    {
        screen.init();
        screen.setRotation(1);
        screen.setSwapBytes(true);

        lv_init();

        /*Set a tick source so that LVGL will know how much time elapsed. */
        lv_tick_set_cb([]
                       { return (uint32_t)millis(); });

        /* register print function for debugging */
        lv_log_register_print_cb(printLog);

        lv_display_t *disp;
        /*Else create a display yourself*/
        disp = lv_display_create(TFT_HEIGHT, TFT_WIDTH);
        lv_display_set_flush_cb(disp, flushScreen);
        lv_display_set_buffers(disp, draw_buf, NULL, sizeof(draw_buf), LV_DISPLAY_RENDER_MODE_PARTIAL);
    }
} // namespace Display
