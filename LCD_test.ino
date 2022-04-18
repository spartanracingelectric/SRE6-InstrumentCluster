#include <Arduino.h>
#include <U8g2lib.h>


#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define PICO_DC 16 //LCD A0
#define PICO_CS 17
#define PICO_SCK 18
#define PICO_TX 19
#define PICO_RST 20

/*
  U8g2lib Example Overview:
    Frame Buffer Examples: clearBuffer/sendBuffer. Fast, but may not work with all Arduino boards because of RAM consumption
    Page Buffer Examples: firstPage/nextPage. Less RAM usage, should work with all Arduino boards.
    U8x8 Text Only Example: No RAM usage, direct communication with display controller. No graphics, 8x8 Text only.
    
*/

// Please UNCOMMENT one of the contructor lines below
// U8g2 Contructor List (Frame Buffer)
// The complete list is available here: https://github.com/olikraus/u8g2/wiki/u8g2setupcpp
// Please update the pin numbers according to your setup. Use U8X8_PIN_NONE if the reset pin is not connected
//U8G2_NULL u8g2(U8G2_R0);  // null device, a 8x8 pixel display which does nothing
//U8G2_ST7565_NHD_C12832_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8G2_ST7565_NHD_C12832_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8G2_ST7565_NHD_C12864_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8G2_ST7565_NHD_C12864_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

// End of constructor list
U8G2_ST7565_NHD_C12864_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ PICO_SCK, /* data=*/ PICO_TX, /* cs=*/ PICO_CS, /* dc=*/ PICO_DC, /* reset=*/ PICO_RST);
//U8G2_ST7565_NHD_C12864_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ PICO_CS, /* dc=*/ PICO_DC, /* reset=*/ PICO_RST);



void driverC(void)
{
//  int w = (128 - u8g2.getStrWidth("50")) / 2;
//  int h = (64 - u8g2.getAscent()) / 2 + u8g2.getAscent();
//  //u8g2.drawXBMP( 0, 0, 128, 64, myBitmap);
//  
//  //temp bottom left
//  u8g2.setFont(u8g2_font_logisoso16_tf);
//  u8g2.drawStr(0, 64,"30");
//  u8g2.drawCircle(u8g2.getStrWidth("30") + 2, (64-u8g2.getAscent()) + 2, 2);
//
//  //rpm center
//  u8g2.setFont(u8g2_font_logisoso42_tf);
//  u8g2.drawStr(w, h,"50");
//
////  u8g2.drawCircle(128-w+4, 64 - 6, 5);
////  u8g2.drawDisc(128-w+10+6, 64 - 6, 4);
////  u8g2.drawCircle(128-w+10+8+8, 64 - 6, 3);
////  u8g2.drawCircle(128-w+10+8+6+10, 64 - 6, 2);
//
//  // gear pos bottom right
//  u8g2.drawCircle(128-w+15, 4+10, 10);
//  u8g2.drawDisc(128-w+15, 4+20+8, 8);
//  u8g2.drawCircle(128-w+15, 4+20+16+6, 6);
//  u8g2.drawCircle(128-w+15, 4+20+16+12+4, 4);

u8g2.setFont(u8g2_font_helvB18_te);
u8g2.drawStr(10, 20,"3");
u8g2.drawStr(40, 20,"31394");
int x = 40 + u8g2.getStrWidth("31394") ;

u8g2.setFont(u8g2_font_helvB10_te);
u8g2.drawStr(0, 64,"30%");
u8g2.drawStr(0, 64-18,"70");
u8g2.drawStr(95, 64,"XXX");
u8g2.drawStr(95, 64-18,"XX");

u8g2.drawCircle(u8g2.getStrWidth("70")+2, 36, 1);

u8g2.setFont(u8g2_font_blipfest_07_tr);
u8g2.drawStr(35, 37,"HAWT");
u8g2.drawStr(35, 61,"COLD");
u8g2.drawStr(76, 37,"HAWT");
u8g2.drawStr(76, 61,"WARM");

u8g2.drawStr(0, 64-12, "LV");
u8g2.drawStr(0, 64-18-12, "Temp C");
u8g2.drawStr(95, 64-12, "Oil PSI");
u8g2.drawStr(95, 64-18-12, "Clnt Temp");
u8g2.drawStr(x, 20, "rpm");

u8g2.drawCircle(u8g2.getStrWidth("Temp C")+2, 29, 1);

u8g2.drawBox(51,30,10,10);
u8g2.drawBox(65,30,10,10);
u8g2.drawBox(51,54,10,10);
u8g2.drawBox(65,54,10,10);


}

