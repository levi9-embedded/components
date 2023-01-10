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