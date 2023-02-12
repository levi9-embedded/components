//------------------------------
// 
// DHT11 library source file
//------------------------------

#include "dht11.h"

dht11::dht11():_temperature(0),
               _humidity(0)
{ /*c'tor*/ };

dht11::stateChangeOrTimeout(uint16_t timePeriod, const uint8_t pin, const uint16_t state)
{
  uint32_t startTime = micros();
  while(digitalRead(pin) == state)
  {
    if((micros()-startTime) > timePeriod) return DHTLIB_TIMEOUT;
  }
  
  return DHTLIB_STATE_CHANGED;
}
			
dht11::readData(const uint8_t pin)
{
  byte receiveBuffer[5];
  uint8_t  idx = 0;
  uint8_t  bit = 7;

  for(int i=0; i<5; i++) receiveBuffer[i] = 0;

  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delay(18);
  digitalWrite(pin, HIGH);
  delayMicroseconds(40);
  pinMode(pin, INPUT);

  if(stateChangeOrTimeout(80, pin, LOW)  != DHTLIB_STATE_CHANGED) return DHTLIB_TIMEOUT;
  if(stateChangeOrTimeout(80, pin, HIGH) != DHTLIB_STATE_CHANGED) return DHTLIB_TIMEOUT;

  for(int i=0; i<40; i++)
  {
    if(stateChangeOrTimeout(50, pin, LOW) != DHTLIB_STATE_CHANGED) return DHTLIB_TIMEOUT;

    delayMicroseconds(28);
    
    if(digitalRead(pin) == HIGH)
    {
      receiveBuffer[idx] |= (1 << bit);
      
      if(stateChangeOrTimeout(70, pin, HIGH) != DHTLIB_STATE_CHANGED) return DHTLIB_TIMEOUT;
    }
    
    if(bit == 0)
    {
      bit = 7;
      idx++;
      continue;
    }
    bit--;
  }
  
  byte checksum = 0;
  for (int i=0; i<4; i++) checksum += receiveBuffer[i];

  if(checksum != receiveBuffer[4]) return DHTLIB_CHECKSUM_ERROR;
  
  _humidity    = receiveBuffer[0] + ((float)receiveBuffer[1] / 100);
  _temperature = receiveBuffer[2] + ((float)receiveBuffer[3] / 100);

  return DHTLIB_OK;
};

			   