void driverE(void)
{
  //u8g2.drawXBMP( 0, 0, 128, 64, myBitmap);
//
//  
//  u8g2.setFont(u8g2_font_logisoso16_tf);
//  u8g2.drawStr(0, 64,"30");
//  u8g2.drawCircle(u8g2.getStrWidth("30") + 2, (64-u8g2.getAscent()) + 2, 2);
//    int w80 = 128-u8g2.getStrWidth("80%");
//u8g2.drawStr(w80, 64,"80%");
//
//  u8g2.setFont(u8g2_font_logisoso42_tf);
//    int w = (128 - u8g2.getStrWidth("50"))/2;
//  int h = (64 - u8g2.getAscent()) / 2 + u8g2.getAscent();
//  u8g2.drawStr(w, h,"50");
  
u8g2.setFont(u8g2_font_helvB18_te);
int x = (128-u8g2.getStrWidth("4.156 V"))/2;
u8g2.drawStr(x, 20,"4.156 V");
u8g2.drawStr(40, 20,"");
u8g2.drawStr(95, 64,"50");

u8g2.setFont(u8g2_font_helvB10_te);
u8g2.drawStr(0, 64,"30%");
u8g2.drawStr(0, 64-18,"70");
//u8g2.drawStr(120, 64, "%");

u8g2.drawCircle(u8g2.getStrWidth("70")+2, 36, 1);

u8g2.setFont(u8g2_font_blipfest_07_tr);
u8g2.drawStr(35, 37,"HAWT");
u8g2.drawStr(35, 61,"COLD");
u8g2.drawStr(76, 37,"HAWT");
u8g2.drawStr(76, 61,"WARM");

u8g2.drawStr(0, 64-12, "LV");
u8g2.drawStr(0, 64-18-12, "B Temp");
u8g2.drawStr(95, 64-18-10, "Charge");

u8g2.drawBox(51,30,10,10);
u8g2.drawBox(65,30,10,10);
u8g2.drawBox(51,54,10,10);
u8g2.drawBox(65,54,10,10);
  
}

void menu(void){
  u8g2.setFontMode(1); /* activate transparent font mode */    
  u8g2.setDrawColor(1);
  u8g2.setFont(u8g2_font_helvB08_te);
  u8g2.drawStr(0, 8, "Settings");
  u8g2.drawStr(0, 16+4, "Diagnosis");
  u8g2.drawStr(0, 24+8, "Tire Status");
  u8g2.drawStr(0, 32+12, "Layout");
  u8g2.drawStr(0, 40+16, "Cool Graphs");
  u8g2.drawBox(128-u8g2.getStrWidth("Back")-1, 64-u8g2.getAscent()-1, u8g2.getStrWidth("Back")+2, u8g2.getAscent()+2);
  u8g2.setDrawColor(0);/* color 0 for the text */
  u8g2.drawStr(128-u8g2.getStrWidth("Back"), 64, "Back");
}


void setup()
{
  // put your setup code here, to run once:
  u8g2.begin();
  u8g2.clearBuffer();
}

void loop()
{
  // put your main code here, to run repeatedly:
  u8g2.firstPage();
  u8g2.setDrawColor(1);
  u8g2.setBitmapMode(0);
  do
  {
    //driverC();
    driverE();
    //menu();
    
  } while (u8g2.nextPage());

  delay(1000);

}
