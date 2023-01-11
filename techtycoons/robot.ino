#include "BluetoothSerial.h" 
#include <ESP32Servo.h> 
Servo myservo;
BluetoothSerial BT;
int flag=0;

#define motor 5
#define trig 16
#define echo 17
#define in1 22 
#define in2 23
#define in3 26
#define in4 27
#define threshold 15

void setup() {
  // put your setup code here, to run once:
  BT.begin("ESP32Blue");
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  myservo.attach(5);
  myservo.write(0);
  Serial.begin(9600);
}

void loop() {
 digitalWrite(trig,0);
 delayMicroseconds(2);
 digitalWrite(trig,1);
 delayMicroseconds(10);
 digitalWrite(trig,0);
 float duration=pulseIn(echo,1);
 duration=duration/2;
 float distance=duration*0.034;
 Serial.print("Distance: ");
 Serial.println(distance);
 
 if(distance<threshold && flag==0) {
    writetoServo(90);
    delay(5000);
    writetoServo(0);
    delay(1000);
    flag=1;
 } else if(distance>threshold) {
    flag=0;
 }
 
 if(BT.available()){
  char ch=BT.read();
  if(ch=='F') {
    Serial.println("Forward");
    forward();
  } else if(ch=='B') {
    Serial.println("Backward");
    backward();
  } else if(ch=='L') {
    Serial.println("Left");
    right();
  } else if(ch=='R') {
    Serial.println("Right");
    left();
  } else {
    Serial.println("Stop");
    stopped();
  }
 }
}

void forward() {
  digitalWrite(in1,1);
  digitalWrite(in2,0);
  digitalWrite(in3,1);
  digitalWrite(in4,0);
}

void backward() {
  digitalWrite(in1,0);
  digitalWrite(in2,1);
  digitalWrite(in3,0);
  digitalWrite(in4,1);
}

void left() {
  digitalWrite(in1,0);
  digitalWrite(in2,0);
  digitalWrite(in3,1);
  digitalWrite(in4,0);
  delay(1000);
  digitalWrite(in3,0);
  digitalWrite(in4,0);
}

void right() {
  digitalWrite(in1,1);
  digitalWrite(in2,0);
  digitalWrite(in3,0);
  digitalWrite(in4,0);
  delay(1000);
  digitalWrite(in1,0);
  digitalWrite(in2,0);
}

void stopped() {
  digitalWrite(in1,0);
  digitalWrite(in2,0);
  digitalWrite(in3,0);
  digitalWrite(in4,0);
}

void writetoServo(int s) {
  for(int i=0;i<=s;i++) {
    myservo.write(i);
    delay(10);
  }
}
