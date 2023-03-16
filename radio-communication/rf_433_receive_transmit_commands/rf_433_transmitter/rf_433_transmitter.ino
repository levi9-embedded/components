/*  Send four different commands to the receiver.
 *
 */

 // RF LINK RECEIVER LIBRARY
#include <RH_ASK.h>

RH_ASK driver(2000, 2, 3, 0);  //2000bps, rxPin = 2, txPin = 3

enum commands
{
    command1,
    command2,
    command3,
    command4
};

void setup()
{
  Serial.begin(9600);
  Serial.println("Initialize RF Link Tx Code");
  driver.init();

  //Set pin for LED as status indicator
  pinMode (13, OUTPUT);

  const char* firstMessage = "Hello world!";

  Serial.print("sending message = ");
  Serial.println(firstMessage);

  driver.send((uint8_t *)firstMessage, strlen(firstMessage));
  driver.waitPacketSent();
  delay(200);
}

void sendCommand(commands command)
{
  digitalWrite(13, true);  //Flash status LED to show transmitting

  char c[20];
  itoa(command, c, 10);
  driver.send((uint8_t *)c, strlen(c));
  
  Serial.print("sending message = ");
  Serial.println(c);

  driver.waitPacketSent();

  //Turn off status LED
  digitalWrite(13, false);

  delay(200);
}

void loop()
{
  sendCommand(commands::command1);
  delay(2000);

  sendCommand(commands::command2);
  delay(2000);

  sendCommand(commands::command3);
  delay(2000);

  sendCommand(commands::command4);
  delay(2000);
}
