// FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h" // Install Firebase ESP8266 library
#include <ESP8266WiFi.h>
#define FIREBASE_HOST \
"firstproject-99bb2-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "yEf6VGsxnPXyfKp0B0sUeuWBQCxX0VqWRGEk6VPR"
#define WIFI_SSID "Revenant"
#define WIFI_PASSWORD "87656787"

int led = LED_BUILTIN;
String readString;
// Define FirebaseESP8266 data object
FirebaseData firebaseData;
FirebaseData ledData;
bool DHT_Error_reported = false;

FirebaseJson json;

void setup() {

  Serial.begin(115200);
  pinMode(led, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}
void sensorUpdate() {
  // if (Firebase.getString(ledData, "/FirebaseIOT/led2")) {
  //   // Serial.println(ledData.stringData());
  //   if (ledData.stringData() == "1") {
  //   } else if (ledData.stringData() == "0") {
  //     Firebase.setString(ledData, "/FirebaseIOT/led2", "1");
  //   }
  // }
  if (Firebase.setInt(firebaseData, "/FirebaseIOT/int", random(50))) {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  } else {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }

  if (Firebase.setFloat(firebaseData, "/FirebaseIOT/float", random(50))) {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  } else {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }
}

bool dataEnterd = false;
void loop() {
  sensorUpdate();

  if (Firebase.getString(ledData, "/FirebaseIOT/led")) {
    Serial.println(ledData.stringData());
    if (ledData.stringData() == "1") {
      digitalWrite(led, HIGH);
    } else if (ledData.stringData() == "0") {
      digitalWrite(led, LOW);
    }
  }
  delay(100);
}