/* Connect output of PIR sensor to the Arduino analog input.
 * Detection of movement should cause 3.3 volts on the outputs.
 *
 *   Check:
 *     - How reliable detection is
 *     - How far detection works
 *     - Under which light conditions detection works
 *     - How long is output on, after detection event
 *
 * Create app to turn light on for 10 minutes after movement
 * detection is observed, use integrated led on pin 13 as light.
*/

#define pirPin 2
#define ledPin 13
boolean detected = false;
boolean ledOn = false;
long long lightStarted = -1;
long long lightTimeout = 600000;

void setup() {
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
   if(digitalRead(pirPin) == HIGH) {
      if(!detected) {
         detected = true;
         digitalWrite(ledPin, HIGH);
         ledOn = true;
         lightStarted = millis();
         Serial.println("Motion detected.");
         Serial.println("LED turned on.");
      }
   }

   if(digitalRead(pirPin) == LOW) {
      if(detected) {
         detected = false;
         Serial.println("Motion ended.");
      }
   }

   if(ledOn && millis() - lightStarted >= lightTimeout) {
      Serial.println("Timeout expired. LED turned off.");
      digitalWrite(ledPin, LOW);
      ledOn = false;
      lightStarted = -1;
   }
}
