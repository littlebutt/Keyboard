#ifndef __ATK_MD0430_TOUCH_H
#define __ATK_MD0430_TOUCH_H

#include "atk_md0430.h"
#include "atk_md0430_touch_iic.h"

#if (ATK_MD0430_USING_TOUCH != 0)


#define ATK_MD0430_TOUCH_READ_PEN()             HAL_GPIO_ReadPin(ATK_MD0430_TOUCH_PEN_GPIO_Port, ATK_MD0430_TOUCH_PEN_Pin)
#define ATK_MD0430_TOUCH_PEN(x)                 do{ x ?                                                                                            \
                                                    HAL_GPIO_WritePin(ATK_MD0430_TOUCH_PEN_GPIO_Port, ATK_MD0430_TOUCH_PEN_Pin, GPIO_PIN_SET) :    \
                                                    HAL_GPIO_WritePin(ATK_MD0430_TOUCH_PEN_GPIO_Port, ATK_MD0430_TOUCH_PEN_Pin, GPIO_PIN_RESET);   \
                                                }while(0)
#define ATK_MD0430_TOUCH_TCS(x)                 do{ x ?                                                                                            \
                                                    HAL_GPIO_WritePin(ATK_MD0430_TOUCH_TCS_GPIO_Port, ATK_MD0430_TOUCH_TCS_Pin, GPIO_PIN_SET) :    \
                                                    HAL_GPIO_WritePin(ATK_MD0430_TOUCH_TCS_GPIO_Port, ATK_MD0430_TOUCH_TCS_Pin, GPIO_PIN_RESET);   \
                                                }while(0)

typedef enum
{
    ATK_MD0430_TOUCH_IIC_ADDR_14 = 0x14,    /* 0x14 */
    ATK_MD0430_TOUCH_IIC_ADDR_5D = 0x5D,    /* 0x5D */
} atk_md0430_touch_iic_addr_t;

typedef struct
{
    uint16_t x;
    uint16_t y;
    uint16_t size;
} atk_md0430_touch_point_t;

#define ATK_MD0430_TOUCH_EOK                    0
#define ATK_MD0430_TOUCH_ERROR                  1


uint8_t atk_md0430_touch_init(void);
uint8_t atk_md0430_touch_scan(atk_md0430_touch_point_t *point, uint8_t cnt);

#endif /* ATK_MD0430_USING_TOUCH */


#endif