
/*
 * Display a dot-matrix compass.
 */

#include <SPI.h>
#include <QMC5883LCompass.h>

//------------------------------------------------------------------------------------------------|100

#define CS           0x03
#define DECODE_MODE  0x09 
#define INTENSITY    0x0A
#define SCAN_LIMIT   0x0B 
#define SHUTDOWN     0x0C
#define DISPLAY_TEST 0x0F

QMC5883LCompass oCompass;

const byte qmc5883l_mode_cont = 0x01; // Mode Control (MODE)
const byte qmc5883l_odr_200hz = 0x0C; // Output Data Rate (ODR)
const byte qmc5883l_rng_8g    = 0x10; // Full Scale Range (RNG)
const byte qmc5883l_osr_512   = 0x00; // Over Sample Ratio (OSR)

//------------------------------------------------------------------------------------------------|100

byte Arrow_North [8]={
B00000000,
B00000000,
B00000100,
B01111110,
B01111110,
B00000100,
B00000000,
B00000000};

byte Arrow_West [8]={
B00000000,
B00011000,
B00111100,
B00011000,
B00011000,
B00011000,
B00011000,
B00000000};

byte Arrow_South [8]={
B00000000,
B00000000,
B00100000,
B01111110,
B01111110,
B00100000,
B00000000,
B00000000};

byte Arrow_East [8]={
B00000000,
B00011000,
B00011000,
B00011000,
B00011000,
B00111100,
B00011000,
B00000000};

byte Arrow_NorthWest [8]={
B00000000,
B00001110,
B00000110,
B00001010,
B00010000,
B00100000,
B01000000,
B00000000};

byte Arrow_NorthEast [8]={
B00000000,
B01000000,
B00100000,
B00010000,
B00001010,
B00000110,
B00001110,
B00000000};

byte Arrow_SouthEast [8]={
B00000000,
B00000010,
B00000100,
B00001000,
B01010000,
B01100000,
B01110000,
B00000000};

byte Arrow_SouthWest [8]={
B00000000,
B01110000,
B01100000,
B01010000,
B00001000,
B00000100,
B00000010,
B00000000};

//------------------------------------------------------------------------------------------------|100

void SendData(uint8_t address, uint8_t value) 
{
  digitalWrite(CS, LOW);   
  SPI.transfer(address);  // Send address.
  SPI.transfer(value);    // Send the value.
  digitalWrite(CS, HIGH); // Finish transfer.
}

//------------------------------------------------------------------------------------------------|100

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

  //----------------------------------------------------------------------------------------------|100

  Serial.begin(9600);
  
  oCompass.init();
}

//------------------------------------------------------------------------------------------------|100

void loop()  
{
  int value_x = 0;
  int value_y = 0;
  int value_z = 0;
  int azimuth = 0; // 0 - 359 degrees.

  byte bearing = 0; // 0 - 15 (N, NNE, NE, ENE, E, ...).

  char szDirection [4]   = {0};
  char szMsg       [100] = {0};

  //----------------------------------------------------------------------------------------------|100

  oCompass.read();

  value_x = oCompass.getX();
  value_y = oCompass.getY();
  value_z = oCompass.getZ();
  azimuth = oCompass.getAzimuth();

  bearing = oCompass.getBearing(azimuth);

  oCompass.getDirection(szDirection, azimuth);
  szDirection[3] = '\0';

  //----------------------------------------------------------------------------------------------|100

  sprintf (szMsg, "Coord >> X=[%6d] Y=[%6d] Z=[%6d] Azimuth=[%3d] Bearing=[%02hu] Direction=[%s]", 
            value_x, value_y, value_z, azimuth, bearing, szDirection);

  Serial.println(szMsg);

  //----------------------------------------------------------------------------------------------|100

  int i = 0;

  switch (bearing)
  {
    case 0:
    {
      for (i = 1; i < 9; i++)
        SendData (i, Arrow_North[i-1]);
    }
    break;

    case 1:
    case 2:
    case 3:
    {
      for (i = 1; i < 9; i++)   
        SendData (i, Arrow_NorthEast[i-1]);
    }
    break;

    case 4:
    {
      for (i = 1; i < 9; i++)   
        SendData (i, Arrow_East[i-1]);
    }
    break;

    case 5:
    case 6:
    case 7:
    {
      for (i = 1; i < 9; i++)   
        SendData (i, Arrow_SouthEast[i-1]);
    }
    break;

    case 8:
    {
      for (i = 1; i < 9; i++)   
        SendData (i, Arrow_South[i-1]);
    }
    break;

    case 9:
    case 10:
    case 11:
    {
      for (i = 1; i < 9; i++)   
        SendData (i, Arrow_SouthWest[i-1]);
    }
    break;

    case 12:
    {
      for (i = 1; i < 9; i++)   
        SendData (i, Arrow_West[i-1]);
    }
    break;

    case 13:
    case 14:
    case 15:
    { 
      for (i = 1; i < 9; i++)   
        SendData (i, Arrow_NorthWest[i-1]);
    }
    break;

    default:
      break;
  }

  delay(1000);
}

//-----------------------------------------------------------------------------------------------|100
