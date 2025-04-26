#include "display.h"
#include "atk_md0430.h"

extern display_ctx ctx;

void _flush_cb(lv_display_t * display, const lv_area_t * area, uint8_t * px_map)
{
    uint16_t * buf16 = (uint16_t *)px_map;
    int32_t x, y;
    for(y = area->y1; y <= area->y2; y++)
    {
        for(x = area->x1; x <= area->x2; x++)
        {
            atk_md0430_draw_point(x, y, *buf16);
            buf16++;
        }
    }

    lv_display_flush_ready(display);
}

void _input_read(lv_indev_t * indev, lv_indev_data_t * data)
{
    static atk_md0430_touch_point_t point[1];
    
    if (atk_md0430_touch_scan(point, sizeof(point) / sizeof(point[0])) == sizeof(point) / sizeof(point[0]))
    {
        data->point.x = point[0].x;
        data->point.y = point[0].y;
        data->state = LV_INDEV_STATE_PRESSED;
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

void _gesture_event(lv_event_t * e)
{
    // lv_obj_t * screen = lv_event_get_current_target(e);
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_active());
    switch(dir) {
        case LV_DIR_LEFT:
            ctx.mode = ctx.mode ? 0 : 1;
            display_layout(ctx);
            break;
        case LV_DIR_RIGHT:
            ctx.mode = ctx.mode ? 0 : 1;
            display_layout(ctx);
            break;
        default:
            break;
    }
}

const char *btn_map_num[21] = {"/", "Etr", "\n",
                               "+", "-", "*", "\n",
                               "7", "8", "9", "\n",
                               "4", "5", "6", "\n",
                               "1", "2", "3", "\n",
                                "0", "." };
const char *btn_map_fn[19] = {"F1", "F2", "F3", "\n",
                              "F4", "F5", "F6", "\n",
                              "F7", "F8", "F9", "\n",
                              "F10", "F11", "F12", "\n",
                              "Cap", "Ins", "Del"};

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
    ctx.main_input = lv_indev_create();
    lv_indev_set_type(ctx.main_input, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(ctx.main_input, _input_read);
    lv_obj_add_event_cb(lv_screen_active(), _gesture_event, LV_EVENT_GESTURE, NULL);
    ctx.mode = 1;
    return ctx;
}

int display_layout(display_ctx ctx)
{
    lv_obj_t * btnms = lv_buttonmatrix_create(lv_screen_active());
    if (ctx.mode == 1)
    {
        lv_buttonmatrix_set_map(btnms, btn_map_num);
        lv_buttonmatrix_set_button_width(btnms, 1, 2);
        lv_buttonmatrix_set_button_width(btnms, 15, 2);
    }
    else
    {
        lv_buttonmatrix_set_map(btnms, btn_map_fn);
    }
    lv_obj_align(btnms, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_size(btnms, ctx.width, ctx.height - 200);
    lv_obj_align(btnms, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_bg_color(btnms, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_style_border_color(btnms, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_style_text_font(btnms, &lv_font_montserrat_28, LV_PART_MAIN);

    static lv_style_t style_btn;
    lv_style_init(&style_btn);
    lv_style_set_bg_color(&style_btn, lv_color_hex(0x000000));
    lv_style_set_bg_opa(&style_btn, LV_OPA_COVER);
    lv_style_set_text_color(&style_btn, lv_color_hex(0xffffff));
    lv_style_set_border_width(&style_btn, 1);
    lv_style_set_border_color(&style_btn, lv_color_hex(0xffffff));
    lv_obj_add_style(btnms, &style_btn, LV_PART_ITEMS);

    static lv_style_t style_pressed;
    lv_style_init(&style_pressed);
    lv_style_set_bg_color(&style_pressed, lv_color_hex(0xaaaaaa));
    lv_style_set_bg_opa(&style_pressed, LV_OPA_COVER);
    lv_obj_add_style(btnms, &style_pressed, LV_PART_ITEMS | LV_STATE_PRESSED);
    
    return 1;
}