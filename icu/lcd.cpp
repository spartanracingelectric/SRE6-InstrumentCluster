#include "lcd.h"

U8G2_ST7565_NHD_C12864_F_4W_SW_SPI *lcd;

uint32_t prev_millis_lcd_rpm = 0;

void lcd__init(U8G2_ST7565_NHD_C12864_F_4W_SW_SPI *lcd_ptr)
{
    // Set internal lcd.cpp ptr to whatever is passed into the function
    lcd = lcd_ptr;
    // Begin
    lcd->begin();
}

void lcd__print14(uint8_t x, uint8_t y, char *str)
{
    // Need to implement a way to update ONLY the space that is to be printed
    lcd->clearBuffer();					// clear the internal memory
    
    //Refuses to take in a passed parameter for some reason
    //Bandaid fix to make multiple functions
    lcd->setFont(u8g2_font_helvB14_tr);	// choose a suitable font

    lcd->drawStr(x, y, str);	// write something to the internal memory
    lcd->sendBuffer();					// transfer internal memory to the display
}

void lcd__print18(uint8_t x, uint8_t y, char *str)
{
    // Need to implement a way to update ONLY the space that is to be printed
    lcd->clearBuffer();					// clear the internal memory
    
    //Refuses to take in a passed parameter for some reason
    //Bandaid fix to make multiple functions
    lcd->setFont(u8g2_font_helvB18_tr);	// choose a suitable font
    
    lcd->drawStr(x, y, str);	// write something to the internal memory
    lcd->sendBuffer();					// transfer internal memory to the display
}

void lcd__print24(uint8_t x, uint8_t y, char *str)
{
    // Need to implement a way to update ONLY the space that is to be printed
    lcd->clearBuffer();					// clear the internal memory
    
    //Refuses to take in a passed parameter for some reason
    //Bandaid fix to make multiple functions
    lcd->setFont(u8g2_font_helvB24_tr);	// choose a suitable font
    
    lcd->drawStr(x, y, str);	// write something to the internal memory
    lcd->sendBuffer();					// transfer internal memory to the display
}

void lcd__print_default_screen_template()
{
    char rpm_str[] = "rpm";
    lcd__print14(45, 45, rpm_str);
}

void lcd__print_rpm(uint16_t rpm, uint32_t curr_millis_lcd_rpm)
{
    if (curr_millis_lcd_rpm-prev_millis_lcd_rpm >= LCD_RPM_UPDATE_MS) {
        prev_millis_lcd_rpm = curr_millis_lcd_rpm;

        //RPM up to 5 digits
        uint8_t RPM_MAX_DIGITS = 5;
        char rpm_str_temp[6] = "     ";
        char rpm_str[6] = "     ";
        uint8_t rpm_num_digits = 1;

        //Round to hundreds
        rpm = (rpm/100) * 100;

        if (rpm!=0)
            rpm_num_digits = (int)log10(rpm)+1;

        //clear remaining 1s before reupdating
        if (rpm_num_digits == 4) {
            rpm_str[0] = ' ';
        }
        
        for (uint8_t i = 0; i < rpm_num_digits; i++) {
            rpm_str_temp[i] = rpm%10 + '0';
            rpm/=10;
        }
        for (uint8_t i = 0; i < rpm_num_digits; i++) {
            rpm_str[RPM_MAX_DIGITS-i-1] = rpm_str_temp[i];
        }

        lcd__print24(18, 30, rpm_str);
    }
}