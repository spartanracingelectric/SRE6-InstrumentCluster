#include <U8g2lib.h>
#include "lcd.h"

U8G2_ST7565_NHD_C12864_F_4W_SW_SPI *lcd; // changed from SW -> HW

uint32_t prev_millis_lcd = 0;

// LCD Set-up --------------------------------------------------------------- ---------------------------------------------------------------
void lcd__init(U8G2_ST7565_NHD_C12864_F_4W_SW_SPI *lcd_ptr) // changed from SW -> HW
{
  // Set internal lcd.cpp ptr to whatever is passed into the function
  lcd = lcd_ptr;
  // Begin
  lcd->begin();
}

void lcd__clear_screen() {
  lcd->clearBuffer();
}

void lcd__print8(uint8_t x, uint8_t y, const char *str)
{
  // Need to implement a way to update ONLY the space that is to be printed
  //lcd->clearBuffer();          // clear the internal memory

  //Refuses to take in a passed parameter for some reason
  //Bandaid fix to make multiple functions
  lcd->setFont(u8g2_font_helvB08_tr); // choose a suitable font

  lcd->drawStr(x, y, str);  // write something to the internal memory
  lcd->sendBuffer();          // transfer internal memory to the display
}

void lcd__print14(uint8_t x, uint8_t y, const char *str)
{
  // Need to implement a way to update ONLY the space that is to be printed
  //lcd->clearBuffer();					// clear the internal memory

  //Refuses to take in a passed parameter for some reason
  //Bandaid fix to make multiple functions
  lcd->setFont(u8g2_font_helvB14_tr);	// choose a suitable font

  lcd->drawStr(x, y, str);	// write something to the internal memory
  lcd->sendBuffer();					// transfer internal memory to the display
}

void lcd__print18(uint8_t x, uint8_t y, char *str)
{
  // Need to implement a way to update ONLY the space that is to be printed
  //lcd->clearBuffer();					// clear the internal memory

  //Refuses to take in a passed parameter for some reason
  //Bandaid fix to make multiple functions
  lcd->setFont(u8g2_font_helvB18_tr);	// choose a suitable font
  //lcd->setFont(u8g2_font_luRS18_tr); // lucida monospaced font for rpm?

  lcd->drawStr(x, y, str);	// write something to the internal memory
  lcd->sendBuffer();					// transfer internal memory to the display
}

void lcd__print24(uint8_t x, uint8_t y, char *str)
{
  // Need to implement a way to update ONLY the space that is to be printed
  //lcd->clearBuffer();					// clear the internal memory

  //Refuses to take in a passed parameter for some reason
  //Bandaid fix to make multiple functions
  lcd->setFont(u8g2_font_helvB24_tr);	// choose a suitable font

  lcd->drawStr(x, y, str);	// write something to the internal memory
  lcd->sendBuffer();					// transfer internal memory to the display
}

void lcd__print_default_screen_template()
{
  char default_str[] = "CARS 3";
  lcd__print14(25, 45, default_str);
}

// Combustion Car --------------------------------------------------------------- ---------------------------------------------------------------
void lcd__print_rpm(uint16_t rpm)
{
  //RPM up to 5 digits
  uint8_t RPM_MAX_DIGITS = 5;
  char rpm_str_temp[6] = "     ";
  char rpm_str[6] = "     ";
  uint8_t rpm_num_digits = 1;

  //Round to hundreds
  rpm = (rpm / 100) * 100;
  rpm_num_digits = (int)log10(rpm) + 1;

  //clear remaining 1s before reupdating
  if (rpm_num_digits == 4) {
    rpm_str[0] = ' ';
  }

  for (uint8_t i = 0; i < rpm_num_digits; i++) {
    rpm_str_temp[i] = rpm % 10 + '0';
    rpm /= 10;
  }
  for (uint8_t i = 0; i < rpm_num_digits; i++) {
    rpm_str[RPM_MAX_DIGITS - i - 1] = rpm_str_temp[i];
  }
  lcd__print8(128 - 20, 18, "rpm");
  lcd__print18(35, 18, rpm_str);
}

