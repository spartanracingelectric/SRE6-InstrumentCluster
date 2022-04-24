#ifndef CONFIG_H_
#define CONFIG_H_

// Set to 1 if you want to print the input data over serial
#define SERIAL_DEBUG_EN 0

/****************************************************************************/
/*  INSTRUMENT CLUSTER - SETUP CONFIGURATION FILE (for ports, etc)      */
/*                                      */
/*  DUE TO F_CPU, conf.h MUST BE INCLUDED BEFORE ANY <avr/delay.h>      */
/****************************************************************************/

/*---------------------------------------------------------------------------/
/ CUSTOM CONFIGURATION VARIABLES
/---------------------------------------------------------------------------*/

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

#endif /* CONF_H_ */
