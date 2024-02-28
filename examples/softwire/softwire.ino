/* Demonstration of Rtc_Pcf8563 Set Time. 
 * Set the clock to a time then loop over reading time and 
 * output the time and date to the serial console.
 *
 * I used a RBBB with Arduino IDE, the pins are mapped a 
 * bit differently. Change for your hw
 * SCK - A5, SDA - A4, INT - D3/INT1
 *
 * After loading and starting the sketch, use the serial monitor
 * to see the clock output.
 * 
 * setup:  see Pcf8563 data sheet.
 *         1x 10Kohm pullup on Pin3 INT
 *         No pullups on Pin5 or Pin6 (I2C internals used)
 *         1x 0.1pf on power
 *         1x 32khz chrystal
 *
 * Joe Robertson, jmr
 * orbitalair@gmail.com
 */

#include "SoftWire.h"
SoftWire SWire(PA8, PA1, SOFT_FAST); //SCL SDA


#define Serial Serial3
#include "Rtc_Pcf8563.h"



//init the real time clock
Rtc_Pcf8563 rtc(SWire);

void setup()
{
  Serial3.begin(9600);
    while (!Serial3);
    Serial3.println("== START 0 ==");
    Serial3.println("== START 1 ==");
    Serial3.println("== START 0 =="); 
  //clear out the registers
  //uint8_t error = rtc.initClock();
   SWire.begin();
   SWire.beginTransmission(0x51);
    uint8_t error = SWire.endTransmission();
  if (error != 0) {
    Serial3.print("InitClock error: "); 
    Serial3.println(error);
  }
  else {
    Serial3.println("No ERROR");
  }
  //set a time to start with.
  //day, weekday, month, century(1=1900, 0=2000), year(0-99)
  //rtc.setDate(14, 6, 3, 0, 24);
  //hr, min, sec
  //rtc.setTime(1, 15, 0);
}

void loop()
{
  //both format functions call the internal getTime() so that the 
  //formatted strings are at the current time/date.
  //Serial.println(rtc.readStatus2());
  Serial.print(rtc.formatTime());
  Serial.print("\r\n");
  Serial.println(rtc.getSecond());
 
  Serial.print(rtc.formatDate());
  Serial.print("\r\n");
  delay(1000);
}
