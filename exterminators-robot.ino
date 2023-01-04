#include <LiquidCrystal.h>
LiquidCrystal lcd(6,7,8,9,10,11);
String locs[]={"Chowrasta","Raj Vihar","C Camp   "};
int i=0;
int in1=2;
int in2=3;
int in3=4;
int in4=5;
int sensor=A0;

void setup() {
  lcd.begin(16,2);
  pinMode(sensor,INPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  lcd.setCursor(0,1);
  lcd.print("Loc: ");
  lcd.setCursor(0,0);
  lcd.print("Wt: ");
  int m=analogRead(sensor);
  int loadValue=map(m,160,420,0,5000);
  Serial.print("#");
  Serial.print(m);
  Serial.println("#");
  delay(1000);
  lcd.setCursor(5,0);
  lcd.print(m);
  while(Serial.available()) {
    char ch=Serial.read();
    if(ch=='F' || ch=='f') {
      forward();
    } else if(ch=='B' || ch=='b') {
      backward();
    } else if(ch=='L' || ch=='l') {
      leftward();
    } else if(ch=='R' || ch=='r') {
      rightward();
    } else if(ch=='S' || ch=='s') {
      stoprobot();
    } else if(ch=='1') {
      lcd.print(locs[i]);
      i++;
      if(i>2)
        i=0;
    }
  }
}

void forward() {
  Serial.println("Forward");
  digitalWrite(in1,1);
  digitalWrite(in2,0);
  digitalWrite(in3,1);
  digitalWrite(in4,0);
}

void backward() {
  Serial.println("Backward");
  digitalWrite(in1,0);
  digitalWrite(in2,1);
  digitalWrite(in3,0);
  digitalWrite(in4,1);
}

void leftward() {
  Serial.println("Leftward");
  digitalWrite(in1,0);
  digitalWrite(in2,0);
  digitalWrite(in3,1);
  digitalWrite(in4,0);
}

void rightward() {
  Serial.println("Rightward");
  digitalWrite(in1,1);
  digitalWrite(in2,0);
  digitalWrite(in3,0);
  digitalWrite(in4,0);
}

void stoprobot() {
  Serial.println("Stop");
  digitalWrite(in1,0);
  digitalWrite(in2,0);
  digitalWrite(in3,0);
  digitalWrite(in4,0);
}
