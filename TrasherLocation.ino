#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include<SoftwareSerial.h>
#include <FirebaseArduino.h>
#include "TinyGPS++.h"

// Set these to run example.
#define FIREBASE_HOST "trasher-5a2fd.firebaseio.com"
#define FIREBASE_AUTH "iFn8z0b8wYte0LtcgMcNPbqIvzV3dbfghFmCa8TY"
#define WIFI_SSID "BELL4G-LTE"
#define WIFI_PASSWORD "leavemealone12"

TinyGPSPlus gps;
SoftwareSerial ss(4,5);
String f;
float lat;
float lng;

void setup() {
  Serial.begin(9600);  
  ss.begin(9600);
  
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("WiFi Connected: ");
  Serial.println(WiFi.localIP());
  Serial.println("GPS Start");
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
void loop() {
  while(ss.available()){
    gps.encode(ss.read());
  }
  
  if(gps.location.isUpdated())
  {
    if (Firebase.failed()) {
       Serial.print("setting /location failed:");
       Serial.println(Firebase.error());
       Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
       delay(2000);  
       return;
    }

    lat=gps.location.lat();
    lng=gps.location.lng();
    Firebase.setFloat("coords/azhsgsfskc1x/latitude",lat);
    Firebase.setFloat("coords/azhsgsfskc1x/longitude",lng);
    f=String(lat,6)+","+String(lng,6);
    Serial.println(f);
    delay(10000); 
  } 
}