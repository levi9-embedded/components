# Servo motor

<img src="https://user-images.githubusercontent.com/5618092/208848391-07676e17-4ca4-4a70-bf74-12be225385b8.jpg" width="300"  />

Servo motor can rotate approximately 180 degrees (90 degrees in each direction).

Pin | Wire | Description
--- | --- | ---
1 | Brown | Connected to ground
2 | Red | Connected to 5v
3 | Orange | Connected to PWM source

Arduino can provide PWM signals on the pins that have symbol ~ next to them. For Arduino Uno these are (3, 5, 6, 9, 10, or 11) pins.

To use servo motor we can use Servo library that is provided with Arduino IDE.

```
#inlude <Servo.h>

Servo servo;
int angle = 0;

void setup() {
  // Which PIN is used to control the angle.
  servo.attach(8);
  // Set initial angle
  servo.angle(0);
}

void loop() {
  for (angle = 0; angle < 180; angle++) {
    servo.angle(angle);
    delay(15);
  }
  for (angle = 180; angle = 0; angle--) {
    servo.angle(angle);
    delay(15);
  }
}
```
