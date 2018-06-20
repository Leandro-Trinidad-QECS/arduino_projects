int vcc = 2; //attach pin 2 to vcc
int trig = 6; // attach pin 3 to Trig
int echo = 7; //attach pin 4 to Echo
int gnd = 5; //attach pin 5 to GND


int ledPin = 3;
int button = 2;
// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

boolean Running;


int motor1 = 11;
int motor2 = 12;

int motor3 = 9;
int motor4 = 10;


void setup() {

  pinMode (vcc, OUTPUT);
  pinMode (gnd, OUTPUT);
  pinMode(button, INPUT);
  // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);

  pinMode (motor1, OUTPUT);
  pinMode (motor2, OUTPUT);
  pinMode (motor3, OUTPUT);
  pinMode (motor4, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
}

void loop()
{
  int reading = digitalRead(button);

  if (reading != lastButtonState) {

    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
 
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }
  lastButtonState = reading;


  digitalWrite(vcc, HIGH);

  long duration, inches, cm;

  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);
  
  pinMode(echo, INPUT);
  duration = pulseIn(echo, HIGH);

  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  digitalWrite(ledPin, ledState);




  // checks if the power button is on
  if (ledState == HIGH) {

    delay(50);

    // if the robot finds a wall it turns
    if (cm > 50) {
      forward();
    } else {
      right();
    }
  } else {
    brake();
  }






}

void right() {
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, HIGH);
}
void left() {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, HIGH);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, LOW);
}
void forward() {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, HIGH);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, HIGH);
}
void brake() {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, LOW);
}
long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second). This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PI...
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
