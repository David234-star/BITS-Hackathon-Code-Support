#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

#define full 4
#define threefourth 3
#define empty 8

#define WIFI_SSID "chandu"
#define WIFI_PASSWORD "1234567890"

#define ownertoken "5916948590:AAGK4Jy5Impfsd3Yg9msaPQrrtsFsVcioFc"
#define municipalid "5063432443"

int trig=D6;
int echo=D5;
int relay=D2;

String muncipalmsg="Alert from Sewege Lines located at Lt: 15.7863, Lg: 76.6935, it is going to be overflow";

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(ownertoken, secured_client);

String serverName = "https://makeskilled.com/projects/exterminators/driver/sewage.php";


void setup() {
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(relay,OUTPUT);
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
  if(distance<full) {
    digitalWrite(relay,1);
    Serial.println("Leakage Detected");
    bot.sendMessage(municipalid,muncipalmsg,"Markdown");
  } else {
    digitalWrite(relay,0);
  }
   while(1) {
      int stat=upload_sensory_feed("15.7863","76.6935",String(distance));
      if(stat==1) {
        break;
      }
      delay(100);
   }
}

int upload_sensory_feed(String a, String g, String st) {
  
  if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      WiFiClientSecure client;
      client.setInsecure(); // this is the magical line that makes everything work


      String serverPath = serverName +"?latitude=" + String(a) + "&longitude=" + String(g) + "&status=" +String(st);
            
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
