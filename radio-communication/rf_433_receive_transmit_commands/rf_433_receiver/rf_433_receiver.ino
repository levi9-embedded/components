/*  Receive one of four different commands and:
 *  Command 1: Turn off led on pin 13
 *  Command 2: Turn on led on pin 13
 *  Command 3: Blink led on pin 13
 *  Command 4: Blink led as SOS signal on pin 13  
 *
 */

// https://github.com/sparkfun/RF_Links/tree/main/Firmware/Arduino/examples

// RF LINK RECEIVER LIBRARY
#include <RH_ASK.h>

RH_ASK driver(2000, 2, 3, 0); //2000bps, rxPin = 2, txPin = 3

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
  Serial.println("Initialize RF Link Rx Code");

  driver.init();

  //Set pin for LED as status indicator
  pinMode (13, OUTPUT);
}

void morseCodeDot()
{
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
}

void morseCodeDash()
{
  digitalWrite(13, HIGH);
  delay(300);
  digitalWrite(13, LOW);
  delay(100);
}

void sendSos()
{
  // SOS
  // ...---...

  // set initial state
  digitalWrite(13, LOW);

  morseCodeDot();
  morseCodeDot();
  morseCodeDot();

  morseCodeDash();
  morseCodeDash();
  morseCodeDash();

  morseCodeDot();
  morseCodeDot();
  morseCodeDot();
}

void loop()
{
  //Set buffer array based on max message length
  uint8_t buff[RH_ASK_MAX_MESSAGE_LEN];

  //Set variable to indicate buffer length
  uint8_t buffLen = sizeof(buff);

  if (driver.recv(buff, &buffLen)) // Non-blocking
  {
    // Message with a good checksum received.
    Serial.print("Received message: ");

    buff[buffLen] = 0;

    Serial.println((char*)buff);

    const int recievedValue = atoi((char*)buff);

    switch(recievedValue)
    {
      case commands::command1:
        Serial.println("recieved command1 Led off");
        digitalWrite(13, LOW);
        break;
      case commands::command2:
        Serial.println("recieved command2 Led on");
        digitalWrite(13, HIGH);
        break;
      case commands::command3:
        Serial.println("recieved command3 Blink");
        digitalWrite(13, LOW);
        delay(100);
        digitalWrite(13, HIGH);
        delay(200);
        digitalWrite(13, LOW);
        break;
      case commands::command4:
        Serial.println("recieved command4 SOS");
        sendSos();
        break;
      default:
        Serial.println("recieved unknown command");
        break;
    }

    delay(100);
  }
}