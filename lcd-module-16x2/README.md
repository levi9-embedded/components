# 16x2 LCD module

## About module

An LCD character display is a unique type of display that can only output individual ASCII characters with fixed size. Using these individual characters then we can form a text.

If we take a closer look at the display we can notice that there are small rectangular areas composed of 5×8 pixels grid. Each pixel can light up individually, and so we can generate characters within each grid.

The number of the rectangular areas define the size of the LCD. The most popular LCD is the 16×2 LCD, which has two rows with 16 rectangular areas or characters. Of course, there are other sizes like 16×1, 16×4, 20×4 and so on, but they all work on the same principle. Also, these LCDs can have different background and text color.




## Pins 
### Pins of 16x2 LCD component (Parallel connection)

![Parallel pins](https://howtomechatronics.com/wp-content/uploads/2015/07/LCD-Display-Tutorial.png?ezimgfmt=ng:webp/ngcb2)


Pin name    | Description
------------- | -------------
GND           | Negative system power supply (Ground)
VCC           | System power supply positive (Input for 5V voltage from Arduino board)
V0            | Vo is pin on which we can attach a potentiometer for controlling the contrast of the display
RS            | The RS pin or register select pin is used for selecting whether we will send commands or data to the LCD. Low state -> Commands (set cursor position, clear display, etc...), High state -> Data.
R/W           | The R/W pin which selects the mode whether we will read or write to the LCD. (Read mode is used by LCD itself)
E             | The E pin enables or disables the writing to the registers
D0-D7         | Each D* input represents 1 bit of data, so with these 8 bits we are sending an information what should be written on the device. (Example: if we want to see the latter uppercase A on the display we will send 0100 0001 to the registers according to the ASCII table)
A,K           | Anode and Cathode are for the LED backlight.
  

### Pins of 16x2 LCD component I2C Adapter (Serial Connection)

![Serial pins](https://cdn.shopify.com/s/files/1/0300/6424/6919/files/I2C-Serial-Interface-Adapter-Module_600x600.jpg?v=1588531223)

Pin name    | Description
------------- | -------------
GND           | Negative system power supply (Ground)
VCC           | System power supply positive (Input for 5V voltage from Arduino board)
SDA           | IIC Serial Data 
SCL           | IIC Serial Clock

**Additionaly it has integrated Potentiometer wich help of we can control contrast of LCD display.*


## Connection

### With parallel connection

![Parallel connection](https://howtomechatronics.com/wp-content/uploads/2015/07/LCD-Display_Transparent03.png?ezimgfmt=ng:webp/ngcb2)

**After connection: With potentiometer control brightness of characters on LCD display*

### With serial connection

![Serial connection](https://www.makerguides.com/wp-content/uploads/2019/02/I2C-LCD-with-Arduino-Wiring-Diagram-Schematic-Pinout.jpg)


## Library used 

### Paralel Connection

Arduino's [LiquidCrystal library](https://www.arduino.cc/reference/en/libraries/liquidcrystal/) is used.

### Serial Connection

For serial connection used library can be found on (https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library). 

We can import it within two ways:
* Go to the link and download the library Arduino-LiquidCrystal-I2C-library. Then open Arduino IDE and go to Sketch>Include Library> Add.ZIP Library. Next select the downloaded ZIP file and click open.
* Import it using Arduino IDE and its library manager. Try to find library by *fdebrabander*.

Additional thing you need to do before implementing solutions with LCD screen with Serial connection is finding addres of L2C adapter. You can find it using helper script located on "tools\find_i2c_addres.ino".
## References

 - [Arduino 16×2 LCD Tutorial – Everything You Need to Know](https://howtomechatronics.com/tutorials/arduino/lcd-tutorial/)
 - [Interface I2C 16x2 LCD with Arduino Uno (Just 4 wires)](https://www.hackster.io/akshayjoseph666/interface-i2c-16x2-lcd-with-arduino-uno-just-4-wires-273b24)
