#ifndef __ATK_MD0430_FSMC_H
#define __ATK_MD0430_FSMC_H

#include "atk_md0430.h"

#include <stdint.h>
#include <cmsis_gcc.h>

#define ATK_MD0430_FSMC_BANK                    FSMC_NORSRAM_BANK4
#define ATK_MD0430_FSMC_BANK_ADDR               (0x6C000000)
#define ATK_MD0430_FSMC_REG_SEL                 (10)
#define ATK_MD0430_FSMC_READ_AST                0x00
#define ATK_MD0430_FSMC_READ_DST                0x0F
#define ATK_MD0430_FSMC_WRITE_AST               0x00
#define ATK_MD0430_FSMC_WRITE_DST               0x01

#define ATK_MD0430_FSMC_CMD_ADDR                (ATK_MD0430_FSMC_BANK_ADDR | (((1U << ATK_MD0430_FSMC_REG_SEL) - 1) << 1))
#define ATK_MD0430_FSMC_DAT_ADDR                (ATK_MD0430_FSMC_BANK_ADDR | ((1U << ATK_MD0430_FSMC_REG_SEL) << 1))

#define ATK_MD0430_FSMC_CMD_REG                 (*(volatile uint16_t *)ATK_MD0430_FSMC_CMD_ADDR)
#define ATK_MD0430_FSMC_DAT_REG                 (*(volatile uint16_t *)ATK_MD0430_FSMC_DAT_ADDR)

static inline void atk_md0430_fsmc_write_cmd(volatile uint16_t cmd)
{
    ATK_MD0430_FSMC_CMD_REG = cmd;
}
static inline void atk_md0430_fsmc_write_dat(volatile uint16_t dat)
{
    ATK_MD0430_FSMC_DAT_REG = dat;
}
static inline void atk_md0430_fsmc_write_reg(volatile uint16_t reg, volatile uint16_t dat)
{
    ATK_MD0430_FSMC_CMD_REG = reg;
    ATK_MD0430_FSMC_DAT_REG = dat;
}
static inline uint16_t atk_md0430_fsmc_read_dat(void)
{
    uint16_t dat;
    
    __NOP();
    __NOP();
    dat = ATK_MD0430_FSMC_DAT_REG;
    
    return dat;
}
#endif