#ifndef LCD_H_
#define LCD_H_

#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include "config.h"

void lcd__init(U8G2_ST7565_NHD_C12864_F_4W_SW_SPI *lcd_ptr);
void lcd__clear_screen();
void lcd__print14(uint8_t x, uint8_t y, char *str);                 //Print str with Helvetica Bold Size 14
void lcd__print18(uint8_t x, uint8_t y, char *str);                 //Print str with Helvetica Bold Size 18
void lcd__print24(uint8_t x, uint8_t y, char *str);                 //Print str with Helvetica Bold Size 24
void lcd__print_default_screen_template();
void lcd__print_rpm(uint16_t rpm);
void lcd__print_gear(uint8_t gear);
void lcd__update_screen(uint16_t rpm, uint8_t gear, uint32_t curr_millis_lcd);


#endif /* LCD_H_ */
