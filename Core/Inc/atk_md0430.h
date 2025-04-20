#ifndef __ATK_MD0430_H
#define __ATK_MD0430_H

#include "main.h"
#include "atk_md0430_fsmc.h"
#include <stdint.h>

#define ATK_MD0430_LCD_WIDTH            480
#define ATK_MD0430_LCD_HEIGHT           800

#define ATK_MD0430_USING_TOUCH          1

#define ATK_MD0430_FONT_12              1
#define ATK_MD0430_FONT_16              1
#define ATK_MD0430_FONT_24              1
#define ATK_MD0430_FONT_32              1

#define ATK_MD0430_BL_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

#define ATK_MD0430_BL(x)                do{ x ?                                                                            \
                                            HAL_GPIO_WritePin(ATK_MD0430_BL_GPIO_Port, ATK_MD0430_BL_Pin, GPIO_PIN_SET) :  \
                                            HAL_GPIO_WritePin(ATK_MD0430_BL_GPIO_Port, ATK_MD0430_BL_Pin, GPIO_PIN_RESET); \
                                        }while(0)

typedef enum
{
    ATK_MD0430_LCD_SCAN_DIR_L2R_U2D = 0x0000,
    ATK_MD0430_LCD_SCAN_DIR_L2R_D2U = 0x0080,
    ATK_MD0430_LCD_SCAN_DIR_R2L_U2D = 0x0040,
    ATK_MD0430_LCD_SCAN_DIR_R2L_D2U = 0x00C0,
    ATK_MD0430_LCD_SCAN_DIR_U2D_L2R = 0x0020,
    ATK_MD0430_LCD_SCAN_DIR_U2D_R2L = 0x0060,
    ATK_MD0430_LCD_SCAN_DIR_D2U_L2R = 0x00A0,
    ATK_MD0430_LCD_SCAN_DIR_D2U_R2L = 0x00E0,
} atk_md0430_lcd_scan_dir_t;

typedef enum
{
    ATK_MD0430_LCD_DISP_DIR_0 = 0x00,
    ATK_MD0430_LCD_DISP_DIR_90,
    ATK_MD0430_LCD_DISP_DIR_180,
    ATK_MD0430_LCD_DISP_DIR_270,
} atk_md0430_lcd_disp_dir_t;

typedef enum
{
#if (ATK_MD0430_FONT_12 != 0)
    ATK_MD0430_LCD_FONT_12,
#endif
#if (ATK_MD0430_FONT_16 != 0)
    ATK_MD0430_LCD_FONT_16,
#endif
#if (ATK_MD0430_FONT_24 != 0)
    ATK_MD0430_LCD_FONT_24,
#endif
#if (ATK_MD0430_FONT_32 != 0)
    ATK_MD0430_LCD_FONT_32,
#endif
} atk_md0430_lcd_font_t;

typedef enum
{
    ATK_MD0430_NUM_SHOW_NOZERO = 0x00,
    ATK_MD0430_NUM_SHOW_ZERO,
} atk_md0430_num_mode_t;

#include "atk_md0430_touch.h"

#define ATK_MD0430_WHITE        0xFFFF
#define ATK_MD0430_BLACK        0x0000
#define ATK_MD0430_BLUE         0x001F
#define ATK_MD0430_BRED         0XF81F
#define ATK_MD0430_GRED         0XFFE0
#define ATK_MD0430_GBLUE        0X07FF
#define ATK_MD0430_RED          0xF800
#define ATK_MD0430_MAGENTA      0xF81F
#define ATK_MD0430_GREEN        0x07E0
#define ATK_MD0430_CYAN         0x7FFF
#define ATK_MD0430_YELLOW       0xFFE0
#define ATK_MD0430_BROWN        0XBC40
#define ATK_MD0430_BRRED        0XFC07
#define ATK_MD0430_GRAY         0X8430

#define ATK_MD0430_EOK          0
#define ATK_MD0430_ERROR        1
#define ATK_MD0430_EINVAL       2


