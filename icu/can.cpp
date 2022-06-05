#include "can.h"
#include "config.h"

static const uint32_t QUARTZ_FREQUENCY = 16UL * 1000UL * 1000UL; // 16 MHz

//Skip INT pin for Rev A, set to 0
#if (BOARD_REVISION == 'A')
ACAN2515 can (PICO_CAN_SPI_CS, SPI, 15);
#elif (BOARD_REVISION == 'B')
ACAN2515 can (PICO_CAN_SPI_CS, SPI1, PICO_CAN_INT);
#endif

ACAN2515Settings settings (QUARTZ_FREQUENCY, 500UL * 1000UL) ; // CAN bit rate 500s kb/s

#if (POWERTRAIN_TYPE == 'C')
uint16_t curr_rpm = 0;
uint8_t curr_gear = 0;

static void can__rpm_receive (const CANMessage & inMessage)
{
  curr_rpm = ((inMessage.data[1]) | (inMessage.data[0] << 8));
  //Serial.println ("Received RPM " + curr_rpm) ;
}

static void can__gear_receive (const CANMessage & inMessage)
{
  curr_gear = inMessage.data[1];
  //Serial.println ("Received Gear " + curr_gear) ;
}
#else
float curr_hv = 0;
float curr_lv = 0;

static void can__hv_receive (const CANMessage & inMessage)
{
  // Little endian
  // As per Stafl CAN protocol divide by 1000 to get units in Volts (or multiply by 0.001)
  curr_hv = ((inMessage.data[4]) | (inMessage.data[5] << 8) | (inMessage.data[6] << 16) | (inMessage.data[7] << 24)) * .001f;
  //Serial.println ("Received RPM " + curr_rpm) ;
}

static void can__lv_receive (const CANMessage & inMessage)
{
  // Little endian
  // As per VCU configuration, divide by 1000 to get units in Volts (or multiply by 0.001)
  curr_lv = ((inMessage.data[0]) | (inMessage.data[1] << 8)) * 0.001f;
  //Serial.println ("Received Gear " + curr_gear) ;
}
#endif

static void can__dummy_receive (const CANMessage & inMessage)
{
  uint8_t durr;
  //curr_gear = inMessage.data[1];
  //Serial.println ("Received Gear " + curr_gear) ;
}

const ACAN2515Mask rxm0 = standard2515Mask (0x7FF, 0, 0) ;
//const ACAN2515Mask rxm1 = standard2515Mask (0x7FF, 0, 0) ;

#if (POWERTRAIN_TYPE == 'C')
const ACAN2515AcceptanceFilter filters [] =
{
  {standard2515Filter (CAN_RPM_ADDR, 0, 0), can__rpm_receive}, // RXF0
  {standard2515Filter (CAN_GEAR_ADDR, 0, 0), can__gear_receive} // RXF1
  //{standard2515Filter (0x7FE, 0, 0), can__dummy_receive}, // RXF2
} ;

uint16_t can__get_rpm()
{
  return curr_rpm;
}

uint8_t can__get_gear()
{
  return curr_gear;
}
#else
const ACAN2515AcceptanceFilter filters [] =
{
  {standard2515Filter (CAN_LV_ADDR, 0, 0), can__lv_receive}, // RXF0
  {standard2515Filter (CAN_HV_ADDR, 0, 0), can__hv_receive} // RXF1
  //{standard2515Filter (0x7FE, 0, 0), can__dummy_receive}, // RXF2
} ;

float can__get_hv()
{
  return curr_hv;
}

float can__get_lv()
{
  return curr_lv;
}
#endif


void can__start()
{
  
  //--- Configure ACAN2515
  //Serial.println ("Configure ACAN2515") ;

  // No filter
  //const uint16_t errorCode = can.begin (settings, [] { can.isr () ; }) ;

  // With filter
  const uint16_t errorCode = can.begin (settings, [] { can.isr () ; },
                                        rxm0, filters, 2) ;
  
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
  
  //Non-zero indicates error
  if (errorCode) {
    Serial.print ("Configuration error 0x") ;
    Serial.println (errorCode, HEX);
  }
 
}

void can__stop()
{
  can.end();
}

static uint32_t gBlinkLedDate = 0 ;
static uint32_t gReceivedFrameCount = 0 ;
static uint32_t gSentFrameCount = 0 ;

void can__send_test()
{
  CANMessage frame;
  frame.id = 0x7EE;
  frame.len = 8;
  frame.data[0] = 0x53; 
  if (gBlinkLedDate < millis ()) {
    gBlinkLedDate += 200 ;
    const bool ok = can.tryToSend (frame) ;
    if (ok) {
      gSentFrameCount += 1 ;
      Serial.print ("Sent: ") ;
      Serial.println (gSentFrameCount) ;
    } else {
      Serial.println ("Send failure") ;
    }
  }
}

void can__receive()
{
  can.dispatchReceivedMessage();
  CANMessage frame ;

  /*
  if (can.available()) {
    can.receive(frame);
    Serial.print("ID: ");
    Serial.println(frame.id);
    Serial.print("Data: ");
    for (int i = 0; i < 8; i++) {
      Serial.println(frame.data[i]);
    }
  }
  */
  
  /*
  if (gBlinkLedDate < millis ()) {
    gBlinkLedDate += 200 ;
    const bool ok = can.tryToSend (frame) ;
    if (ok) {
      gSentFrameCount += 1 ;
      Serial.print ("Sent: ") ;
      Serial.println (gSentFrameCount) ;
    } else {
      Serial.println ("Send failure") ;
    }
  }
  */
  if (can.available ()) {
    can.receive (frame) ;
    Serial.println((frame.data[1]) | (frame.data[0] << 8));
  }
  
}
