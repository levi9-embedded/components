/* Example of DS1302 library usage */

#include "ds1302.h"

ds1302 ds(7, 2, 4);

void setup()
{
  Serial.begin(9600);

  // init and enableClock are mandatory to call first
  ds.init();
  ds.enableClock(true);

  // example of setting custom date and time
  ds.setSeconds(17);
  ds.setMinutes(3);

  // regardless of hour mode AM/PM or 24 mode
  // we always set hour using 24h format
  ds.setHour(22);

  ds.setDate(22);
  ds.setMonth(2);
  ds.setYear(23);
  ds.setDay(4);
}

void testReadData()
{
  byte seconds = ds.getSeconds();
  byte minutes = ds.getMinutes();
  byte hour = ds.getHour();
  byte date = ds.getDate();
  byte month = ds.getMonth();
  byte year = ds.getYear();
  byte day = ds.getDay();
  ds1302::HourMode hourMode = ds.getHourMode();

  Serial.print(date);
  Serial.print("/");
  Serial.print(month);
  Serial.print("/");
  Serial.print(year);
  Serial.print(" ");
  Serial.print(hour);
  Serial.print(":");
  Serial.print(minutes);
  Serial.print(":");
  Serial.print(seconds);

  if (hourMode == ds1302::HourMode::AM)
  {
    Serial.print(" ");
    Serial.print("AM");
  }
  else if (hourMode == ds1302::HourMode::PM)
  {
    Serial.print(" ");
    Serial.print("PM");
  }

  Serial.print(" ");
  Serial.print(day);

  Serial.println();
}

void loop()
{
  testReadData();

  // Note: DS1302 memory is separated to C,D,E and F pages
  // For pages C,D and E addressIndex range 0 - 7
  // For page F addressIndex range 0 - 6
  // Total DS1302 memory 31 bytes

  // read from DS1302 memory
  byte data = ds.readRam(ds1302::RamPage::C, 1);

  Serial.print("RamPage C index 1 value ");
  Serial.println(data);

  ++data;

  // write new data to DS1302 memory
  ds.writeRam(ds1302::RamPage::C, 1, data);

  delay(500);
}
