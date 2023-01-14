/*  Perform continuos movement from inital position of 0 deg, to 90 deg
 *  in duration of 5 second. Then move to 180 degrees, wait 5 seconds,
 *  perform continuos movement from 180 deg to 90 degrees, and finally
 *  move to 0 degrees and wait 5 seconds. Loop this behavior.
 */

#include <Servo.h>

//-----------------------------------------------------------------------------------------------|100

int angle = 0;
int delay_to_90_degrees = 56; // (5 seconds) 5 000 miliseconds / 90 degrees = 56 miliseconds

Servo my_servo;

//-----------------------------------------------------------------------------------------------|100

void setup () 
{  
  my_servo.attach (9);
  my_servo.write (0);
}

//-----------------------------------------------------------------------------------------------|100

void loop () 
{
  // Initial delay 3s.
  delay (3000);

  // Move to pos 90 degrees in a period of 5s.
  for (angle = 0; angle <= 90; angle++)
  {
    delay (delay_to_90_degrees);
    my_servo.write (angle);
  }

  // Wait for 5s and then move to pos 180 degrees.
  delay (5000);
  my_servo.write (180);
  
  // Wait for 5s and then move to pos 90 degrees in a period of 5s.
  delay (5000);
  for (angle = 180; angle >= 90; angle--)
  {
    delay (delay_to_90_degrees);
    my_servo.write (angle);
  }

  // Wait for 5s and then move to (initial) pos 0 degrees.
  delay (5000);
  my_servo.write (0);
}

//-----------------------------------------------------------------------------------------------|100
