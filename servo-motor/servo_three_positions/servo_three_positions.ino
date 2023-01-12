/* Move the servo motor sequentially to following positions:
 * - 0 degrees (min)
 * - 90 degrees
 * - 180 degrees (max)
 * Add 4 seconds delay after each position and loop continuously.
*/

#include <Servo.h>

Servo servo;

int timeout = 4000;
int controlPin = 10;

void setup() {
  servo.attach(controlPin);
}

void loop() {
  servo.write(0);
  delay(timeout);

  servo.write(90);
  delay(timeout);
  
  servo.write(180);
  delay(timeout);
}
