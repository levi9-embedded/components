/*  When knock is detected, count number of knocks 
 *  performed within 5 seconds of first knock and 
 *  show on serial monitor. 
 *
 */

#define KNOCK_SENSOR A0   // the piezo is connected to analog pin 0
#define THRESHOLD 14 // threshold value to decide when the detected sound is a knock or not
#define KNOCK_SESSION_INTERVAL_MILLI 5000

int sensorReading = 0;  // variable to store the value read from the sensor pin
int numberOfKnocksInSession = 0;
unsigned long startKnockSessionTimeMillis = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {

  sensorReading = analogRead(KNOCK_SENSOR);  // read the sensor and store it in the variable sensorReading:

  /*
    millis() - Returns the number of milliseconds passed since the Arduino board began running the current program. This number will overflow (go back to zero), after approximately 50 days.
  */
  if(startKnockSessionTimeMillis != 0 && (millis() - startKnockSessionTimeMillis) > KNOCK_SESSION_INTERVAL_MILLI)
  {
    Serial.print("Number of knocks occured in this session: ");
    Serial.println(numberOfKnocksInSession);

    numberOfKnocksInSession = 0;
    startKnockSessionTimeMillis = 0;
  }
  
  if (sensorReading >= THRESHOLD) 
  {
    if(numberOfKnocksInSession == 0)
    {
      startKnockSessionTimeMillis = millis();
      numberOfKnocksInSession++;
      Serial.print("The first knock detected. Starting a session of ");
      Serial.print(KNOCK_SESSION_INTERVAL_MILLI/1000);
      Serial.println(" seconds.");
    }
    else
    {
      numberOfKnocksInSession++;
    }
  }
  
  delay(100);  // delay to avoid overloading the serial port buffer
}