void lcd__print_gear(uint8_t gear)
{
  char gear_str[4] = "\0";
  //gear is uint8_t, so no negative values expected
  //We only need to compare for gear values past 6
  //If gear out of range
  if (gear > 6) {
    strcpy(gear_str, "ERR");
  }
  else {
    //Print gear (turn int into char first)
    //We can assume gear is one digit based on first conditional
    gear_str[0] = gear + '0';
  }
  lcd__print8(52, 37, "Gear");
  lcd__print24((128 - 16) / 2, 64, gear_str);
}

void lcd__print_oiltemp(uint8_t oiltemp) // Oil coolant? temperature
{
  uint8_t oil_MAX_DIGITS = 3;
  uint8_t oil_num_digits;
  char oil_str[4] = "\0";
  char oil_str_temp[4] = "   ";

  oil_num_digits = (int)log10(oiltemp) + 1;

  if (oil_num_digits == 2) {
    oil_str[0] = ' ';
  }

  for (int i = 0; i < oil_num_digits; i++) {
    oil_str_temp[i] = oiltemp % 10 + '0';
    oiltemp = oiltemp / 10;
  }
  for (uint8_t i = 0; i < oil_num_digits; i++) {
    oil_str[oil_MAX_DIGITS - i - 1] = oil_str_temp[i];
  }

  lcd__print8(0, 50, "Oil T");
  lcd__print14(0, 64, oil_str);
}

// E & C car --------------------------------------------------------------- ---------------------------------------------------------------
void lcd__print_lv(uint8_t lv) // low voltage battery soc
{
  //lv up to 3 digits + '.';
  uint8_t lv_MAX_DIGITS = 4;
  char lv_str_temp[5] = "    ";
  char lv_str[5] = "    ";

  //  //Regain decimals: 100 -> 10.0 V
  //  lv = lv/10;

  // Convert to string
  for (uint8_t i = 0; i < lv_MAX_DIGITS; i++) {
    if (i == 1) {
      lv_str_temp[i] = '.';
      continue;
    }
    lv_str_temp[i] = lv % 10 + '0';
    lv /= 10;
  }

  // Reorder string_temp
  for (uint8_t i = 0; i < lv_MAX_DIGITS; i++) {
    if (lv_str_temp[lv_MAX_DIGITS - 1] == '0' && i == lv_MAX_DIGITS - 1) {
      lv_str[0] = ' ';
      continue;
    }
    lv_str[lv_MAX_DIGITS - i - 1] = lv_str_temp[i];
  }

  lcd__print8(114, 64 - 15, "LV");
  lcd__print14(94, 64, lv_str);
}

void lcd__print_etemp(uint8_t etemp) // Accumulator/Engine temperature
{
  uint8_t etemp_MAX_DIGITS = 3;
  uint8_t etemp_num_digits;
  char etemp_str[4] = "\0";
  char etemp_str_temp[4] = "   ";

  etemp_num_digits = (int)log10(etemp) + 1;

  for (int i = 0; i < etemp_num_digits; i++) {
    etemp_str_temp[i] = etemp % 10 + '0';
    etemp = etemp / 10;
  }
  for (uint8_t i = 0; i < etemp_num_digits; i++) {
    etemp_str[etemp_MAX_DIGITS - i - 1] = etemp_str_temp[i];
  }

  lcd__print8(0, 20, "Eng T");
  lcd__print14(0, 36, etemp_str);
}

void lcd__print_drs(uint8_t drs) // DRS Open or Closed: 0 or 1
{
  lcd__print8(90, 64 - 26, "DRS");
  if (drs == 0)
  {
    lcd__print14(113, 64, "O");
  }
  else if (drs == 1)
  {
    lcd__print14(113, 64 - 26, "M");
  }
  else if (drs == 2)
  {
    lcd__print14(113, 64, "A");
  }
  else if (drs == 3)
  {
    lcd__print14(113, 64 - 30, "C");
  }

}

