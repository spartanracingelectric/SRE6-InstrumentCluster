#include "lcd.h"

U8G2_ST7565_NHD_C12864_F_4W_SW_SPI *lcd;

uint32_t prev_millis_lcd = 0;

void lcd__init(U8G2_ST7565_NHD_C12864_F_4W_SW_SPI *lcd_ptr)
{
  // Set internal lcd.cpp ptr to whatever is passed into the function
  lcd = lcd_ptr;
  // Begin
  lcd->begin();
}

void lcd__clear_screen() {
  lcd->clearBuffer();
}

void lcd__print8(uint8_t x, uint8_t y, char *str)
{
  // Need to implement a way to update ONLY the space that is to be printed
  //lcd->clearBuffer();          // clear the internal memory

  //Refuses to take in a passed parameter for some reason
  //Bandaid fix to make multiple functions
  lcd->setFont(u8g2_font_helvB08_tr); // choose a suitable font

  lcd->drawStr(x, y, str);  // write something to the internal memory
  lcd->sendBuffer();          // transfer internal memory to the display
}

void lcd__print14(uint8_t x, uint8_t y, char *str)
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
  char rpm_str[] = "rpm";
  lcd__print14(45, 45, rpm_str);
}

void lcd__print_template()
{
  if (POWERTRAIN_TYPE == 'C') {

    //    lcd__print14(40, 40, "Gear POS");
    //    lcd__print14(0, 40, "Engine T");
    //    lcd__print10(0,
  }
}

// Combustion Car ---------------------------------------------------------------
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

// E & C car ---------------------------------------------------------------
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
    if (lv_str_temp[lv_MAX_DIGITS - 1] == '0' && i == lv_MAX_DIGITS-1){
      lv_str[0] = ' ';
      continue;
    }
    lv_str[lv_MAX_DIGITS - i - 1] = lv_str_temp[i];
  }

  lcd__print8(114, 33, "LV");
  lcd__print14(94, 48, lv_str);
}

void lcd__print_etemp(uint8_t etemp) // Accumulator/Engine temperature
{
  uint8_t etemp_MAX_DIGITS = 3;
  uint8_t etemp_num_digits;
  char etemp_str[4] = "\0";
  char etemp_str_temp[4] = "   ";

  etemp_num_digits = (int)log10(etemp) + 1;

  for(int i = 0; i < etemp_num_digits; i++){
    etemp_str_temp[i] = etemp%10 + '0';
    etemp = etemp/10;
  }
  for (uint8_t i = 0; i < etemp_num_digits; i++) {
    etemp_str[etemp_MAX_DIGITS - i - 1] = etemp_str_temp[i];
  }

  lcd__print8(0, 20, "Eng T");
  lcd__print14(0, 36, etemp_str);
}

void lcd__print_oiltemp(uint8_t oiltemp) // Oil coolant? temperature
{
  uint8_t oil_MAX_DIGITS = 3;
  uint8_t oil_num_digits;
  char oil_str[4] = "\0";
  char oil_str_temp[4] = "   ";

  oil_num_digits = (int)log10(oiltemp) + 1;

  for(int i = 0; i < oil_num_digits; i++){
    oil_str_temp[i] = oiltemp%10 + '0';
    oiltemp = oiltemp/10;
  }
  for (uint8_t i = 0; i < oil_num_digits; i++) {
    oil_str[oil_MAX_DIGITS - i - 1] = oil_str_temp[i];
  }

  lcd__print8(0, 50, "Oil T");
  lcd__print14(0, 64, oil_str);
}

void lcd__print_drs(uint8_t drs) // DRS Open or Closed: 0 or 1
{
  lcd__print8(90, 64, "DRS");
  if(drs == 0)
  {
    lcd__print14(114, 64, "O");
  }else if(drs == 1)
  {
    lcd__print14(114, 64, "C");
  }
  
}

// Electric car ---------------------------------------------------------------
void lcd__print_hv(uint16_t hv) { // accumulator voltage (comes in float or integer?)
  //RPM up to 5 digits
  uint8_t HV_MAX_DIGITS = 5;
  char hv_str_temp[6] = "     ";
  char hv_str[6] = "     ";
  uint8_t hv_num_digits = 1;

  //Round to hundreds
  hv = (hv / 100) * 100;

  if (hv != 0)
    hv_num_digits = (int)log10(hv) + 1;

  //clear remaining 1s before reupdating
  if (hv_num_digits == 4) {
    hv_str[0] = ' ';
  }

  for (uint8_t i = 0; i < hv_num_digits; i++) {
    hv_str_temp[i] = hv % 10 + '0';
    hv /= 10;
  }
  for (uint8_t i = 0; i < hv_num_digits; i++) {
    hv_str[HV_MAX_DIGITS - i - 1] = hv_str_temp[i];
  }

  lcd__print18(40, 10, hv_str);
}

void lcd__print_soc(uint8_t soc) { // State of charge 0-100%
  //soc up to 3 digits
  uint8_t SOC_MAX_DIGITS = 3;
  char soc_str_temp[4] = "   ";
  char soc_str[4] = "   ";
  uint8_t soc_num_digits = 1;

  //Round to hundreds
  soc = (soc / 100) * 100;

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

  lcd__print18(80, 64, soc_str);
}

void lcd__update_screen(uint16_t rpm, uint8_t gear, uint8_t lv, uint8_t etemp, uint8_t oiltemp, uint8_t drs, uint32_t curr_millis_lcd)
{
  if (curr_millis_lcd - prev_millis_lcd >= LCD_UPDATE_MS) {
    prev_millis_lcd = curr_millis_lcd;
    lcd__clear_screen();
    lcd__print_rpm(rpm);
    lcd__print_gear(gear);
    lcd__print_lv(lv);
    lcd__print_etemp(etemp);
    lcd__print_oiltemp(oiltemp);
    lcd__print_drs(drs);

  }
}
