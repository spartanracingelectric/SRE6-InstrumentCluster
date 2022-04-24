#include "leds.h"
#include "can.h"
#include "lcd.h"

#ifndef ARDUINO_ARCH_RP2040
#error "Select a Raspberry Pi Pico board"
#endif

#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW

// LCD Object Initialization
// Args: (U8G2_R0/Rotate, SCK, MOSI, CS, A0/DC, RST)
U8G2_ST7565_NHD_C12864_F_4W_SW_SPI lcd_u8g2(U8G2_R2, PICO_LCD_SPI_SCK, PICO_LCD_SPI_MOSI, PICO_LCD_SPI_CS, PICO_LCD_A0, PICO_LCD_RST);

MD_MAX72XX leds_md = MD_MAX72XX(HARDWARE_TYPE, PICO_LED_SPI_CS, 1);

void setup()
{
  Serial.begin(115200);
  SPI.setSCK(PICO_LED_SPI_SCK);
  SPI.setTX(PICO_LED_SPI_MOSI);
  // Initialize lcd, pass U8G2 object pointer
  leds__init(&leds_md);
  lcd__init(&lcd_u8g2);
  //lcd__print(32, 50, "rpm");
  lcd__print_default_screen_template();
  /*
  //LED Sniffing code (Cause bad routing!!!!)
  delay(5000);
  for (uint8_t i = 0; i < 8; i++) {
    for (uint8_t j = 0; j < 8; j++) {
      Serial.println(i);
      Serial.println(j);
      Serial.println();
      leds_md.setPoint(i,j,true); //LED1
      delay(2000);
      leds_md.setPoint(i,j,false); //LED1
    }
  }
  */
  leds_md.setPoint(0,0,true); //LED1
  delay(1000);
  leds_md.setPoint(0,3,true); //LED4
  delay(1000);
  leds_md.setPoint(1,1,true); //LED7
  delay(1000);
  leds_md.setPoint(1,4,true); //LED10
  delay(1000);
  leds_md.setPoint(4,5,true); //LED11-B
  delay(1000);
  leds_md.setPoint(4,0,true); //LED16-B
  delay(1000);
  leds_md.setPoint(2,5,true); //LED11-R
  delay(1000);
  leds_md.setPoint(2,0,true); //LED16-R
  delay(1000);
  leds_md.setPoint(3,5,true); //LED11-G
  delay(1000);
  leds_md.setPoint(3,0,true); //LED16-G
  delay(1000);
}

char str0[] = "12000";
char str1[] = "12333";
char str2[] = "12666";
uint8_t cnt = 0;
uint16_t dly = 400;

void loop()
{
  lcd__print_rpm(12000);
  delay(dly);
  lcd__print_rpm(12333);
  delay(dly);
  lcd__print_rpm(12666);
  delay(dly);
}
