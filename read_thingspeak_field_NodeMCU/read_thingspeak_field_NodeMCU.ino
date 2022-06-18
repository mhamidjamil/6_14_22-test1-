/////////////////////////////////
// Generated with a lot of love//
// with TUNIOT FOR ESP8266     //
// Website: Easycoding.tn      //
/////////////////////////////////
#include <ESP8266WiFi.h>

#include <ThingSpeak.h>

WiFiClient client;

void setup()
{
  Serial.begin(115200);
ThingSpeak.begin(client);

  WiFi.disconnect();
  delay(1000);
  Serial.println("Start");
  Serial.println("Connecting");
   WiFi.begin("Revenant","56787656");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(200);
    Serial.println("..");

  }
  Serial.println("Connected ");
  Serial.println("IP is : ");
  Serial.println((WiFi.localIP().toString()));

}


void loop()
{

    Serial.println((ThingSpeak.readIntField(1769780,1,"QLL7IHIBXRWJ38GU")));
    delay(3000);

}
