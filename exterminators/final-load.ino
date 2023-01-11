#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>

#define WIFI_SSID "chandu"
#define WIFI_PASSWORD "1234567890"

String serverName = "https://makeskilled.com/projects/exterminators/driver/robot.php";

TinyGPSPlus  gps;              
SoftwareSerial  ss(D2, D3) ;

LiquidCrystal lcd(D0,D1,D4,D5,D6,D7);
int sensor=A0;
int zerowt=262;

float latitude , longitude;
String lat_str="15.8283837",lng_str="77.588802";

String driver="Ravi";
String mobile="7893015625";
String vno="AP39JE8873";


void setup() {
  ss.begin(9600);
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Wt: ");

  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  if (ss.available() > 0) {
    if (gps.encode(ss.read()))
    {
      if (gps.location.isValid())
      {
        latitude = gps.location.lat();
        lat_str = String(latitude , 6);
        longitude = gps.location.lng();
        lng_str = String(longitude , 6);
        Serial.print("Lt: ");
        Serial.print(lat_str);
        Serial.print(", Lg: ");
        Serial.println(lng_str);
      }
    }
  }

  int m=analogRead(sensor);
  m=m-zerowt;
  float wt=(0.0235)*m;
  if(wt<0) 
    wt=abs(wt);
  if(wt<0.1)
    wt=0;
  Serial.print("Value: ");
  Serial.println(wt);
  lcd.setCursor(5,0);
  lcd.print(wt);
  lcd.setCursor(11,0);
  lcd.print("KG");
  delay(1000);
//  for(int i=5;i<11;i++) {
//    lcd.setCursor(i,0);
//    lcd.print(" ");
//  }
  while(1) {
      int stat=upload_sensory_feed(driver,String(wt),lat_str,lng_str,mobile,vno);
      if(stat==1) {
        break;
      }
      delay(100);
  }
}

int upload_sensory_feed(String dname, String wt, String latt, String longi,String mob, String v) {
  
  if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      WiFiClientSecure client;
      client.setInsecure(); // this is the magical line that makes everything work


      String serverPath = serverName +"?dname=" + String(dname) + "&wt=" + String(wt) + "&latitude=" + String(latt) + "&longitude=" + String(longi) + "&mobile="+String(mob)+"&vno=" + String(v);
            
      http.begin(client,serverPath.c_str());
       
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
        return(1);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        return(0);        
      }
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
      return(0);
    }
}
