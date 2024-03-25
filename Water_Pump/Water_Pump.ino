
/*
 * AJ Alves (aj.alves@zerokol.com)
*/

const int PUMP_PIN = 13; // Water Pump Pin
const int MOISTURE_INFO_PIN = A0;//Pin to read Moisture Value
const int MOISTURE_POW_PIN = 7;//Pin to power moisture reader

int MOISTURE_VAL = 0; //Moisture Value

void setup() {
  Serial.begin(9600); // Serial Port setup
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, HIGH);//TODO Set to LOW so no power is flowing to the pump

  pinMode(MOISTURE_POW_PIN, OUTPUT);//Set D7 as an POWER OUTPUT
  digitalWrite(MOISTURE_POW_PIN, LOW);//Set to LOW so no power is flowing through the sensor
}

void loop() {

//  digitalWrite(PUMP_PIN, LOW); // Set pin HIGH
//  Serial.println("The Water Pump is ON!");
//  delay(1000); // Wait 1 seconds
//  digitalWrite(PUMP_PIN, LOW); // Set pin LOW
//  Serial.println("The Water Pump is OFF!");
  //delay(250); // Wait 1 seconds

//800 seems to be the moisture barrier
  //if moisture is low, turn pump on
  if (readSoil() < 750) {
    digitalWrite(PUMP_PIN, HIGH);
  }
  //if moisture is high, turn pump off
  else {
    digitalWrite(PUMP_PIN, LOW);
  }

  Serial.println(readSoil());

}

//This is a function used to get the soil moisture content
int readSoil()
{

    digitalWrite(MOISTURE_POW_PIN, HIGH);//Turn sensor on
    delay(10);//wait 10 milliseconds 
    MOISTURE_VAL = analogRead(MOISTURE_INFO_PIN);//Read the SIG value from sensor 
    digitalWrite(MOISTURE_POW_PIN, LOW);//turn sensor off
    return MOISTURE_VAL;//send current moisture value
}
