//------------------------------
// 
// DHT11 library header file
//------------------------------

#ifndef dht11_h
#define dht11_h

#include <Arduino.h>

#define DHTLIB_OK              0
#define DHTLIB_STATE_CHANGED   1
#define DHTLIB_CHECKSUM_ERROR -1
#define DHTLIB_TIMEOUT        -2

class dht11
{
  private:
    float _temperature;
    float _humidity;
    int   stateChangeOrTimeout(uint16_t timePeriod, const uint8_t pin, const uint16_t state);
	
  public:
    dht11();

    //Read data from DHT11 sensor
	  int readData(const uint8_t pin);
	
    //Get temperature value read from DHT11 sensor
	  float getTemperature() 
    {
      return _temperature;
    }
    //Get humidity value read from DHT11 sensor
	  float getHumidity()
    {
      return _humidity;
    }
};

#endif