const int DATA_PIN = A0;
int waterValue = 0;

const int PUMP_PIN = 13; // Water Pump Pin

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  waterValue = analogRead(DATA_PIN);
  Serial.println(waterValue);

  if (waterValue > 600) {
    digitalWrite(PUMP_PIN, HIGH);
  }
  else {
    digitalWrite(PUMP_PIN, LOW);
  }
  delay(1000);
}
