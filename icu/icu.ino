#include "config.h"
#include "leds.h"
#include "can.h"
#include "lcd.h"

#ifndef ARDUINO_ARCH_RP2040
#error "Select a Raspberry Pi Pico board"
#endif

// LCD Object Initialization
// Args: (U8G2_R0/Rotate, SCK, MOSI, CS, A0/DC, RST)
U8G2_ST7565_NHD_C12864_F_4W_SW_SPI lcd_u8g2(U8G2_R2, PICO_LCD_SPI_SCK, PICO_LCD_SPI_MOSI, PICO_LCD_SPI_CS, PICO_LCD_A0, PICO_LCD_RST);

// LED Object Initialization
// Args: (MAX72XX_HARDWARE_TYPE, CS, NUM_MAX72XX_DEVICES)
// PAROLA_HW refers to an 8x8 LED matrix which we are sort of simulating
MD_MAX72XX leds_md = MD_MAX72XX(MAX72XX_HARDWARE_TYPE, PICO_LED_SPI_CS, 1);

void setup()
{
  //Serial.begin(115200);
  SPI.setSCK(PICO_CAN_SPI_SCK);
  SPI.setTX(PICO_CAN_SPI_MOSI);
  SPI.setRX(PICO_CAN_SPI_MISO);
  SPI.begin();

  // No need to initialize CAB here, as can.begin seems to hog the data
  // buffer which in turn stalls the MAX7219 and therefore the whole program
  
  // Initialize leds, pass U8G2 object pointer
  leds__init(&leds_md);
  // Initialize lcd, pass U8G2 object pointer
  lcd__init(&lcd_u8g2);
  
  //Non functional as clearBuffer in loop overwrites for now
  lcd__print_default_screen_template();
  /*
  //LED Sniffing code
  delay(5000);
  for (uint8_t i = 0; i < 8; i++) {
    for (uint8_t j = 0; j < 8; j++) {
      Serial.println(i);
      Serial.println(j);
      Serial.println();
      leds_md.setPoint(i,j,true);
      delay(2000);
      leds_md.setPoint(i,j,false);
    }
  }
  */
}

//Test values for proof of concept
uint8_t cnt = 0;
uint16_t test_vals[] = {250, 1259, 2400, 3658, 4815, 4405, 4623, 6042, 7404, 9480, 11400, 13004};
uint16_t dly = 500;

void loop()
{
  can__start();
  can__update();
  can__stop();
  leds__rpm_update(test_vals[cnt]);
  lcd__print_rpm(test_vals[cnt]);
  delay(dly);
  cnt++;
  if (cnt == (sizeof(test_vals)/sizeof(test_vals[0]))) {
    cnt = 0;
  }
}
