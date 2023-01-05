#include <LiquidCrystal.h>

LiquidCrystal lcd(D0,D1,D2,D3,D4,D5);
int sensor=A0;
int zerowt=262;

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Wt: ");
}

void loop() {
  int m=analogRead(sensor);
  m=m-zerowt;
  float wt=(0.0235)*m;
  Serial.print("Value: ");
  Serial.println(wt);
  lcd.setCursor(5,0);
  lcd.print(wt);
  delay(1000);
  for(int i=5;i<16;i++) {
    lcd.setCursor(i,0);
    lcd.print(" ");
  }
}
