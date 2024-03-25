
  int redLED = 13;
  int blueLED = 11;
  int greenLED = 12;
  int timeInterval = 100;

void setup() {
  // put your setup code here, to run once:
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  //Is actually saying
  //pinMode(13, OUTPUT);
  //pinMode(11, OUTPUT);
  //pinMode(12, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  RGBtoBGR(timeInterval);
}

//Turns on all
void turnOnAll() {
  digitalWrite(redLED, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(greenLED, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(blueLED, HIGH);  // turn the LED on (HIGH is the voltage level)
}

//Turns on one at a time, without turning them off
void onOneAtATime(int interval) {
  digitalWrite(redLED, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(interval);                      // wait for a second
  digitalWrite(greenLED, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(interval);                      // wait for a second
  digitalWrite(blueLED, HIGH);  // turn the LED on (HIGH is the voltage level)
}

//Turns them off one at a time, without turning them on
void offOneAtATime(int interval) {
  digitalWrite(blueLED, LOW);  // turn the LED on (HIGH is the voltage level)
  delay(interval);                      // wait for a second
  digitalWrite(greenLED, LOW);  // turn the LED on (HIGH is the voltage level)
  delay(interval);                      // wait for a second
  digitalWrite(redLED, LOW);  // turn the LED on (HIGH is the voltage level)
}

//Turns them on one at a time, then off one at a time
void onOffOneAtATime(int interval) {
  onOneAtATime(interval);
  delay(interval);
  offOneAtATime(interval);
  delay(interval);
}

//Turns on and off one color at a time, Red to Blue
void lightTransferRGB(int interval) {
  if (digitalRead(redLED) != LOW) {
    digitalWrite(redLED, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(interval);                      // wait for a second
    digitalWrite(redLED, LOW);  // turn the LED on (HIGH is the voltage level)
  }
  digitalWrite(greenLED, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(interval);                      // wait for a second
  digitalWrite(greenLED, LOW);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(blueLED, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(interval);                      // wait for a second
  digitalWrite(blueLED, LOW);  // turn the LED on (HIGH is the voltage level)
}

//Turns on and off one color at a time, Blue to Red
void lightTransferBGR(int interval) {
  if (digitalRead(blueLED) != LOW) {
    digitalWrite(blueLED, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(interval);                      // wait for a second
    digitalWrite(blueLED, LOW);  // turn the LED on (HIGH is the voltage level)
  }
  digitalWrite(greenLED, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(interval);                      // wait for a second
  digitalWrite(greenLED, LOW);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(redLED, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(interval);                      // wait for a second
  digitalWrite(redLED, LOW);  // turn the LED on (HIGH is the voltage level)
}

//Turns on and off one color at a time, Blue to Red, then Red to Blue
void RGBtoBGR(int interval) {
  lightTransferRGB(interval);
  lightTransferBGR(interval);
}

//Complete Random Intervals
void completeRandom(int maxTime) {
  digitalWrite(random(11, 14), HIGH);
  delay(random(maxTime));
  digitalWrite(random(11, 14), LOW);
  delay(random(maxTime));
}
