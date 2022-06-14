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

#if (POWERTRAIN_TYPE == 'C')
uint16_t rpm = 0;
uint8_t gear = 0;
#else
float hv = 0.0f;
float lv = 0.0f;
#endif

void setup()
{
  pinMode(PICO_CAN_SPI_CS,OUTPUT);
  digitalWrite(PICO_CAN_SPI_CS,HIGH);
  pinMode(PICO_LED_SPI_CS,OUTPUT);
  digitalWrite(PICO_LED_SPI_CS,HIGH);

  //Serial.begin(115200);
#if (BOARD_REVISION == 'A')
  SPI.setSCK(PICO_CAN_SPI_SCK);
  SPI.setTX(PICO_CAN_SPI_MOSI);
  SPI.setRX(PICO_CAN_SPI_MISO);
  SPI.setCS(PICO_CAN_SPI_CS);
  SPI.begin();
#elif (BOARD_REVISION == 'B')
  pinMode(PICO_CAN_RST, OUTPUT);
  digitalWrite(PICO_CAN_RST, HIGH);
  SPI.setSCK(PICO_LED_SPI_SCK);
  SPI.setTX(PICO_LED_SPI_MOSI);
  SPI.setCS(PICO_LED_SPI_CS);
  SPI1.setSCK(PICO_CAN_SPI_SCK);
  SPI1.setTX(PICO_CAN_SPI_MOSI);
  SPI1.setRX(PICO_CAN_SPI_MISO);
  SPI1.setCS(PICO_CAN_SPI_CS);
  SPI.begin();
  SPI1.begin();
#endif

  // No need to initialize CAB here, as can.begin seems to hog the data
  // buffer which in turn stalls the MAX7219 and therefore the whole program
  
  // Initialize leds, pass U8G2 object pointer
  leds__init(&leds_md);
  // Initialize lcd, pass U8G2 object pointer
  lcd__init(&lcd_u8g2);
  
  //Non functional as clearBuffer in loop overwrites for now
  lcd__print_default_screen_template();
  leds__set_brightness(MAX_LED_BRIGHTNESS);
  leds__wake();
#if (BOARD_REVISION == 'B')
  can__start();
#endif
  /*
  //LED Sniffing code
  delay(5000);
  for (uint8_t i = 0; i < 8; i++) {
    for (uint8_t j = 0; j < 8; j++) {
      Serial.println(i);
      Serial.println(j);
      Serial.println();
      leds_md.setPoint(i,j,true);
      delay(1000);
      leds_md.setPoint(i,j,false);
    }
  }
  */
}

//Test values for proof of concept
//uint8_t cnt = 0;
//uint16_t test_vals[] = {109, 250, 1259, 2400, 3658, 4815, 4405, 4623, 6042, 7404, 9480, 11400, 12000, 13004};
//uint16_t test_vals[] = {14600};

void loop()
{
  uint32_t curr_millis = millis();
#if (BOARD_REVISION == 'A')
  can__start();
  delay(10);
#endif
  //can__send_test();
  can__receive();
#if (POWERTRAIN_TYPE == 'C')
  rpm = can__get_rpm();
  gear = can__get_gear();
#else
  hv = can__get_hv();
  lv = can__get_lv();
#endif

#if (BOARD_REVISION == 'A')
  can__stop();
#endif
#if (POWERTRAIN_TYPE == 'C')
  leds__rpm_update_flash(rpm, gear, curr_millis);
  lcd__update_screen(rpm, gear, curr_millis);
#else
  lcd__update_screen(hv, lv, curr_millis);
#endif
  //delay(500);
}
