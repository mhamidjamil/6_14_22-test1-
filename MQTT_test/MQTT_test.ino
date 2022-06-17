/////////////////////////////////
// Generated with a lot of love//
// with TUNIOT FOR ESP32     //
// Website: Easycoding.tn      //
/////////////////////////////////
#include <WiFi.h>

#include <PubSubClient.h>

String  MyData;
WiFiClient espClient;
PubSubClient client(espClient);

void reconnectmqttserver() {
while (!client.connected()) {
Serial.print("Attempting MQTT connection...");
String clientId = "ESP32Client-";
 clientId += String(random(0xffff), HEX);
if (client.connect(clientId.c_str())) {
Serial.println("connected");
} else {
Serial.print("failed, rc=");
Serial.print(client.state());
Serial.println(" try again in 5 seconds");
delay(5000);
}
}
}

char msgmqtt[50];
void callback(char* topic, byte* payload, unsigned int length) {
  String MQTT_DATA = "";
  for (int i=0;i<length;i++) {
   MQTT_DATA += (char)payload[i];}

}

void setup()
{
MyData = "Revenant!";

Serial.begin(115200);

  WiFi.disconnect();
  delay(1000);
  Serial.println("Start");
  Serial.println("Connecting");
  WiFi.begin("Revenant","87656787");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(200);
    Serial.println("..");

  }
  Serial.println("Connected ");
  Serial.println("IP is : ");
  Serial.println((WiFi.localIP()));
  client.setServer("127.0.0.1", 1883);
  client.setCallback(callback);

}


void loop()
{

    if (!client.connected()) {
    reconnectmqttserver();
    }
    client.loop();
    MyData = "ON";
    snprintf (msgmqtt, 50, "%s",MyData);
    client.publish("test", msgmqtt);
    delay(3000);
    MyData = "OFF";
    snprintf (msgmqtt, 50, "%s",MyData);
    client.publish("test", msgmqtt);
    delay(3000);

}
