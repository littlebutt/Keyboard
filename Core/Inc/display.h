#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "lvgl.h"
#include "main.h"

typedef struct 
{
    lv_display_t *main_display;
    int width, height;
} display_ctx;


display_ctx display_init();


#endif // __DISPLAY_H