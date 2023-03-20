/*  
 * If light is less then threshold => Turn on light
 * If light is more then threshold => Turn off light
 * If light is on more then X milliseconds => Turn off light
 */

#define LIGHT_SENSOR A0   // the light sensor is connected to analog pin 0
#define LED_OUT 13 // integrated led which will be used as "night-lamp"
#define LIGHT_ON_INTERVAL_MILLI 5000 // Defined interval until "night-lamp overheat", value is represented in milliseconds

//Light upper-threshold values by light type
#define VERY_BRIGHT 100
#define BRIGHT 200
#define LIGHT 500
#define DIM 900

int sensorReading = 0;  // variable to store the value read from the sensor pin
unsigned long startLightOnTimeMillis = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_OUT, OUTPUT);
}

void loop() {

  sensorReading = analogRead(LIGHT_SENSOR);

  printSensorReading(sensorReading);

  /*
    Manipulation of "Night - lamp"
  */

  if(sensorReading > LIGHT && digitalRead(LED_OUT) == LOW) // Turning the night-light [ON] when sensor gets in [DIM] environement
  {
    Serial.println("Turning the Light [ON]");
    digitalWrite(LED_OUT, HIGH);

    startLightOnTimeMillis = millis();
  }
  else if (digitalRead(LED_OUT) == HIGH && sensorReading < LIGHT) // Turning the night-light [OFF] when sensor gets in [LIGHT] or lighter environement
  {
    Serial.println("Turning the light [OFF]");
    digitalWrite(LED_OUT, LOW);

    startLightOnTimeMillis = 0;
  }
  else if (digitalRead(LED_OUT) == HIGH && (millis() - startLightOnTimeMillis) > LIGHT_ON_INTERVAL_MILLI) // turning the night-light [OFF] when LIGHT_INTERVAL runs out
  {
    Serial.println("Turning the light [OFF]");
    digitalWrite(LED_OUT, LOW);

    startLightOnTimeMillis = 0;
  }


  delay(500);  // delay to avoid overloading the serial port buffer
}

void printSensorReading(int sensorReading)
{
  Serial.print("Light Sensor reading: ");
  Serial.print(sensorReading);

  if(sensorReading < VERY_BRIGHT)
  {
    Serial.println(" - Very bright");
  }
  else if(sensorReading < BRIGHT)
  {
    Serial.println(" - Bright");
  }
  else if(sensorReading < LIGHT)
  {
    Serial.println(" - Light");
  }
  else if(sensorReading < DIM)
  {
    Serial.println(" - Dim");
  }
  else
  {
    Serial.println(" - Dark");
  }
}
