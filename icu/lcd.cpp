#include "lcd.h"

U8G2_ST7565_NHD_C12864_F_4W_SW_SPI *lcd;

void lcd__init(U8G2_ST7565_NHD_C12864_F_4W_SW_SPI *lcd_ptr)
{
    // Set internal lcd.cpp ptr to whatever is passed into the function
    lcd = lcd_ptr;
    // Begin
    lcd->begin();
}

void lcd__print14(uint8_t x, uint8_t y, char *str)
{
    //lcd->clearBuffer();					// clear the internal memory
    
    //Refuses to take in a passed parameter for some reason
    //Bandaid fix to make multiple functions
    lcd->setFont(u8g2_font_helvB14_tr);	// choose a suitable font

    lcd->drawStr(x, y, str);	// write something to the internal memory
    lcd->sendBuffer();					// transfer internal memory to the display
}

void lcd__print18(uint8_t x, uint8_t y, char *str)
{
    //lcd->clearBuffer();					// clear the internal memory
    
    //Refuses to take in a passed parameter for some reason
    //Bandaid fix to make multiple functions
    lcd->setFont(u8g2_font_helvB18_tr);	// choose a suitable font
    
    lcd->drawStr(x, y, str);	// write something to the internal memory
    lcd->sendBuffer();					// transfer internal memory to the display
}

void lcd__print24(uint8_t x, uint8_t y, char *str)
{
    //lcd->clearBuffer();					// clear the internal memory
    
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

void lcd__print_rpm(uint16_t rpm)
{
    //RPM up to 5 digits
    char rpm_str[6];
    //Convert uint16_t to str
    sprintf(rpm_str, "%d", rpm);

    lcd__print24(18, 30, rpm_str);
}