// Electric car --------------------------------------------------------------- ---------------------------------------------------------------
void lcd__print_hv(uint16_t hv) // accumulator voltage (comes in float or integer?)
{
  //RPM up to 3 digits
  uint8_t HV_MAX_DIGITS = 3;
  char hv_str_temp[4] = "   ";
  char hv_str[4] = "   ";
  uint8_t hv_num_digits = 1;

  if (hv != 0)
    hv_num_digits = (int)log10(hv) + 1;

  //clear remaining 1s before reupdating
  if (hv_num_digits == 2) {
    hv_str[0] = ' ';
  }

  for (uint8_t i = 0; i < hv_num_digits; i++) {
    hv_str_temp[i] = hv % 10 + '0';
    hv /= 10;
  }
  for (uint8_t i = 0; i < hv_num_digits; i++) {
    hv_str[HV_MAX_DIGITS - i - 1] = hv_str_temp[i];
  }

  lcd__print8(102, 18, "volts");
  lcd__print18(46, 18, hv_str);
}

void lcd__print_soc(uint8_t soc) // State of charge 0-100%
{
  //soc up to 3 digits
  uint8_t SOC_MAX_DIGITS = 3;
  char soc_str_temp[4] = "   ";
  char soc_str[4] = "   ";
  uint8_t soc_num_digits = 1;

  if (soc != 0)
    soc_num_digits = (int)log10(soc) + 1;

  //clear remaining 1s before reupdating
  if (soc_num_digits == 2) {
    soc_str[0] = ' ';
  }

  for (uint8_t i = 0; i < soc_num_digits; i++) {
    soc_str_temp[i] = soc % 10 + '0';
    soc /= 10;
  }
  for (uint8_t i = 0; i < soc_num_digits; i++) {
    soc_str[SOC_MAX_DIGITS - i - 1] = soc_str_temp[i];
  }

  lcd__print8(54, 37, "SOC");
  lcd__print18(46, 64, soc_str);
}

void lcd__print_wattemp(uint8_t watertemp) // water coolant? temperature
{
  uint8_t water_MAX_DIGITS = 3;
  uint8_t water_num_digits;
  char water_str[4] = "\0";
  char water_str_temp[4] = "   ";

  water_num_digits = (int)log10(watertemp) + 1;

  if (water_num_digits == 2) {
    water_str[0] = ' ';
  }

  for (int i = 0; i < water_num_digits; i++) {
    water_str_temp[i] = watertemp % 10 + '0';
    watertemp = watertemp / 10;
  }
  for (uint8_t i = 0; i < water_num_digits; i++) {
    water_str[water_MAX_DIGITS - i - 1] = water_str_temp[i];
  }

  lcd__print8(0, 50, "Water T");
  lcd__print14(0, 64, water_str);
}

// Menu Functions --------------------------------------------------------------- ---------------------------------------------------------------
void lcd__print_menu(void)
{
  // Screens
  char* zero = "Diagnostics";
  char* one = "RPM Threshold";
  char* two = "Regen";
  char* three = "Catchphrase";
  char* four = "Placeholder";
  char* five = "Back";
  uint8_t row_count = 0; // for button selection

  // Overlay Button Selection
  switch (row_count) {
    case 0:
      lcd__highlight_menu(0, zero);
      break;
    case 1:
      lcd__highlight_menu(1, one);
      break;
    case 2:
      lcd__highlight_menu(2, two);
      break;
    case 3:
      lcd__highlight_menu(3, three);
      break;
    case 4:
      lcd__highlight_menu(4, four);
      break;
    default:
      lcd__highlight_menu(5, five);
      break;
  }

  // Display the rest of the selections
  if (row_count != 0) lcd__print8(1, 1 + 8, zero);
  if (row_count != 1) lcd__print8(1, 1 + 16 + 4, one);
  if (row_count != 2) lcd__print8(1, 1 + 24 + 8, two);
  if (row_count != 3) lcd__print8(1, 1 + 32 + 12, three);
  if (row_count != 4) lcd__print8(1, 1 + 40 + 16, four);
  if (row_count != 5) lcd__print8(128 - lcd->getStrWidth(five) - 1, 63, five);

}

