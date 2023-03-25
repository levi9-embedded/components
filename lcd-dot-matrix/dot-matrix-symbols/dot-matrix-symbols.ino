/*
 * Display various symbols, letters and numbers w/ as dot-matrix patterns.
 */

#include <SPI.h>

//-----------------------------------------------------------------------------------------------|100

#define CS           0x03
#define DECODE_MODE  0x09 
#define INTENSITY    0x0A
#define SCAN_LIMIT   0x0B 
#define SHUTDOWN     0x0C
#define DISPLAY_TEST 0x0F

//-----------------------------------------------------------------------------------------------|100

byte Plus [8]={
B00000000, 
B00011000, 
B00011000, 
B01111110, 
B01111110, 
B00011000, 
B00011000, 
B00000000};

byte Division [8]={
B00000000,
B01100000,
B00110000,
B00011000,
B00001100,
B00000110,
B00000010,
B00000000};

byte Minus [8]={
B00000000,
B00011000,
B00011000,
B00011000,
B00011000,
B00011000,
B00011000,
B00000000};

byte Multiply [8]={
B00000000,
B00000000,
B00000000,
B00011000,
B00011000,
B00000000,
B00000000,
B00000000};

byte letter_L [8]={
B00000000,
B00000000,
B01111110,
B01111110,
B01100000,
B01100000,
B00000000,
B00000000};

byte letter_E [8]={
B00000000,
B00000000,
B01111110,
B01111110,
B01001010,
B01000010,
B00000000,
B00000000};

byte letter_V [8]={
B00000000,
B00011110,
B00111110,
B01100000,
B01100000,
B00111110,
B00011110,
B00000000};

byte letter_I [8]={
B00000000,
B00000000,
B00000000,
B01111110,
B01111110,
B00000000,
B00000000,
B00000000};

byte number_9 [8]={
B00000000,
B00001100,
B01011110,
B01010010,
B01010010,
B01111110,
B00001100,
B00000000};

//-----------------------------------------------------------------------------------------------|100

void SendData(uint8_t address, uint8_t value) 
{
  digitalWrite(CS, LOW);   
  SPI.transfer(address);  // Send address.
  SPI.transfer(value);    // Send the value.
  digitalWrite(CS, HIGH); // Finish transfer.
}

//-----------------------------------------------------------------------------------------------|100

void setup()
{
  pinMode(CS, OUTPUT);  
  
  SPI.setBitOrder(MSBFIRST);   // Most significant   bit first 
  SPI.begin();                 // Start SPI
  
  SendData(DISPLAY_TEST, 0x01); // Run test - All LED segments lit.
  
  delay(1000);
  
  SendData(DISPLAY_TEST, 0x00); // Finish test mode.
  SendData(DECODE_MODE , 0x00); // Disable BCD mode. 
  SendData(INTENSITY   , 0x0e); // Use lowest intensity.   
  SendData(SCAN_LIMIT  , 0x0f); // Scan all digits.
  SendData(SHUTDOWN    , 0x01); // Turn on chip.
}

//-----------------------------------------------------------------------------------------------|100

void loop()  
{
  int i = 0;

  for (i = 1; i < 9; i++)
    SendData (i, Plus[i-1]);
  
  delay(5000);

  for (i = 1; i < 9; i++)   
    SendData (i, Minus[i-1]);

  delay(5000);

  for (i = 1; i < 9; i++)   
    SendData (i, Division[i-1]);

  delay(5000);

  for (i = 1; i < 9; i++)   
    SendData (i, Multiply[i-1]);

  delay(5000);

  for (i = 1; i < 9; i++)   
    SendData (i, letter_L[i-1]);

  delay(5000);

  for (i = 1; i < 9; i++)   
    SendData (i, letter_E[i-1]);

  delay(5000);

  for (i = 1; i < 9; i++)   
    SendData (i, letter_V[i-1]);

  delay(5000);

  for (i = 1; i < 9; i++)   
    SendData (i, letter_I[i-1]);

  delay(5000);

  for (i = 1; i < 9; i++)   
    SendData (i, number_9[i-1]);

  delay(5000);
}

//-----------------------------------------------------------------------------------------------|100
