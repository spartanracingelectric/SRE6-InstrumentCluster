//——————————————————————————————————————————————————————————————————————————————
//  ACAN2515 Demo in loopback mode, for the Raspberry Pi Pico
//  Thanks to Duncan Greenwood for providing this sample sketch
//——————————————————————————————————————————————————————————————————————————————

#ifndef ARDUINO_ARCH_RP2040
#error "Select a Raspberry Pi Pico board"
#endif

//——————————————————————————————————————————————————————————————————————————————

#include <ACAN2515.h>
#include "LedControl.h"
#include <math.h>

//16 bit, start bit 0
const uint16_t RPM_ADDR = 0x640;

//const uint16_t GEAR_ADDR = 0x64D;

const uint16_t GEAR_ADDR = 0x703;

static const byte MCP2515_SCK  = 24; // SCK input of MCP2515
static const byte MCP2515_MOSI = 25; // SDI input of MCP2515
static const byte MCP2515_MISO = 21; // SDO output of MCP2517

static const byte MCP2515_CS  = 22;  // CS input of MCP2515 (adapt to your design)
static const byte MCP2515_INT = 20;  // INT output of MCP2515 (adapt to your design)


//——————————————————————————————————————————————————————————————————————————————
//  MCP2515 Driver object
//——————————————————————————————————————————————————————————————————————————————

ACAN2515 can (MCP2515_CS, SPI, MCP2515_INT) ;


//LED Display Driver Object

LedControl lc = LedControl(11,10,9,1);

//Refresh Rate

unsigned long delaytime = 500;
//——————————————————————————————————————————————————————————————————————————————
//  MCP2515 Quartz: adapt to your design
//——————————————————————————————————————————————————————————————————————————————

static const uint32_t QUARTZ_FREQUENCY = 8UL * 1000UL * 1000UL ; // 8 MHz


uint16_t rpm;
uint8_t gear;

static void receive0 (const CANMessage & inMessage) {
  Serial.println ("Receive 0") ;
}

//——————————————————————————————————————————————————————————————————————————————

static void receive1 (const CANMessage & inMessage) {
  Serial.println ("Receive 1") ;
}

//——————————————————————————————————————————————————————————————————————————————
//   SETUP
//——————————————————————————————————————————————————————————————————————————————

void setup () {

 /* The MAX72XX is in power-saving mode on startup, we have to do a wakeup call */
  
  lc.shutdown(0,false);
  
  /* Set the brightness to a medium values */
  
  lc.setIntensity(0,8);
  
  /* and clear the display */
  
  lc.clearDisplay(0);
  
  //--- Switch on builtin led
  pinMode (LED_BUILTIN, OUTPUT) ;
  digitalWrite (LED_BUILTIN, HIGH) ;
  //--- Start serial
  Serial.begin (115200) ;
  //--- Wait for serial (blink led at 10 Hz during waiting)
  /*
  while (!Serial) {
    delay (50) ;
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
  }
  */
  //--- There are no default SPI pins so they must be explicitly assigned
  SPI.setSCK(MCP2515_SCK);
  SPI.setTX(MCP2515_MOSI);
  SPI.setRX(MCP2515_MISO);
  SPI.setCS(MCP2515_CS);
  //--- Begin SPI
  SPI.begin () ;
  //--- Configure ACAN2515
  Serial.println ("Configure ACAN2515") ;
  ACAN2515Settings settings (QUARTZ_FREQUENCY, 500UL * 1000UL) ; // CAN bit rate 500 kb/s
  //settings.mRequestedMode = ACAN2515Settings::LoopBackMode ; // Select loopback mode

  const ACAN2515Mask rxm0 = extended2515Mask (0x1FFFFFFF) ;
  const ACAN2515Mask rxm1 = standard2515Mask (0x7FF, 0, 0) ;
  const ACAN2515AcceptanceFilter filters [] = {
  {standard2515Filter (RPM_ADDR, 0, 0), receive0}, // RXF0
  {standard2515Filter (GEAR_ADDR, 0, 0), receive1} // RXF1
  } ;
  
  //const uint16_t errorCode = can.begin (settings, [] { can.isr () ; }, rxm0, rxm1, filters, 2) ;
  const uint16_t errorCode = can.begin (settings, [] { can.isr () ; }) ;
  
  if (errorCode == 0) {
    Serial.print ("Bit Rate prescaler: ") ;
    Serial.println (settings.mBitRatePrescaler) ;
    Serial.print ("Propagation Segment: ") ;
    Serial.println (settings.mPropagationSegment) ;
    Serial.print ("Phase segment 1: ") ;
    Serial.println (settings.mPhaseSegment1) ;
    Serial.print ("Phase segment 2: ") ;
    Serial.println (settings.mPhaseSegment2) ;
    Serial.print ("SJW: ") ;
    Serial.println (settings.mSJW) ;
    Serial.print ("Triple Sampling: ") ;
    Serial.println (settings.mTripleSampling ? "yes" : "no") ;
    Serial.print ("Actual bit rate: ") ;
    Serial.print (settings.actualBitRate ()) ;
    Serial.println (" bit/s") ;
    Serial.print ("Exact bit rate ? ") ;
    Serial.println (settings.exactBitRate () ? "yes" : "no") ;
    Serial.print ("Sample point: ") ;
    Serial.print (settings.samplePointFromBitStart ()) ;
    Serial.println ("%") ;
  } else {
    Serial.print ("Configuration error 0x") ;
    Serial.println (errorCode, HEX) ;
  }
 
  digitalWrite (LED_BUILTIN, HIGH) ;
}

