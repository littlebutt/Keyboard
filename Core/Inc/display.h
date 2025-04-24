#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "lvgl.h"
#include "main.h"

typedef struct 
{
    lv_display_t *main_display;
    lv_indev_t *main_input;
    int width, height;
    int mode; // 1 for num, 0 for fn 
} display_ctx;


display_ctx display_init();
int display_layout(display_ctx ctx);


#endif // __DISPLAY_H