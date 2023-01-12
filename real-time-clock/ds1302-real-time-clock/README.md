# DS1302 

DS1302 trickle-charge timekeeping chip contains a real-time clock/calendar and 31 bytes of static RAM.

It communicates with a microprocessor via a simple serial interface.

The real-time clock/calendar provides seconds, minutes, hours, day, date, month, and year information. The end of the month date is automatically adjusted for months with fewer than 31 days, including corrections for leap year. The clock operates in either the 24-hour or 12-hour format with an AM/PM indicator.

<img src="https://user-images.githubusercontent.com/5618092/212041017-bf7b8c45-7256-42f8-b25f-195c0174f2d2.png" width="200"  />

It has following pins:

| PIN | Description |
| --- | ----------- |
| VCC | Power supply |
| GND | Ground |
| CLK | Input for synchronizing data movement |
| DAT | Input/Output data |
| RST | Value must be high during read/write operations (chip enabled) |

Data sheet for DS1302 is provided in repository.

TODO: Describe how to connect it with Arduino.

