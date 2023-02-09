/* Perform the following test sequence in loop:
 * - Start with empty screen
 * - Turn the background light on, wait 2 seconds
 * - Turn the backgrond light off, wait 2 seconds
 * - Repeat that 3 times
 * - Turn the background light on
 * - Turn on all pixels of all chars
 * - Wait 4 seconds
 * - Clear the screen
 * - Turn on each pixel for first character, wait 1 second
 * - Turn off first character, do the same for second character
 * - Do the same until last character on second line is reached
 * - Clear screen, turn off back light, wait 2 seconds
 * - Repeat
*/

//#include <LiquidCrystal.h> (Paralel connection)
#include <LiquidCrystal_I2C.h>

byte fullRectangle[8] = {
  B01111,          // B stands for binary formatter and the five numbers are the pixels
  B01111,
  B01111,
  B01111,
  B01111,
  B01111,
  B01111,
  B01111
};

/*
  Instantiate lcd screen object with I2C connector (Serial connection).

  - First parameter (0x27) represents address of I2C device
  - Second parameter (16) represents number of chars (rectangles) in single line (row).
  - Third parameter (2) represents number of rows on LCD device.
*/
LiquidCrystal_I2C lcd(0x27, 16, 2);

/*
  Instatiate lcd screen object with paralel connection.

  - First parameter (1) represents port number on Arduino board where RS input of lcd screen is connected to.
  - Second parameter (2) represents port number on Arduino board where E (enable) input of lcd screen is connected to.
  - Rest of the parameters represents active pins for data transfer (d4, d5, d6, d7) 
*/
//LiquidCrystal lcd(1, 2, 4, 5, 6, 7);

void setup() {
  //lcd.begin(16, 2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display (Paralel connection)
  lcd.init(); // Instead of "lcd.begin()" in Serial connection lcd.init() is used.
  lcd.createChar(0, fullRectangle); // Create a custom character

  lcd.clear();
  lcd.backlight();
}

void loop() {
  lcd.clear();

  for(int i = 1; i <= 3; i++)
  {
   lcd.backlight();
   delay(2000);
   lcd.noBacklight();
   delay(2000);
  }

  lcd.backlight();
  
  for(int i = 0; i <= 15; i++)
  {
    for(int j = 0; j <= 1; j++)
    {
      lcd.setCursor(i,j);
      lcd.write(byte(0)); //byte(0) represents fullRectangle char - look up to its init in setup function
    }
  }

  delay(4000);

  lcd.clear();

  for(int i = 0; i <= 15; i++)
  {
    for(int j = 0; j <= 1; j++)
    {
      lcd.clear();
      lcd.setCursor(i,j);
      lcd.write(byte(0));
      delay(1000);
    }
  }

  lcd.clear();
  lcd.noBacklight();

  delay(2000);
}
