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

    void lightOn(byte row, int column) {
      if (row > 8 && column > 8) return;

      auto col = 0x80 >> (column - 1);

      write(row, static_cast<uint8_t>(col));
    }

    void clearDisplay() {
      for (uint8_t row = 0x01; row <= 0x08; row++) {
        write(row, 0x00);
      }      
    }

    void setup() {
      SPI.begin();
      
      pinMode(chipSelectPin, OUTPUT);

      delay(100);

      write(0x0C, 0x01); // Shutdown register, Normal operation
      write(0x0F, 0x00); // Display test register, Normal display
      write(0x0B, 0x07); // Scan limit register, Display digits 0, ..., 7
      write(0x09, 0x00); // Decode mode register, No decode for digits 7 - 0
    }

  private:
    void write(uint8_t reg, uint8_t data) {
      digitalWrite(chipSelectPin, LOW);

      SPI.transfer(reg); 
      SPI.transfer(data); 

      digitalWrite(chipSelectPin, HIGH);
    }
};

DotMatrix dotMatrix;

void setup() {
  dotMatrix.setup();
  dotMatrix.clearDisplay();
}

void loop() {
  for (byte row = 1; row <= 8; row++) {
    for (byte column = 1; column <= 8; column++) {
      dotMatrix.lightOn(row, column);
      delay(200);
    }    
    dotMatrix.clearDisplay();
  }  
}
