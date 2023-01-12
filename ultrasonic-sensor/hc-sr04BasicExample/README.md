# Ultrasonic sensor basic example

Detects obstacle and try to guess distance.
Data is sent over serial port.

# Observations

While hc-sr04 is ok for detecting and semi precise mesuring on small distances
it is not recomended for measuring/detecting longer distances ( > 50 cm )
Targeted surface need to be at right angle or readings will get erratic, becuase
hc-sr04 fire sound, sound is bounced from targeted surface and hc-sr04 catches this sound,
if we are not at appropriate angle, sound will never come back to hc-sr04.
