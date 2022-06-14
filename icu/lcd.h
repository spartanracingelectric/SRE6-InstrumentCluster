#ifndef LCD_H_
#define LCD_H_

#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include "config.h"

void lcd__init(U8G2_ST7565_NHD_C12864_F_4W_SW_SPI *lcd_ptr); // changed from SW -> HW
void lcd__clear_screen();
void lcd__print8(uint8_t x, uint8_t y, const char *str);                 //Print str with Helvetica Bold Size 10
void lcd__print14(uint8_t x, uint8_t y, const char *str);                 //Print str with Helvetica Bold Size 14
void lcd__print18(uint8_t x, uint8_t y, char *str);                 //Print str with Helvetica Bold Size 18
void lcd__print24(uint8_t x, uint8_t y, char *str);                 //Print str with Helvetica Bold Size 24
void lcd__print_default_screen_template();
void lcd__print_template();
// C car
void lcd__print_rpm(uint16_t rpm);
void lcd__print_gear(uint8_t gear);
void lcd__print_oiltemp(uint8_t oiltemp); // Oil coolant? temperature
// E car
void lcd__print_hv(uint16_t hv); // accumulator voltage
void lcd__print_soc(uint8_t soc); // State of charge 0-100%
void lcd__print_wattemp(uint8_t watertemp); // Water Coolant Temp
// E & C car
void lcd__print_lv(uint8_t lv); // low voltage battery soc
void lcd__print_etemp(uint8_t etemp); // Accumulator/Engine temperature

// 
void lcd__rpm_screen(void); // Change RPM Threshold
void lcd__rpm_G12(void); // Gears 1-2
void lcd__rpm_G23(void); // Gears 2-3
void lcd__rpm_G34(void); // Gears 3-4
void lcd__rpm_G45(void); // Gears 4-5
void lcd__rpm_G56(void); // Gears 5-6
//void lcd_print__tiretemp(uint8_t tiretemp); // Tire temperatures multiple variables?

// Menu stuff
void lcd__menu(void);
void lcd__highlight_screen(uint8_t row, const char* screen);
void lcd__print_screen(uint8_t selection, uint8_t row, char screen); // 5 row + Back template
void lcd__drs_screen(uint8_t drs);

void lcd__update_screen(uint16_t rpm, uint8_t gear, uint8_t lv, uint8_t etemp, uint8_t oiltemp, uint8_t drs, uint32_t curr_millis_lcd);
void lcd__update_screenE(uint16_t hv, uint8_t soc, uint8_t lv, uint8_t etemp, uint8_t oiltemp, uint8_t drs, uint32_t curr_millis_lcd);


#endif /* LCD_H_ */
