#ifndef LCD_H
#define LCD_H

#include "stm32c0xx_hal.h"

void lcd_init(I2C_HandleTypeDef *hi2c, uint8_t addr);
void lcd_print_cmd(char cmd);
void lcd_print_data(char data);
void lcd_print_string(char *str);

#endif // LCD_H