#include "display.h"
#include "atk_md0430.h"

void _flush_cb(lv_display_t * display, const lv_area_t * area, uint8_t * px_map)
{
    uint16_t * buf16 = (uint16_t *)px_map;
    int32_t x, y;
    for(y = area->y1; y <= area->y2; y++) {
        for(x = area->x1; x <= area->x2; x++) {
            atk_md0430_draw_point(x, y, *buf16);
            buf16++;
        }
    }

    lv_display_flush_ready(display);
}

display_ctx display_init()
{
    lv_init();
    lv_tick_set_cb(HAL_GetTick);
    display_ctx ctx = {0};
    ctx.width = 480;
    ctx.height = 800;
    ctx.main_display = lv_display_create(480, 800);
    static lv_color_t buf[480 * 20];
    lv_display_set_buffers(ctx.main_display, buf, NULL, sizeof(buf), LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_display_set_flush_cb(ctx.main_display, _flush_cb);
    return ctx;
}