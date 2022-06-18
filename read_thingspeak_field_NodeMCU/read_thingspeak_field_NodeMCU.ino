#include <ThingSpeak.h>
#include <ESP8266WiFi.h>

// Network Parameters
const char* ssid     = "Revenant";
const char* password = "56787656";

// ThingSpeak information
char* server = "api.thingspeak.com";
unsigned long channelID = 1769780;
char* readAPIKey = "QLL7IHIBXRWJ38GU";
unsigned int dataFieldOne = 1;                            // Field to write temperature data

// Global variables
// These constants are device specific.  You need to get them from the manufacturer or determine them yourself.
float aConst = 2.25E-02;
WiFiClient client;

void setup() {

  Serial.begin(115200);
  Serial.println("Start");
  connectWiFi();

  // Read the constants at startup.
  aConst = readTSData( channelID, dataFieldOne );
  //Serial.println(aConst);
  delay(1000);
}

void loop() {

  delay(2000);
  Serial.println("Waiting...");
  //reading data from thing speak
  aConst = readTSData( channelID, dataFieldOne );
  Serial.println(aConst);

}

int connectWiFi() {
  WiFi.begin( ssid, password );
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println( "Connected" );
  ThingSpeak.begin( client );
}

float readTSData( long TSChannel, unsigned int TSField ) {

  float data =  ThingSpeak.readFloatField( TSChannel, TSField, readAPIKey );
  Serial.println( " Data read from ThingSpeak: " + String( data, 9 ) );
  return data;

}
