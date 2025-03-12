#include "lcd.h"
#include "i2c.h"

static I2C_HandleTypeDef *lcd;
static uint8_t lcd_addr;

void lcd_print_cmd(char cmd) {
  uint8_t data_u = (cmd & 0xF0);
  uint8_t data_l = ((cmd << 4) & 0xF0);
  uint8_t data[4] = {data_u | 0x0C, data_u | 0x08, data_l | 0x0C, data_l | 0x08};
  HAL_I2C_Master_Transmit(lcd, lcd_addr, data, 4, 10);
}

void lcd_print_data(char data) {
  uint8_t data_u = (data & 0xF0);
  uint8_t data_l = ((data << 4) & 0xF0);
  uint8_t data_arr[4] = {data_u | 0x0D, data_u | 0x09, data_l | 0x0D, data_l | 0x09};
  HAL_I2C_Master_Transmit(lcd, lcd_addr, data_arr, 4, 10);
}

void lcd_init(I2C_HandleTypeDef *hi2c, uint8_t addr) {
  lcd = hi2c;
  lcd_addr = addr << 1;  // Зміщення адреси для HAL

  if (HAL_I2C_IsDeviceReady(lcd, lcd_addr << 1, 3, 100) != HAL_OK) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
  }

  HAL_Delay(50);
  lcd_print_cmd(0x03);
  HAL_Delay(5);
  lcd_print_cmd(0x03);
  HAL_Delay(1);
  lcd_print_cmd(0x03);
  HAL_Delay(10);
  lcd_print_cmd(0x02);  // 4-бітний режим

  lcd_print_cmd(0x28);  // 2 рядки, 5x8 розмір символу
  lcd_print_cmd(0x0C);  // Увімкнути дисплей, вимкнути курсор
  lcd_print_cmd(0x06);  // Інкремент адреси, без зсуву дисплея
  lcd_print_cmd(0x01);  // Очистити дисплей
  HAL_Delay(2);
}

void lcd_print_string(char *str) {
  while (*str) {
    lcd_print_data(*str++);
  }
}

void lcd_print(char *str) {
  lcd_init(&hi2c1, 0x27);  // 0x27 - стандартна адреса LCD через I2C
  lcd_print_string(str);  // Вивід тексту на дисплей
}