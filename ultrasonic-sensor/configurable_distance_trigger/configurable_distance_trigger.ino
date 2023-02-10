/*  Connect ultrasonic sensor, two buttons and one LED to Arduino.
 *  On Arduino start, the LED should be turned off. Whenever the ultrasonic 
 *  sensor detects object (like hand wave) it should toggle the state of LED.
 *  Initially the object detection should be as far as possible. Pressing  
 *  one button, the detection distance should decrease by 10 cm, up to a minimum, 
 *  with other button, detection distance should increase by 10 cm, up to a maximum.
 */

#define MAX_DISTANCE    200
#define MIN_DISTANCE    2
#define INCREMENT_VALUE 10
#define DECREMENT_VALUE 10

//Constants
const unsigned int trigPin = 13;
const unsigned int echoPin = 12;
const unsigned int keyPin1 = 10;
const unsigned int keyPin2 = 9;

//Variables
int distanceToCapture     = MAX_DISTANCE;
unsigned int distanceInCm = 0;
bool isObjectCaptured     = false;
//bool isLedOn              = false;

//Function prototypes
void calculateDistance(const unsigned int& trigPin, const unsigned int& echoPin);
void incrementCapturePoint();
void decrementCapturePoint();

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(keyPin1, INPUT_PULLUP);
  pinMode(keyPin2, INPUT_PULLUP);
//  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  int key1Pressed = digitalRead(keyPin1);
  int key2Pressed = digitalRead(keyPin2);
  
  if (!key1Pressed)
  {
    decrementCapturePoint();
  }

  if(!key2Pressed)
  {
    incrementCapturePoint();
  }

  Serial.print("Capture point is up to:" );
  Serial.print(distanceToCapture);
  Serial.println(" cm");

  calculateDistance(trigPin, echoPin);

  if (distanceInCm > distanceToCapture)
  {
    if (isObjectCaptured)
    {
      isObjectCaptured = false;
      Serial.println("Object is out of range");
    }
    else
    {
      Serial.println("Object is STILL out of range");
    }
  }
  else
  {
    if (!isObjectCaptured)
    {
//    digitalWrite(LED_BUILTIN, isLedOn ? LOW : HIGH);
//    isLedOn = !isLedOn
      isObjectCaptured = true; 
      Serial.print("Captured object on: ");
    }
    else
    {
      Serial.print("Object STILL on: ");
    }
    Serial.print(distanceInCm);
    Serial.println(" cm away");
  }
  delay(100);
}

//Function definitions
void calculateDistance(const unsigned int& trigPin, const unsigned int& echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  distanceInCm = (unsigned int)(duration * 0.034 / 2);
}

void incrementCapturePoint()
{
  if ((distanceToCapture + INCREMENT_VALUE) > MAX_DISTANCE)
  {
    distanceToCapture = MAX_DISTANCE;
  }
  else
  {
    distanceToCapture += INCREMENT_VALUE;
  }
}

void decrementCapturePoint()
{
  if ((distanceToCapture - DECREMENT_VALUE) < MIN_DISTANCE)
  {
    distanceToCapture = MIN_DISTANCE;
  }
  else
  {
    distanceToCapture -= DECREMENT_VALUE;
  }
}