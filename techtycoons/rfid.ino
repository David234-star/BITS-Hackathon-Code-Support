#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

TinyGPSPlus  gps;              
SoftwareSerial  ss(D2, D3) ;
LiquidCrystal lcd(D0,D1,D4,D5,D8,A0);


float latitude , longitude;
String lat_str,lng_str;

String card1741="09005ECA1D80";
String card9831="5300A54D77CC";
String card1675="3600A6068B1D";
String card9230="27001C722E67";

String area="Bandimetta";
String ward="3";
String drivername="Raju";
String mobile="8555896297";
String vehicleno="AP39JE7388";

String card1name="";
String card1mobile="";
String card1lat="";
String card1long="";

String card2name="";
String card2mobile="";
String card2lat="";
String card2long="";

void setup() {
  lcd.begin(16,2);
  lcd.print("WELCOME");
  delay(4000);
  lcd.clear();
  Serial.begin(9600);
  ss.begin(9600);
  Serial.println("WELCOME");
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
    
  while(Serial.available()) {
    String cData=Serial.readString();
    //Serial.println(cData);
    if(cData==card1741) {
      Serial.println("C1 Dry Waste");
    } else if(cData==card9831) {
      Serial.println("C1 Wet Waste");
    } else if(cData==card1675) {
      Serial.println("C2 Dry Waste");
    } else if(cData==card9230) {
      Serial.println("C2 Wet Waste");
    }
  }
}
