int sunPin = A0;
int sunVal = 0;

//1.67mV (from 0 to 3 VDC) equals to 1 W/m2?

int resetPin = 12;


void setup() {
digitalWrite(resetPin, HIGH);
Serial.begin(9600);
pinMode(resetPin, OUTPUT);

}

void loop() {
 sunlight();
 resetDevice();
}


int sunlight(){
  sunVal = analogRead(sunPin);
  Serial.print("Sunlight Level: ");
  Serial.println(sunVal);
  delay(1000);
 
}

void resetDevice(){
  Serial.println("resetting");
  //delay(180000);
  delay(10000);
  digitalWrite(resetPin, LOW);
  Serial.println("If you see this it not work");
}
