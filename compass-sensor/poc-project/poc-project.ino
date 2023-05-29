
#include <QMC5883LCompass.h>

//------------------------------------------------------------------------------------------------|100

QMC5883LCompass oCompass;

const byte qmc5883l_mode_cont = 0x01; // Mode Control (MODE)
const byte qmc5883l_odr_200hz = 0x0C; // Output Data Rate (ODR)
const byte qmc5883l_rng_8g    = 0x10; // Full Scale Range (RNG)
const byte qmc5883l_osr_512   = 0x00; // Over Sample Ratio (OSR)

//------------------------------------------------------------------------------------------------|100

void setup() 
{
  Serial.begin(9600);
  
  oCompass.init();
  //oCompass.setCalibration(-861, 1657, -1566, 1253, -1341, 1415);
  oCompass.setCalibration(-746, 1698, -1532, 1233, -1341, 1433);
  //oCompass.setCalibration(-915, 1660, -1695, 1077, -1277, 1420);
  

}

//------------------------------------------------------------------------------------------------|100

void loop() 
{
  int value_x = 0;
  int value_y = 0;
  int value_z = 0;
  int azimuth = 0; // 0 - 359 degrees.

  byte bearing = 0; // 0 -15 (N, NNE, NE, ENE, E, ...).

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

  delay (200);
}

//------------------------------------------------------------------------------------------------|100

