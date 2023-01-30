/* Display animation with with dot matrix module where:
 * - Display starts blank
 * - One dot runs through all 64 led's
 */

#include <SPI.h>

const int chipSelectPin = 7;

class DotMatrix {
  public:
    DotMatrix() {

    }

  private:
};

void setup() {
  SPI.begin();

  pinMode(chipSelectPin, OUTPUT);

  delay(100);

  write(0x0C, 0x01); // Shutdown register, Normal operation

  write(0x0F, 0x00); // Display test register, Test display

  write(0x0B, 0x07); // Scan limit, Display digits 0, ..., 7

  write(0x09, 0x00); // Decode mode register, No decode for digits 7 - 0

  write(0x01, 0xFF); // Digit 0 register, set all
  write(0x02, 0xFF); // Digit 1 register, set all
  write(0x03, 0xFF); // Digit 2 register, set all
  write(0x04, 0xFF); // Digit 3 register, set all
  write(0x05, 0xFF); // Digit 4 register, set all
  write(0x06, 0xFF); // Digit 5 register, set all
  write(0x07, 0xFF); // Digit 6 register, set all
  write(0x08, 0xFF); // Digit 7 register, set all
}

void write(uint8_t reg, uint8_t data) {
  digitalWrite(chipSelectPin, LOW);

  SPI.transfer(reg); 
  SPI.transfer(data); 

  digitalWrite(chipSelectPin, HIGH);
}

void loop() {


}
