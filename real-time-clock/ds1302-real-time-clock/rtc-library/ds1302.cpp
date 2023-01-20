#include "ds1302.h"

#define RegisterSecondsWrite 0b10000000
#define RegisterSecondsEnableClock 0b00000000
#define RegisterSecondsDisableClock 0b10000000

#define RegisterSecondsRead 0b10000001
#define RegisterMinutesWrite 0b10000010
#define RegisterMinutesRead 0b10000011
#define RegisterHourWrite 0b10000100
#define RegisterHourRead 0b10000101
#define RegisterDateWrite 0b10000110
#define RegisterDateRead 0b10000111
#define RegisterMonthWrite 0b10001000
#define RegisterMonthRead 0b10001001
#define RegisterDayWrite 0b10001010
#define RegisterDayRead 0b10001011
#define RegisterYearWrite 0b10001100
#define RegisterYearRead 0b10001101
#define RegisterWriteProtectWrite 0b10001110
#define RegisterWriteProtectRead 0b10001111
#define RegisterTrickleChargeWrite 0b10010000
#define RegisterTrickleChargeRead 0b10010001

ds1302::ds1302(uint8_t cePin, uint8_t dataPin, uint8_t clkPin) : _cePin(cePin), _dataPin(dataPin), _clkPin(clkPin), _clkDelay(1)
{

}

ds1302::~ds1302()
{

}

void ds1302::init()
{
  pinMode(_clkPin, OUTPUT);
  pinMode(_cePin, OUTPUT);
  
  digitalWrite(_clkPin, LOW);
  delay(10);
  digitalWrite(_cePin, LOW);
  delay(10);

  pinMode(_dataPin, INPUT);

  disableWriteProtection();
}

void ds1302::clock()
{
  digitalWrite(_clkPin, HIGH);
  delay(_clkDelay);
  digitalWrite(_clkPin, LOW);
  delay(_clkDelay);
}

void ds1302::startData()
{
  digitalWrite(_cePin, HIGH);
  delay(10);
}

void ds1302::stopData()
{
  digitalWrite(_cePin, LOW);
  delay(10);
}

void ds1302::writeByte(byte data)
{
  pinMode(_dataPin, OUTPUT);

  byte mask = 0b00000001;

  for (int i = 0; i < 8; i++)
  {
    uint8_t signalType = LOW;

    if ((data & mask) > 0)
    {
      signalType = HIGH;
    }

    digitalWrite(_dataPin, signalType);
    clock();

   mask <<= 1;
  }
}

byte ds1302::readByte()
{
  pinMode(_dataPin, INPUT);

  byte result = 0;

  for (int i = 0; i < 8; i++)
  {
    int b = digitalRead(_dataPin);
    // reversing from big endian to little endian
    result |= b << i;
    clock();

  }

  return result;
}

void ds1302::disableWriteProtection()
{
  startData();

  writeByte(RegisterWriteProtectWrite);
  writeByte(0b00000000);

  stopData();
}

bool ds1302::isClockEnabled()
{
  startData();

  writeByte(RegisterSecondsRead);
  byte clockEnabledFlag = readByte();

  stopData();

  byte clockEnabled = (clockEnabledFlag & 0b10000000) >> 7;

  if (clockEnabled == 1)
  {
    return false;
  }

  return true;
}

void ds1302::enableClock(bool enable)
{
  if (enable == true)
  {
    if (isClockEnabled() == false)
    {
      startData();

      writeByte(RegisterSecondsWrite);
      writeByte(RegisterSecondsEnableClock);

      stopData();
    }
  }
  else
  {
    if (isClockEnabled() == true)
    {
      startData();

      writeByte(RegisterSecondsWrite);
      writeByte(RegisterSecondsDisableClock);

      stopData();
    }
  }
}

byte ds1302::getSeconds()
{
  startData();

  writeByte(RegisterSecondsRead);
  byte data = readByte();

  stopData();

  byte seconds1 = 0b00001111 & data;
  byte seconds10 = (0b01110000 & data) >> 4;

  byte totalSeconds = seconds10 * 10 + seconds1;

  return totalSeconds;
}

byte ds1302::getMinutes()
{
  startData();

  writeByte(RegisterMinutesRead);
  byte data = readByte();

  stopData();

  byte minutes1 = 0b00001111 & data;
  byte minutes10 = (0b01110000 & data) >> 4;

  byte totalMinutes = minutes10 * 10 + minutes1;

  return totalMinutes;
}

byte ds1302::getHour()
{
  startData();

  writeByte(RegisterHourRead);
  byte data = readByte();

  stopData();

  byte hours1 = 0b00001111 & data;
  byte hours10 = 0;

  byte hourModeFlag = (0b10000000 & data) >> 7;

  if (hourModeFlag == 1)
  {
    hours10 = (0b00010000 & data) >> 4;
  }
  else
  {
    hours10 = (0b00110000 & data) >> 4;
  }

  byte totalHours = hours10 * 10 + hours1;

  return totalHours;
}

