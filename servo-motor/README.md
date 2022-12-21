# Servo motor

<img src="https://user-images.githubusercontent.com/5618092/208848391-07676e17-4ca4-4a70-bf74-12be225385b8.jpg" width="300"  />

Servo motor can rotate approximately 180 degrees (90 degrees in each direction).

Pin | Wire | Description
--- | --- | ---
1 | Brown | Connected to ground
2 | Red | Connected to 5v
3 | Orange | Connected to PWM source

PWM - Power Width Modulation

To control the position of the servo motor we need to use arduino output that has the ability to provide PWM signal. That means that in addition of providing 0v and 5v on the pin, it can also provide signal that periodically alternates between 0v and 5v.

<img src="https://user-images.githubusercontent.com/5618092/208847188-f6adc689-a070-4238-a54b-ee0c6db17b41.png" width="500"  />
