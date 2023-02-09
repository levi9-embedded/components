/* Show a display that contains empty rectangles for all characters.
 * Make it so that these rectangles are replaced with filled and back
 * every half second.  
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

byte borderRectangle[8] = {
  B01111,
  B01001,
  B01001,
  B01001,
  B01001,
  B01001,
  B01001,
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

  lcd.createChar(0, borderRectangle); // Create a custom character
  lcd.createChar(1, fullRectangle);

  lcd.clear();
  lcd.backlight();
}

void loop() {
  lcd.clear();
  
  for(int i = 0; i <= 15; i++)
  {
    for(int j = 0; j <= 1; j++)
    {
      lcd.setCursor(i,j);
      lcd.write(byte(0)); //byte(0) represents borderRectangle char - look up to its init in setup function
    }
  }

  delay(500);
  lcd.clear();

  for(int i = 0; i <= 15; i++)
  {
    for(int j = 0; j <= 1; j++)
    {
      lcd.setCursor(i,j);
      lcd.write(byte(1));
    }
  }

  delay(500);
}
