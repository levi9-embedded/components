/*  Display on the serial port current temperature and humidity
 *  every five seconds.
 *
 */
#include "dht11.h"

const uint8_t DHT11pin = 8;

dht11 DHT11;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int retVal = DHT11.readData(DHT11pin);

  if(retVal == DHTLIB_CHECKSUM_ERROR)
  {
    Serial.println("Checksum ERROR!");
  }
  else if(retVal == DHTLIB_TIMEOUT)
  {
    Serial.println("Communication TIMED OUT!");
  }
  else
  {
    Serial.print("Temperature: ");
    Serial.print(DHT11.getTemperature());
    Serial.println(" C");

    Serial.print("Humidity: ");
    Serial.print(DHT11.getHumidity());
    Serial.println(" %");
  }
 
  delay(5000);
}