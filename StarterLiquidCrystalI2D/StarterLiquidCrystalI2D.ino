#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
int seconds = 55;

void setup() {
  // put your setup code here, to run once:
  
  lcd.init();   // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("TIME:00:00:00");
  lcd.setCursor(0,1);
  lcd.print("DATE:00/00/00");

  //The following are on lines that are not on the display
  //lcd.setCursor(0,2);
  //lcd.print("Arduino LCM IIC 2004");
  //lcd.setCursor(2,3);
  //lcd.print("Power By Ec-yuan!");

}

void loop() {
  // put your main code here, to run repeatedly:
  // when characters arrive over the serial port...
  delay(1000);
  seconds++;

  //Seconds
  if ((seconds % 60) < 10) {
    lcd.setCursor(12,0);
    lcd.print(strcat("0", String(seconds % 60)))
  }
  else {
   lcd.setCursor(11,0);
   lcd.print(String(seconds % 60));
  }
}

void onOff() {
    //The patern goes: Print, High, Low

  //Set curser and print
  lcd.setCursor(0,0);
  lcd.print("Hello");

  //Delay to display on HIGH
  lcd.setBacklight(HIGH);
  delay(1000);

  //Delay to stay LOW
  lcd.setBacklight(LOW);
  delay(1000);
  
  //Set curser and print
  lcd.setCursor(0,0);
  lcd.print("World");

  //Delay to display on HIGH
  lcd.setBacklight(HIGH);
  delay(1000);

  //Delay to stay LOW;
  lcd.setBacklight(LOW);
  delay(1000);
}
