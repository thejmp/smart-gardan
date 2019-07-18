#if defined(ESP8266)
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#else
#include <WiFi.h>          //https://github.com/esp8266/Arduino
#endif

//needed for library
#if defined(ESP8266)
#include <ESP8266WebServer.h>
#else
#include <WebServer.h>
#endif
#include <DNSServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#include <PubSubClient.h>

const char* mqttServer = "io.adafruit.com";
const int mqttPort = 1883;
const char* mqttUser = "jpattull";
const char* mqttPassword = "82bab7e36add49f6acf49a288ddbe524";

float val[5] = {0};
short soilPower = 23;
short floatSensor = 16;
short led = 4;
bool waterLevel = 0;
short relayPower[6] = {22,21,19,18,5,17};
short soilPin[5] = {34, 35, 32, 33, 25};
String mqttMessSoil = "jpattull/f/soilPlant";
String mqttMess = "";
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  WiFiManager wifiManager;
  bool connected = 1;
  wifiManager.setConfigPortalTimeout(120);
  if (!wifiManager.startConfigPortal("Smart Gardan")) {
      Serial.println("failed to connect and hit timeout");
      Serial.println("type 1 to retry or 0 to continue");
      while(!Serial.available());
      if (Serial.read() == 49) {
        delay(3000);
        //reset and try again, or maybe put it to deep sleep
        ESP.restart();
        delay(5000);
      } else {
        connected = 0;
      }
  }
  if (connected){
    Serial.println("Connected to the WiFi network");
    client.setServer(mqttServer, mqttPort);
    
    while (!client.connected()) {
      Serial.println("Connecting to MQTT...");
      if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
        Serial.println("connected");
      } else {
        Serial.print("failed with state ");
        Serial.print(client.state());
        delay(2000);
        ESP.restart();
        delay(5000);
      }
    }
  }
  client.disconnect ();
  pinMode(soilPower, OUTPUT);
  digitalWrite(soilPower, LOW);
  pinMode(floatSensor, INPUT_PULLUP);
  pinMode (led, OUTPUT);
  for (int i = 0; i < 6; i++){
    pinMode(relayPower[i], OUTPUT);
    digitalWrite(relayPower[i], HIGH);
  }
}

void loop() {
  readSoil(-1);
  client.connect("ESP32Client", mqttUser, mqttPassword );
  for (int i = 0; i < 5; i++){
    Serial.print("Soil Moisture plant ");
    Serial.print(i);
    Serial.print(" = ");
    Serial.println(val[i]);
    mqttMess = mqttMessSoil + (i+ 1);
    client.publish(mqttMess.c_str(), String(val[i]).c_str());
    if(val[i] < 50 && digitalRead(floatSensor))
      water(i);
  }
  waterLevel = digitalRead(floatSensor);
  if (!waterLevel)
    digitalWrite(led, HIGH);
  else
    digitalWrite(led, LOW);
  client.publish("jpattull/f/waterLevel", String(waterLevel).c_str());
  client.disconnect ();
  delay(1000);
}

int readSoil(int plant)
{
  float offset= 3900;
    digitalWrite(soilPower, HIGH);
    delay(10);
      if(plant == -1){
        for (int i = 0; i < 5; i++) {
          val[i] = (1.0 - (((float)analogRead(soilPin[i])-575)/offset)) * 100.0;
        }
      } else 
        val[plant] = (1.0 - ((float)analogRead(soilPin[plant])/offset)) * 100.0;
    digitalWrite(soilPower, LOW);
    return val[plant];
}

void water(short plant) {
  bool watered = 0;
  if (digitalRead(floatSensor)) {
    client.publish("jpattull/f/wateredPlant", String(plant).c_str());
    for (int i = 0; i < 1; i++) {
     digitalWrite(relayPower[plant], LOW);
     digitalWrite(relayPower[5], LOW);
     delay(10000);
     if (readSoil(plant) < 1000) {
        watered = 1;
        break;
    }
    if(!digitalRead(floatSensor))
      break;
  }
  digitalWrite(relayPower[plant], HIGH);
  digitalWrite(relayPower[5], HIGH);
  if (!watered)
    Serial.println("problom watering plants");
  }
}
