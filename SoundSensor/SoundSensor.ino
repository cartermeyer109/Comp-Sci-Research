/*
 * Rui Santos 
 * Complete Project Details https://randomnerdtutorials.com
*/

int sensorPin=2;
boolean val =0;

void setup(){
  pinMode(sensorPin, INPUT);
  Serial.begin (9600);
}
  
void loop (){
  val =digitalRead(sensorPin);
  Serial.println (val);
  // when the sensor detects a signal above the threshold value, LED flashes
  if (val==HIGH) {
    Serial.println("HIGH");
  }
  else {
  }
}
