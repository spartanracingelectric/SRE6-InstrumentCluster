#ifndef LCD_H_
#define LCD_H_

#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include "config.h"

void lcd__init(U8G2_ST7565_NHD_C12864_F_4W_SW_SPI *lcd_ptr);
void lcd__clear_screen();
void lcd__print8(uint8_t x, uint8_t y, char *str);                 //Print str with Helvetica Bold Size 10
void lcd__print14(uint8_t x, uint8_t y, char *str);                 //Print str with Helvetica Bold Size 14
void lcd__print18(uint8_t x, uint8_t y, char *str);                 //Print str with Helvetica Bold Size 18
void lcd__print24(uint8_t x, uint8_t y, char *str);                 //Print str with Helvetica Bold Size 24
void lcd__print_default_screen_template();
void lcd__print_template();
// C car
void lcd__print_rpm(uint16_t rpm);
void lcd__print_gear(uint8_t gear);
// E car
void lcd__print_hv(uint16_t hv); // accumulator voltage
void lcd__print_soc(uint8_t soc); // State of charge 0-100%
// E & C car
void lcd__print_lv(uint8_t lv); // low voltage battery soc
void lcd__print_etemp(uint8_t etemp); // Accumulator/Engine temperature
void lcd__print_oiltemp(uint8_t oiltemp); // Oil coolant? temperature
void lcd__print_drs(uint8_t drs); // Drag Reduction System: Open or Closed - CAN: 0 or 1
//void lcd_print__tiretemp(uint8_t tiretemp); // Tire temperatures multiple variables?



void lcd__update_screen(uint16_t rpm, uint8_t gear, uint8_t lv, uint8_t etemp, uint8_t oiltemp, uint8_t drs, uint32_t curr_millis_lcd);
void lcd__update_screenE(uint16_t hv, uint8_t soc, uint8_t lv, uint8_t etemp, uint8_t oiltemp, uint8_t drs, uint32_t curr_millis_lcd);


#endif /* LCD_H_ */
