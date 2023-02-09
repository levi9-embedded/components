/* Show five messages on screen in a sequence, with 3 seconds of delay
 * after each. Messages that are longer that one line (16 chars) should
 * continue on second line. Repeat this.
*/

#define ARRAYSIZE 5
#define ROW_LENGTH 16
#define LCD_MAX_LENGTH 32

//#include <LiquidCrystal.h> (Paralel connection)
#include <LiquidCrystal_I2C.h>


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


String messages[ARRAYSIZE] = { "First sentence", "The second one, I am longer", "My name is 3rd sentence, I come from family of long sentences, nice to meet you!", "4th sentc", "Hello, 5th" };

void setup() {
  //lcd.begin(16, 2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display (Paralel connection)
  lcd.init(); // Instead of "lcd.begin()" in Serial connection lcd.init() is used.

  lcd.clear();
  lcd.backlight();
}

void loop() {
    for (int i=0; i < ARRAYSIZE; i++)
    {
        String message = messages[i];

        showMessage(message);

        delay(3000);
    }
}

void showMessage(String message)
{
    if(message.length() < ROW_LENGTH)
    {
      showMessageInSingleRow(message); 
    }
    else if(message.length() < LCD_MAX_LENGTH)
    {
      showMessageInTwoRows(message);
    }
    else
    {
      showMessageAsMovingText(message); 
    }
}

void showMessageInSingleRow(String message)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message); 
}

void showMessageInTwoRows(String message)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(message.substring(0,ROW_LENGTH)); // Arduino - StringSubstring
  lcd.setCursor(0,1);
  lcd.print(message.substring(ROW_LENGTH,message.length()));
}

void showMessageAsMovingText(String message)
{
  lcd.clear();
  

  for(int i = 0; i < message.length() ; i++)
  {
    lcd.clear();

    lcd.setCursor(0, 0);
    int messageEndIndexForFirstRow = i + ROW_LENGTH;
    lcd.print(message.substring(i, messageEndIndexForFirstRow));
    
    lcd.setCursor(0, 1);
    int messageEndIndexForSecondRow = messageEndIndexForFirstRow + ROW_LENGTH;

    if(messageEndIndexForSecondRow < message.length())
      lcd.print(message.substring(messageEndIndexForFirstRow, messageEndIndexForSecondRow));
    else   
      lcd.print(message.substring(messageEndIndexForFirstRow, message.length()));         
    
    delay(200); 
  }  
}