//----------------------------------------------------------------------------------------------------------------------

static uint32_t gGearUpdate = 0 ;
static uint32_t gRPMUpdate = 0 ;
static uint32_t gReceivedFrameCount = 0 ;
static uint32_t gSentFrameCount = 0 ;
static uint8_t gTransmitBufferIndex = 0 ;


//——————————————————————————————————————————————————————————————————————————————

void loop () {
  can.dispatchReceivedMessage();

  
  //CANMessage gear, rpm, frame;
  CANMessage frame;
  //gear.len = 8;
  //rpm.len = 8;

  if (can.available ()) {
    can.receive (frame);
    if (frame.id == RPM_ADDR) {
        rpm = frame.data[1]+frame.data[0]*256;
    }
    if (frame.id == GEAR_ADDR) {
        //gear = (frame.data[6]&(0b11110000))>>4;
        gear = frame.data[1];
    }
  }

  if (gRPMUpdate < millis()) {
    gRPMUpdate += 400;
     //Serial.print (frame.id);
    //Serial.print (" Gear: ") ;
    Serial.println(gear);
    //Serial.print (" RPM: ");
    Serial.println(rpm);
    Serial.println();
  
    //interpret rpm data
    uint16_t x = (rpm/100) * 100 ; //Round to hundreds
    
    uint8_t count = 0;
    uint8_t xLength;
    
    if(x!=0)
      xLength = (int)log10(x)+1;
    else xLength = 1;
    
    //ensure correct format for rpm data
    while(count<xLength){
      lc.setDigit(0,count,x%10,false);
      count++;
      x/=10;
    }
  }

  if (gGearUpdate < millis ()) {
    gGearUpdate += 200 ;
    //digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;

    lc.setDigit(0,7,gear,false);
    /*
    frame.idx = gTransmitBufferIndex ;
    gTransmitBufferIndex = (gTransmitBufferIndex + 1) % 2 ;
    switch (gSentFrameCount % 2) {
      case 0 : { // Matches filter #0
        
        //interpret rpm data
        uint8_t x = frame.data[0]+frame.data[1]*256;
        
        uint8_t count = 0;
        uint8_t xLength;
        
        if(x!=0)
          xLength = (int)log10(x)+1;
        else xLength = 1;
        
        //ensure correct format for rpm data
        while(count<xLength){
          lc.setDigit(0,count,x%10,false);
          count++;
          x/=10;
        }
        break ;
      }
      case 1 : // Matches filter #1
        uint8_t gearRatio = (frame.data[6]&(0b11110000))>>4;
        lc.setDigit(0,7,gearRatio,false);
        break ;
    }
    */
  }
}


  /*
//keep reading CAN messages until both gear and rpm data is found
  while(gear.id != 0x64D || rpm.id != 0x640){
     can.receive(frame);
     if(frame.id==0x64D)
      gear = frame;
     else if(frame.id==0x640)
      rpm = frame;

      Serial.print ("Received: ") ;
    for (uint8_t i = 0; i < frame.len; i++) {
      Serial.print(frame.data[i]);
      Serial.print(" ");
    }
    Serial.println();
      
    }
    //display gearRatio data
    uint8_t gearRatio = (gear.data[6]&(0b11110000))>>4;
    lc.setDigit(0,7,gearRatio,false);

    //interpret rpm data
    uint8_t x = rpm.data[0]+rpm.data[1]*256;
    
    uint8_t count = 0;
    uint8_t xLength;
    if(x!=0)
      xLength = (int)log10(x)+1;
    else xLength = 1;
    
    //ensure correct format for rpm data
    while(count<xLength){
      lc.setDigit(0,count,x%10,false);
      count++;
      x/=10;
    }
    
    //Serial.println (gReceivedCount) ;
    delay(delaytime);
  }
  */
 
  

//——————————————————————————————————————————————————————————————————————————————