byte ds1302::getDate()
{
  startData();

  writeByte(RegisterDateRead);
  byte data = readByte();

  stopData();

  byte date1 = 0b00001111 & data;
  byte date10 = (0b00110000 & data) >> 4;

  byte date = date10 * 10 + date1;

  return date;
}

byte ds1302::getMonth()
{
  startData();

  writeByte(RegisterMonthRead);
  byte data = readByte();

  stopData();

  byte month1 = 0b00001111 & data;
  byte month10 = (0b00010000 & data) >> 4;

  byte month = month10 * 10 + month1;

  return month;
}

byte ds1302::getDay()
{
  startData();

  writeByte(RegisterDayRead);
  byte data = readByte();

  stopData();

  byte day = 0b00000111 & data;

  return day;
}

byte ds1302::getYear()
{
  startData();

  writeByte(RegisterYearRead);
  byte data = readByte();

  stopData();

  byte year1 = 0b00001111 & data;
  byte year10 = (0b11110000 & data) >> 4;

  byte year = year10 * 10 + year1;

  return year;
}

void ds1302::setSeconds(byte seconds)
{
  byte seconds1 = seconds % 10;
  byte seconds10 = seconds / 10;

  byte message = seconds10 << 4;
  message |= 0b00001111 & seconds1;

  startData();

  writeByte(RegisterSecondsWrite);
  writeByte(message);

  stopData();
}

void ds1302::setMinutes(byte minutes)
{
  byte minutes1 = minutes % 10;
  byte minutes10 = minutes / 10;

  byte message = minutes10 << 4;
  message |= 0b00001111 & minutes1;

  startData();

  writeByte(RegisterMinutesWrite);
  writeByte(message);

  stopData();
}

ds1302::HourMode ds1302::getHourMode()
{
  startData();

  writeByte(RegisterHourRead);
  byte data = readByte();

  stopData();

  HourMode result = HourMode::Mode24;

  byte hourModeFlag = (0b10000000 & data) >> 7;

  if (hourModeFlag == 1)
  {
    byte pmFlag = (0b00100000 & data) >> 5;

    if (pmFlag == 1)
    {
      result = HourMode::PM;
    }
    else
    {
      result = HourMode::AM;
    }
  }

  return result;
}

void ds1302::setHour(byte hour)
{
  if (hour > 23)
  {
    return;
  }

  HourMode hourMode = getHourMode();

  byte AMPMFlag = 0;

  if (hourMode != HourMode::Mode24)
  {
    if (hour > 12)
    {
      hour -= 12;
      AMPMFlag = 0b10100000;
    }
  }

  byte hour1 = hour % 10;
  byte hour10 = hour / 10;

  byte message = hour10 << 4;

  message |= (0b00001111 & hour1);

  if (hourMode != HourMode::Mode24)
  {
    message |= (0b10100000 & AMPMFlag);
  }

  startData();

  writeByte(RegisterHourWrite);
  writeByte(message);

  stopData();
}

void ds1302::setDate(byte date)
{
  if (date == 0 || date > 31)
  {
    return;
  }

  byte date1 = date % 10;
  byte date10 = date / 10;

  byte message = date10 << 4;
  message |= 0b00001111 & date1;

  startData();

  writeByte(RegisterDateWrite);
  writeByte(message);

  stopData();
}

void ds1302::setMonth(byte month)
{
  if (month == 0 || month > 12)
  {
    return;
  }

  byte month1 = month % 10;
  byte month10 = month / 10;

  byte message = month10 << 4;
  message |= 0b00001111 & month1;

  startData();

  writeByte(RegisterMonthWrite);
  writeByte(message);

  stopData();
}

void ds1302::setDay(byte day)
{
  if (day == 0 || day > 7)
  {
    return;
  }

  startData();

  writeByte(RegisterDayWrite);
  writeByte(day);

  stopData();
}

void ds1302::setYear(byte year)
{
  if (year > 99)
  {
    return;
  }

  byte year1 = year % 10;
  byte year10 = year / 10;

  byte message = year10 << 4;
  message |= 0b00001111 & year1;

  startData();

  writeByte(RegisterYearWrite);
  writeByte(message);

  stopData();
}

void ds1302::set24HourMode(bool hourMode24)
{
  byte message = 0b10000000;

  if (hourMode24 == true)
  {
    message = 0;
  }

  startData();

  writeByte(RegisterHourWrite);
  writeByte(message);

  stopData();
}

byte ds1302::readRam(RamPage page, uint8_t addressIndex)
{
  if (addressIndex > 7 || (page == RamPage::F && addressIndex > 6))
  {
    return 0;
  }

  addressIndex *= 2;
  ++addressIndex;

  byte targetAddress = page;
  targetAddress += addressIndex;

  startData();

  writeByte(targetAddress);
  byte data = readByte();

  stopData();

  return data;
}

void ds1302::writeRam(RamPage page, uint8_t addressIndex, byte data)
{
  if (addressIndex > 7 || (page == RamPage::F && addressIndex > 6))
  {
    return;
  }

  addressIndex *= 2;

  byte targetAddress = page;
  targetAddress += addressIndex;

  startData();

  writeByte(targetAddress);
  writeByte(data);

  stopData();
}
