int relay=5;
int trig=2;
int echo=3;

float threshold=10.0;
float water=20.0;

void setup() {
  pinMode(relay,OUTPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  Serial.begin(9600);  
}

void loop() {
  digitalWrite(trig,0);
  delayMicroseconds(2);

  digitalWrite(trig,1);
  delayMicroseconds(10);
  digitalWrite(trig,0);

  float duration=pulseIn(echo,1);
  float distance=(duration/2)*0.034;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(1000);
  if(distance<threshold) {
    Serial.println("Overflow Detected");
    digitalWrite(relay,1);
  }
  if(distance>water) {
    Serial.println("Pipe Empty");
    digitalWrite(relay,0);
  }
}
