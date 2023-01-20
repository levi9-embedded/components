# Usage

See rtc-library.ino for examples.

ds1302 class needs three pins CLK ( SCLK ), DAT ( I/O ) and RST ( CE )

Library must first initialized by calling init() to configure arduino pins.

For function explanation see ds1302.h

We can set/read date, time and RAM data from ds1302

Note: when battery is removed all RAM data is lost but date/time is not reset.