uint8_t atk_md0430_init(void);                                                                                                                          /* ATK-MD0430模锟斤拷锟绞硷拷锟� */
uint16_t atk_md0430_get_lcd_width(void);                                                                                                                /* 锟斤拷取ATK-MD0430模锟斤拷LCD锟斤拷锟斤拷 */
uint16_t atk_md0430_get_lcd_height(void);                                                                                                               /* 锟斤拷取ATK-MD0430模锟斤拷LCD锟竭讹拷 */
void atk_md0430_backlight_on(void);                                                                                                                     /* 锟斤拷锟斤拷ATK-MD0430模锟斤拷LCD锟斤拷锟斤拷 */
void atk_md0430_backlight_off(void);                                                                                                                    /* 锟截憋拷ATK-MD0430模锟斤拷LCD锟斤拷锟斤拷 */
void atk_md0430_display_on(void);                                                                                                                       /* 锟斤拷锟斤拷ATK-MD0430模锟斤拷LCD锟斤拷示 */
void atk_md0430_display_off(void);                                                                                                                      /* 锟截憋拷ATK-MD0430模锟斤拷LCD锟斤拷示 */
uint8_t atk_md0430_set_scan_dir(atk_md0430_lcd_scan_dir_t scan_dir);                                                                                    /* 锟斤拷锟斤拷ATK-MD0430模锟斤拷LCD扫锟借方锟斤拷 */
uint8_t atk_md0430_set_disp_dir(atk_md0430_lcd_disp_dir_t disp_dir);                                                                                    /* 锟斤拷锟斤拷ATK-MD0430模锟斤拷LCD锟斤拷示锟斤拷锟斤拷 */
atk_md0430_lcd_scan_dir_t atk_md0430_get_scan_dir(void);                                                                                                /* 锟斤拷取ATK-MD0430模锟斤拷LCD扫锟借方锟斤拷 */
atk_md0430_lcd_disp_dir_t atk_md0430_get_disp_dir(void);                                                                                                /* 锟斤拷取ATK-MD0430模锟斤拷LCD锟斤拷示锟斤拷锟斤拷 */
void atk_md0430_fill(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t color);                                                               /* ATK-MD0430模锟斤拷LCD锟斤拷锟斤拷锟斤拷锟� */
void atk_md0430_clear(uint16_t color);                                                                                                                  /* ATK-MD0430模锟斤拷LCD锟斤拷锟斤拷 */
void atk_md0430_draw_point(uint16_t x, uint16_t y, uint16_t color);                                                                                     /* ATK-MD0430模锟斤拷LCD锟斤拷锟斤拷 */
uint16_t atk_md0430_read_point(uint16_t x, uint16_t y);                                                                                                 /* ATK-MD0430模锟斤拷LCD锟斤拷锟斤拷 */
void atk_md0430_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);                                                          /* ATK-MD0430模锟斤拷LCD锟斤拷锟竭讹拷 */
void atk_md0430_draw_rect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);                                                          /* ATK-MD0430模锟斤拷LCD锟斤拷锟斤拷锟轿匡拷 */
void atk_md0430_draw_circle(uint16_t x, uint16_t y, uint16_t r, uint16_t color);                                                                        /* ATK-MD0430模锟斤拷LCD锟斤拷圆锟轿匡拷 */
void atk_md0430_show_char(uint16_t x, uint16_t y, char ch, atk_md0430_lcd_font_t font, uint16_t color);                                                 /* ATK-MD0430模锟斤拷LCD锟斤拷示1锟斤拷锟街凤拷 */
void atk_md0430_show_string(uint16_t x, uint16_t y, uint16_t width, uint16_t height, char *str, atk_md0430_lcd_font_t font, uint16_t color);            /* ATK-MD0430模锟斤拷LCD锟斤拷示锟街凤拷锟斤拷 */
void atk_md0430_show_xnum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, atk_md0430_num_mode_t mode, atk_md0430_lcd_font_t font, uint16_t color);   /* ATK-MD0430模锟斤拷LCD锟斤拷示锟斤拷锟街ｏ拷锟缴匡拷锟斤拷锟斤拷示锟斤拷位0 */
void atk_md0430_show_num(uint16_t x, uint16_t y, uint32_t num, uint8_t len, atk_md0430_lcd_font_t font, uint16_t color);                                /* ATK-MD0430模锟斤拷LCD锟斤拷示锟斤拷锟街ｏ拷锟斤拷锟斤拷示锟斤拷位0 */
void atk_md0430_show_pic(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t *pic);                                                        /* ATK-MD0430模锟斤拷LCD图片 */


#endif // __ATK_MD0430_H