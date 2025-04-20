#include "delay.h"
#include "main.h"

// XXX
void delay_us(uint32_t nus)
{
    HAL_Delay(1);
}

void delay_ms(uint16_t nms)
{
    HAL_Delay(nms);
}