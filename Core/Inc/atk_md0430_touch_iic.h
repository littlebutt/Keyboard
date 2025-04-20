#ifndef __ATK_MD0430_TOUCH_IIC_H
#define __ATK_MD0430_TOUCH_IIC_H

#include "atk_md0430.h"

#if (ATK_MD0430_USING_TOUCH != 0)


#define ATK_MD0430_TOUCH_IIC_SCL(x)                 do{ x ?                                                                                                    \
                                                        HAL_GPIO_WritePin(ATK_MD0430_TOUCH_IIC_SCL_GPIO_Port, ATK_MD0430_TOUCH_IIC_SCL_Pin, GPIO_PIN_SET) :    \
                                                        HAL_GPIO_WritePin(ATK_MD0430_TOUCH_IIC_SCL_GPIO_Port, ATK_MD0430_TOUCH_IIC_SCL_Pin, GPIO_PIN_RESET);   \
                                                    }while(0)

#define ATK_MD0430_TOUCH_IIC_SDA(x)                 do{ x ?                                                                                                    \
                                                        HAL_GPIO_WritePin(ATK_MD0430_TOUCH_IIC_SDA_GPIO_Port, ATK_MD0430_TOUCH_IIC_SDA_Pin, GPIO_PIN_SET) :    \
                                                        HAL_GPIO_WritePin(ATK_MD0430_TOUCH_IIC_SDA_GPIO_Port, ATK_MD0430_TOUCH_IIC_SDA_Pin, GPIO_PIN_RESET);   \
                                                    }while(0)

#define ATK_MD0430_TOUCH_IIC_READ_SDA()             HAL_GPIO_ReadPin(ATK_MD0430_TOUCH_IIC_SDA_GPIO_Port, ATK_MD0430_TOUCH_IIC_SDA_Pin)

#define ATK_MD0430_TOUCH_IIC_EOK    0
#define ATK_MD0430_TOUCH_IIC_ERROR  1

void atk_md0430_touch_iic_init(uint8_t iic_addr);
uint8_t atk_md0430_touch_iic_write_reg(uint16_t reg, uint8_t *buf, uint8_t len);
void atk_md0430_touch_iic_read_reg(uint16_t reg, uint8_t *buf, uint8_t len);

#endif /* ATK_MD0430_USING_TOUCH */


#endif