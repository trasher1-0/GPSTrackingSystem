#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include<SoftwareSerial.h>
#include <FirebaseArduino.h>
#include "TinyGPS++.h"

// Set these to run example.
#define FIREBASE_HOST "vehicletrackinsystem.firebaseio.com"
#define FIREBASE_AUTH "Yy9Blaj6oxgBCo7QXKpABB8PrtNZFRN5zD4Dq0Mt"
#define WIFI_SSID "Hasee"
#define WIFI_PASSWORD "haseesart"

TinyGPSPlus gps;
SoftwareSerial ss(4,5);

void setup() {
  Serial.println("GPS Start");
  Serial.begin(9600);  
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
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
void loop() {
   while (ss.available() > 0)
    if (gps.encode(ss.read()))
    {
      if (gps.location.isValid())
      {
        Serial.println("Latitude : "+String(gps.location.lat() , 6));
        Serial.println("Longitude : "+String(gps.location.lng() , 6));
      }
    }
}
