#include "config.h"
#include "leds.h"
#include "can.h"
#include "lcd.h"

#ifndef ARDUINO_ARCH_RP2040
#error "Select a Raspberry Pi Pico board"
#endif

// LCD Object Initialization
// Args: (U8G2_R0/Rotate, SCK, MOSI, CS, A0/DC, RST) clock and data from SW_SPI: PICO_LCD_SPI_SCK, PICO_LCD_SPI_MOSI,
//U8G2_ST7565_NHD_C12864_F_4W_HW_SPI lcd_u8g2(U8G2_R2, PICO_LCD_SPI_CS, PICO_LCD_A0, PICO_LCD_RST);
U8G2_ST7565_NHD_C12864_F_4W_SW_SPI lcd_u8g2(U8G2_R2, PICO_LCD_SPI_SCK, PICO_LCD_SPI_MOSI, PICO_LCD_SPI_CS, PICO_LCD_A0, PICO_LCD_RST);

// LED Object Initialization
// Args: (MAX72XX_HARDWARE_TYPE, CS, NUM_MAX72XX_DEVICES)
// PAROLA_HW refers to an 8x8 LED matrix which we are sort of simulating

MD_MAX72XX leds_md = MD_MAX72XX(MAX72XX_HARDWARE_TYPE, PICO_LED_SPI_CS, 1);

uint16_t rpm = 0;
uint8_t gear = 0;
uint16_t hv = 0; // is it unsigned int 16? since it's supposed to be a float
uint8_t soc = 0;
uint8_t lv = 0;
uint8_t etemp = 0;
uint8_t oiltemp = 0;
uint8_t watertemp = 0;
uint8_t drs = 0;

void setup()
{
  pinMode(PICO_CAN_SPI_CS, OUTPUT);
  digitalWrite(PICO_CAN_SPI_CS, HIGH);
  pinMode(PICO_LED_SPI_CS, OUTPUT);
  digitalWrite(PICO_LED_SPI_CS, HIGH);

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
#elif (BOARD_REVISION == 'A')
  can__start();
  delay(10);
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

  //can__send_test();
  can__receive();

#if(POWERTRAIN_TYPE == 'C')
  rpm = can__get_rpm();
  gear = can__get_gear();
  oiltemp = can__get_oiltemp();
  etemp = can__get_engtemp();    
#elif (POWERTRAIN_TYPE == 'E')
  hv = can__get_hv();
  soc = can__get_soc();
//  wattemp = can__get_wattemp();
  etemp = can__get_acctemp();
#endif

  lv = can__get_lv();
//  drs = can__get_dr);

#if (BOARD_REVISION == 'A')
  can__stop();
#endif

  // temporary values. change later ---
//  rpm = 10000;
//  gear = 6;
//  hv = 250;
//  soc = 88;
//  lv = 145;
//  etemp = 150;
//  oiltemp = 150;
//  watertemp = 70;
//  drs = 1;

  leds__rpm_update_flash(rpm, gear, curr_millis);
  //lcd__print_rpm(rpm, curr_millis);
#if (POWERTRAIN_TYPE == 'C')
    lcd__update_screen(rpm, gear, lv, etemp, oiltemp, drs, curr_millis);
//    lcd__update_screenE(hv, soc, lv, etemp, watertemp, drs, curr_millis);
#elif (POWERTRAIN_TYPE == 'E')
    lcd__update_screenE(hv, soc, lv, etemp, watertemp, drs, curr_millis);
#endif
  //delay(500);
}
