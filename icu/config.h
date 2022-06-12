#ifndef CONFIG_H_
#define CONFIG_H_

/********************************************************************/
/*  INSTRUMENT CLUSTER - SETUP CONFIGURATION FILE (for ports, etc)  */
/*                                                                  */
/********************************************************************/

// Board Revision, select:
// 'A' for Rev A
// 'B' for Rev B
#define BOARD_REVISION 'A'
//#define BOARD_REVISION 'B'
//#define BOARD_REVISION 'B' //Potentially unused

#define POWERTRAIN_TYPE 'C'
//#define POWERTRAIN_TYPE 'E'

// Set to 1 if you want to print the input data over serial
#define SERIAL_DEBUG_EN 0

// Display Screen Status
// 0 for Driver
// 1 for Menu
// 2 for Individual Menu Screens
#define DISPLAY_SCREEN 0

/*---------------------------------------------------------------------------/
/ DRIVER PARAMETERS
/---------------------------------------------------------------------------*/

#define DEFAULT_SHIFT_THRESHOLD_RPM 11500
#define G12_SHIFT_THRESHOLD_RPM 11800
#define G23_SHIFT_THRESHOLD_RPM 11600
#define G34_SHIFT_THRESHOLD_RPM 11400
#define G45_SHIFT_THRESHOLD_RPM 11200
#define G56_SHIFT_THRESHOLD_RPM 11000

#define OVERREV_THRESHOLD_RPM_ADDER 500

//#define OVERREV_THRESHOLD_RPM (SHIFT_THRESHOLD_RPM+500)
#define REVLIM_THRESHOLD_RPM 13000
//#define SHIFT_THRESHOLD_FLASH_MS
#define OVERREV_THRESHOLD_FLASH_MS 250
#define REVLIM_THRESHOLD_FLASH_MS 100

#define LCD_UPDATE_MS 500

/*---------------------------------------------------------------------------/
/ PIN INITIALIZATIONS
/---------------------------------------------------------------------------*/

//  Rev A
#if (BOARD_REVISION == 'A')
//  LCD
#define PICO_LCD_SPI_CS     2
#define PICO_LCD_SPI_MOSI   4
#define PICO_LCD_SPI_SCK    5
#define PICO_LCD_A0         3
#define PICO_LCD_RST        U8X8_PIN_NONE
//  LEDS, MAX7219
#define PICO_LED_SPI_SCK    18
#define PICO_LED_SPI_MOSI   19
#define PICO_LED_SPI_CS     13
//CAN, MCP2515
#define PICO_CAN_SPI_SCK    18
#define PICO_CAN_SPI_MOSI   19
#define PICO_CAN_SPI_MISO   16
#define PICO_CAN_SPI_CS     17

//  Rev B
#elif (BOARD_REVISION == 'B')
//  LCD
#define PICO_LCD_SPI_CS     5
#define PICO_LCD_SPI_MOSI   3
#define PICO_LCD_SPI_SCK    2
#define PICO_LCD_A0         4
#define PICO_LCD_RST        1
//  LEDS, MAX7219
#define PICO_LED_SPI_SCK    18
#define PICO_LED_SPI_MOSI   19
#define PICO_LED_SPI_CS     17
//CAN, MCP2515
#define PICO_CAN_SPI_SCK    10
#define PICO_CAN_SPI_MOSI   11
#define PICO_CAN_SPI_MISO   12
#define PICO_CAN_SPI_CS     13
#define PICO_CAN_INT        14
#define PICO_CAN_RST        15
#endif

// Buttons - change if needed
#define HOLD_TIME 1000          //Button hold time for bottom buttons on default screen. In ms
#define BUT1 PINC0            //Top left
#define BUT2 PINC1            //Top right
#define BUT3 PINC2            //Bottom left
#define BUT4 PINC3            //Bottom right
#define PCINT_BUT1 (1<<PCINT8)
#define PCINT_BUT2 (1<<PCINT9)
#define PCINT_BUT3 (1<<PCINT10)
#define PCINT_BUT4 (1<<PCINT11)

/*---------------------------------------------------------------------------/
/ CUSTOM CONFIGURATION VARIABLES
/---------------------------------------------------------------------------*/

//  CAN BUS
/////////////////////
#if (POWERTRAIN_TYPE == 'C') 
//#define CANBUS_SPEED 1000UL * 1000UL //1 Mbit/s
#define CANBUS_SPEED 500UL * 1000UL //500 kbit/s
#define CAN_RPM_ADDR 0x640
#define CAN_GEAR_ADDR 0x703
#else //POWERTRAIN_TYPE == 'E'
#define CANBUS_SPEED 500UL * 1000UL //500 kbit/s
#endif

#if (POWERTRAIN_TYPE == 'E')
//#define CANBUS_SPEED 1000UL * 1000UL //1 Mbit/s
#define CANBUS_SPEED 500UL * 1000UL //500 kbit/s
#define CAN_RPM_ADDR 0x640
#define CAN_GEAR_ADDR 0x703
#define CANBUS_SPEED 500UL * 1000UL //500 kbit/s
#endif

if (POWERTRAIN_TYPE == 'E')
#define CANBUS_SPEED 500UL * 1000UL //500 kbit/s
#define CAN_SOC_ADDR 0x627
#define CAN_BAT_TEMP_ADDR 0x628
#define CAN_RPM_ADDR 0x0A5 // Does ev need rpm?
#define CAN_REGEN_ADDR 0x508
#define CAN_HV_ADDR 0x623
#define CAN_LV_ADDR 0x700
#define CANBUS_SPEED 500UL * 1000UL //500 kbit/s
#endif

//  LOW VOLTAGE
/////////////////////
#define LV_WARNING_THRESHOLD 12.0f

//  WHEEL SPEEDS
/////////////////////
//Wheel diameter in inches
#define WHEEL_DIAMETER_IN 16.0f
#define WHEEL_CIRCUMFERENCE_M (WHEEL_DIAMETER_IN * 0.0254 * 3.141f)
#define METERS_SEC_TO_MPH  2.237f

/*---------------------------------------------------------------------------/
/ LOW VOLTAGE
/---------------------------------------------------------------------------*/

#define LV_OFFSET .8f

/*---------------------------------------------------------------------------/
/ CAN ADDRESSES
/---------------------------------------------------------------------------*/
/* CAN packet addresses based on the spreadsheet */
#define SOC_ADDR 0x627
#define BAT_TEMP_ADDR 0x628
#define RPM_ADDR 0x0A5
#define WSS_ADDR 0x505      // Interpolated WSS address
#define REGEN_ADDR 0x508
#define HV_ADDR 0x623
#define LV_ADDR 0x700
#define TS_ADDR 0x701       // Timestamp Address (-> DAQ)
#define REGEN1_ADDR 0x702       // (-> VCU)
#define REGEN2_ADDR 0x703       // (-> VCU)
#define REGEN3_ADDR 0x704

#define MAX72XX_HARDWARE_TYPE MD_MAX72XX::PAROLA_HW

#ifndef BOARD_REVISION
#error "Select a board revision"
#endif
#ifndef POWERTRAIN_TYPE
#error "Select a powertrain type (C for Combustion or E for Electric)"
#endif

/*---------------------------------------------------------------------------/
/ HELPFUL MACROS
/---------------------------------------------------------------------------*/
#define MAX_LED_BRIGHTNESS 0xF

#endif /* CONF_H_ */
