
#pragma once

#include "Arduino.h"

class ds1302
{
public:
  ds1302(uint8_t cePin, uint8_t dataPin, uint8_t clkPin);
  ~ds1302();

  void init();

  void startData();
  void stopData();

  // enable or disable internal clock
  // When disabled, clock oscillator is stopped and the DS1302
  // is placed into a low-power standby mode with a current drain of less than 100nA.
  void enableClock(bool enable);

  void disableWriteProtection();

  // read
  byte getSeconds();
  byte getMinutes();
  byte getHour();
  byte getDate();
  byte getMonth();
  
  // day in week
  byte getDay();

  byte getYear();

  // write

  // seconds range 00 - 59
  void setSeconds(byte seconds);

  // minutes range 00 - 59
  void setMinutes(byte minutes);

  // regardless of hour mode AM/PM or 24 mode
  // we always set hour using 24h format
  // hour range 0 - 23
  void setHour(byte hour);

  // date range 1 - 31
  void setDate(byte date);

  // month range 1 - 12
  void setMonth(byte month);

  // day range 1 - 7
  void setDay(byte day);

  // year range 00 - 99
  void setYear(byte year);

  // TODO switching reinitialize clock
  // The hours data must be re-initialized whenever the 12/24 bit is changed
  // How?
  // For now, when we change hour mode, device need to be restarted
  void set24HourMode(bool hourMode24);

  enum HourMode
  {
    Mode24,
    AM,
    PM
  };

  HourMode getHourMode();

  enum RamPage
  {
    C = 0b11000000,
    D = 0b11010000,
    E = 0b11100000,
    F = 0b11110000
  };

  // Note: Ram values are cleared of battery power is lost
  // For pages C,D and E addressIndex range 0 - 7
  // For page F addressIndex range 0 - 6
  byte readRam(RamPage page, uint8_t addressIndex);
  void writeRam(RamPage page, uint8_t addressIndex, byte data);


private:
  uint8_t _cePin; // RST/CE
  uint8_t _dataPin; // I/O
  uint8_t _clkPin; // clock pin

  uint8_t _clkDelay; // clock delay
  
  void clock();
  void writeByte(byte data);
  byte readByte();

  bool isClockEnabled();

};