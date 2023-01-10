#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>


// Wifi network station credentials
#define WIFI_SSID "The WIFI"
#define WIFI_PASSWORD "123madhu"

#define ownertoken "5982109878:AAGzuL31DtSVJLKIruPOKQLfVKo6GUzsLWo"
#define ownerid "1694002474"
#define municipalid "5137812486"

String ownermsg="Alert from Septic Tank, your tank is going to be full. Clean it before it overflows";
String muncipalmsg="Alert from Septic Tank located at Lt: 15.8283837, Lg: 77.588802, it is going to be full";

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(ownertoken, secured_client);

String serverName = "https://makeskilled.com/projects/mockingbirds/driver/septictank.php";


int button=D2;

int rled1=D3;
int gled1=D4;
int wled1=D5;
int flag=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(rled1,OUTPUT);
  pinMode(gled1,OUTPUT);
  pinMode(wled1,OUTPUT);
  pinMode(button,INPUT);
  Serial.begin(9600);
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

}

void loop() {
  delay(1000);
  // put your main code here, to run repeatedly:
  if(digitalRead(button)==0){
    flag=0;
    digitalWrite(rled1,1);
    digitalWrite(wled1,1);
    digitalWrite(gled1,0);
  } else if(digitalRead(button)==1 && flag==0) {
    Serial.println("MOTOR OFF");
    bot.sendMessage(ownerid,ownermsg, "Markdown");
    bot.sendMessage(municipalid,muncipalmsg,"Markdown");
    while(1) {
      int stat=upload_sensory_feed("15.8283837","77.588802","Omkar","7396060373");
      if(stat==1) {
        break;
      }
      delay(100);
    }
    flag=1;
    digitalWrite(gled1,1);
    digitalWrite(rled1,1);
    for(int i=0;i<10 ;i++) {
     digitalWrite(wled1,0);
     delay(100);
     digitalWrite(wled1,1);
     delay(100);
   }
   digitalWrite(rled1,0);
  }
}

int upload_sensory_feed(String a, String g, String s, String d) {
  
  if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      WiFiClientSecure client;
      client.setInsecure(); // this is the magical line that makes everything work


      String serverPath = serverName +"?latitude=" + String(a) + "&longitude=" + String(g) + "&owner=" + String(s) + "&contact=" + String(d);
            
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
