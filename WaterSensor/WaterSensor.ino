const int data = A0;
int value = 0;

const int PUMP_PIN = 13; // Water Pump Pin

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(data);
  Serial.println(value);

  if (value > 600) {
    digitalWrite(PUMP_PIN, HIGH);
  }
  else {
    digitalWrite(PUMP_PIN, LOW);
  }
  delay(1000);
}

//600 is halfway point