void lcd__highlight_menu(uint8_t row, const char* screen) // number 0-5
{
  if (row == 5) {
    lcd->drawBox(128 - lcd->getStrWidth(screen) - 2, 64 - lcd->getAscent() - 2, lcd->getStrWidth(screen) + 2, lcd->getAscent() + 2);
    lcd->setDrawColor(0);/* color 0 for the text */
    lcd__print8(128 - lcd->getStrWidth(screen) - 1, 63, screen);
    lcd->setDrawColor(1);
  } else {
    lcd->drawBox(0, row * 12, lcd->getStrWidth(screen) + 2, lcd->getAscent() + 2);
    lcd->setDrawColor(0);/* color 0 for the text */
    lcd__print8(1, 1 + 8 + 12 * row, screen);
    lcd->setDrawColor(1);
  }
}

void lcd__rpm_screen(void) // rpm threshold
{
//  lcd__print24(53, (64 - 24) / 2 + 24, DEFAULT_SHIFT_THRESHOLD_RPM);
  
  uint16_t rpm = DEFAULT_SHIFT_THRESHOLD_RPM;
    //RPM up to 5 digits
  uint8_t RPM_MAX_DIGITS = 5;
  char rpm_str_temp[6] = "     ";
  char rpm_str[6] = "     ";
  uint8_t rpm_num_digits = 1;

  //Round to hundreds
  rpm_num_digits = (int)log10(rpm) + 1;

  //clear remaining 1s before reupdating
  if (rpm_num_digits == 4) {
    rpm_str[0] = ' ';
  }

  for (uint8_t i = 0; i < rpm_num_digits; i++) {
    rpm_str_temp[i] = rpm % 10 + '0';
    rpm /= 10;
  }
  for (uint8_t i = 0; i < rpm_num_digits; i++) {
    rpm_str[RPM_MAX_DIGITS - i - 1] = rpm_str_temp[i];
  }
  lcd__print8(0, 8, "RPM Threshold");
  lcd__print18(53, (64 - 24) / 2 + 24, rpm_str);
  
}

// LCD Screen Update --------------------------------------------------------------- ---------------------------------------------------------------
void lcd__update_screen(uint16_t rpm, uint8_t gear, uint8_t lv, uint8_t etemp, uint8_t oiltemp, uint8_t drs, uint32_t curr_millis_lcd)
{
  if (curr_millis_lcd - prev_millis_lcd >= LCD_UPDATE_MS) {
    prev_millis_lcd = curr_millis_lcd;
    lcd__clear_screen();
    if (DISPLAY_SCREEN == 0) {
      lcd__print_rpm(rpm);
      lcd__print_gear(gear);
      lcd__print_lv(lv);
      lcd__print_etemp(etemp);
      lcd__print_oiltemp(oiltemp);
      lcd__print_drs(drs);
    }
    else if (DISPLAY_SCREEN == 1) {
      lcd__print_menu();
    }
    else if (DISPLAY_SCREEN == 2) {
      lcd__rpm_screen();
    }
  }
}

void lcd__update_screenE(uint16_t hv, uint8_t soc, uint8_t lv, uint8_t etemp, uint8_t watertemp, uint8_t drs, uint32_t curr_millis_lcd)
{
  if (curr_millis_lcd - prev_millis_lcd >= LCD_UPDATE_MS) {
    prev_millis_lcd = curr_millis_lcd;
    lcd__clear_screen();

    if (DISPLAY_SCREEN == 0) {
      lcd__print_hv(hv);
      lcd__print_soc(soc);
      lcd__print_lv(lv);
      lcd__print_etemp(etemp);
      lcd__print_wattemp(watertemp);
      lcd__print_drs(drs);
    }
    if (DISPLAY_SCREEN == 1) {
      lcd__print_menu();
    }
    else if (DISPLAY_SCREEN == 2) {
      lcd__rpm_screen();
    }
  }
}
