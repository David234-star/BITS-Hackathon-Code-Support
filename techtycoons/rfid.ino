#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <Arduino.h>
#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 12;
const int LOADCELL_SCK_PIN = 13;

HX711 scale;

TinyGPSPlus  gps;        
SoftwareSerial  ss(D8, A0) ;      
LiquidCrystal lcd(D0,D1,D2,D3,D4,D5);

#define WIFI_SSID "The WIFI"
#define WIFI_PASSWORD "123madhu"

#define ownertoken "5754346731:AAHfIyNtU29C9uxgHjHxkTuK4NyR9kvetEE"
#define ownerid1 "1413191733"
#define ownerid2 "1852543719"

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(ownertoken, secured_client);

String serverName = "https://makeskilled.com/projects/techtycoons1/driver/load.php";

float c1d,c1w;
float c2d,c2w;

float latitude , longitude;
String lat_str="15.8283837",lng_str="77.588802";

String card1741="09005ECA1D80";
String card9831="5300A54D77CC";
String card1675="3600A6068B1D";
String card9230="27001C722E67";

String area="Bandimetta";
String ward="3";
String drivername="Raju";
String mobile="8555896297";
String vehicleno="AP39JE7388";

String card1hno="HNo233";
String card1name="Chand";
String card1mobile="7993573775";
String card1lat="15.7148961";
String card1long="78.0024522";

String card2hno="HNO125";
String card2name="Meghana";
String card2mobile="8555896297";
String card2lat="15.741483";
String card2long="78.006639";

String cardhno,cardname,cardmobile,cardlat,cardlong;


void setup() {
  lcd.begin(16,2);
  lcd.print("WELCOME");
  delay(4000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Wt: ");
  lcd.setCursor(11,0);
  lcd.print("G");
  Serial.begin(9600);
  ss.begin(9600);
  secured_client.setTrustAnchors(&cert);
  configTime(0,0,"pool.ntp.org");
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
  Serial.println("WELCOME");
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());      // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));   // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided
            // by the SCALE parameter (not set yet)
            
  scale.set_scale(-478.507);
  //scale.set_scale(-471.497);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
            // by the SCALE parameter set with set_scale

  Serial.println("Readings:");
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
      cardhno=card1hno;
      cardname=card1name;
      cardmobile=card1mobile;
      cardlat=card1lat;
      cardlong=card1long;
      delay(10000);
      Serial.print("one reading:\t");
      Serial.print(scale.get_units(), 1);
      Serial.print("\t| average:\t");
      c1d=scale.get_units(10);
      Serial.println(c1d, 5);

      scale.power_down();             // put the ADC in sleep mode
      delay(5000);
      scale.power_up();
      lcd.setCursor(5,0);
      lcd.print(c1d);
    } else if(cData==card9831) {
      Serial.println("C1 Wet Waste");
      cardhno=card1hno;
      cardname=card1name;
      cardmobile=card1mobile;
      cardlat=card1lat;
      cardlong=card1long;
      delay(10000);
      Serial.print("one reading:\t");
      Serial.print(scale.get_units(), 1);
      Serial.print("\t| average:\t");
      c1w=scale.get_units(10);
      Serial.println(c1d, 5);

      scale.power_down();             // put the ADC in sleep mode
      delay(5000);
      scale.power_up();
      lcd.setCursor(5,0);
      lcd.print(c1w);
      bot.sendMessage(ownerid1,"Today, we have collected your dry waste: "+String(c1d)+"g, wet waste: "+String(c1w)+"g","Markdown");

      while(1) {
      int stat=upload_sensory_feed(cardhno,cardname,cardmobile,cardlat,cardlong,String(c1d),String(c1w),drivername,ward+area,mobile,vehicleno);
      if(stat==1) {
        break;
      }
      delay(100);
    }
    } else if(cData==card1675) {
      Serial.println("C2 Dry Waste");
      cardhno=card2hno;
      cardname=card2name;
      cardmobile=card2mobile;
      cardlat=card2lat;
      cardlong=card2long;
      delay(10000);
      Serial.print("one reading:\t");
      Serial.print(scale.get_units(), 1);
      Serial.print("\t| average:\t");
      c2d=scale.get_units(10);
      Serial.println(c2d, 5);

      scale.power_down();             // put the ADC in sleep mode
      delay(5000);
      scale.power_up();
      lcd.setCursor(5,0);
      lcd.print(c2d);
    } else if(cData==card9230) {
      Serial.println("C2 Wet Waste");
      cardhno=card2hno;
      cardname=card2name;
      cardmobile=card2mobile;
      cardlat=card2lat;
      cardlong=card2long;
      delay(10000);
      Serial.print("one reading:\t");
      Serial.print(scale.get_units(), 1);
      Serial.print("\t| average:\t");
      c2w=scale.get_units(10);
      Serial.println(c1d, 5);

      scale.power_down();             // put the ADC in sleep mode
      delay(5000);
      scale.power_up();
      lcd.setCursor(5,0);
      lcd.print(c2w);
      bot.sendMessage(ownerid2,"Today, we have collected your dry waste: "+String(c2d)+"g, wet waste: "+String(c2w)+"g","Markdown");

      while(1) {
      int stat=upload_sensory_feed(cardhno,cardname,cardmobile,cardlat,cardlong,String(c2d),String(c2w),drivername,ward+","+area,mobile,vehicleno);
      if(stat==1) {
        break;
      }
      delay(100);
    }
    }
  }
  

}

int upload_sensory_feed(String hno, String name1,String mob, String latt, String longg, String wt1, String wt2, String dname,String ward, String dmob,String vno) {
  
  if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      WiFiClientSecure client;
      client.setInsecure(); // this is the magical line that makes everything work


      String serverPath = serverName +"?hno="+String(hno)+"&name="+String(name1)+"&mobile="+String(mob)+"&latitude="+String(latt)+"&longitude="+String(longg)+"&dry="+String(wt1)+"&wet="+String(wt2)+"&dname="+String(dname)+"&ward="+String(ward)+"&dmobile="+String(dmob)+"&vno="+String(vno);
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
