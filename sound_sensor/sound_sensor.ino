#include <Arduino_JSON.h>

// This example uses an Adafruit Huzzah ESP8266
// to connect to shiftr.io.
//
// You can check on your device after a successful
// connection here: https://shiftr.io/try.
//
// by Joël Gähwiler
// https://github.com/256dpi/arduino-mqtt

#include <ESP8266WiFi.h>
#include <MQTT.h>


const char ssid[] = "xinyi";
const char pass[] = "xinyi123";
int turnOn = 0;

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("soundSensor", "quitebtn", "12345678")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("/btn");
  
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
  //订阅了多个topic时需要check

    JSONVar myObject = JSON.parse(payload);
  
  if (JSON.typeof(myObject) == "undefined") {
    Serial.println("Parsing input failed!");
    return;
  }

  if (myObject.hasOwnProperty("btnState")) {
    //Serial.print("myObject[\"btnState\"] = ");

    //Serial.println((int) myObject["btnState"]);

    turnOn = (int)myObject["btnState"];
    //Serial.print((String)turnOn);
  }
}

int dOut = D3;//DOUT接D3号引脚
//int sound = 0;

int sample_Time = 20;
unsigned long millisCurrent;
unsigned long millisLast = 0;
unsigned long millisElapsed = 0;

int sampleBufferValue = 0;


void setup() {
  pinMode(D1, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, pass);


  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
  // You need to set the IP address directly.
  client.begin("broker.shiftr.io", net);
  client.onMessage(messageReceived);

  connect();
}

void loop() {
  if(turnOn == 1 ) {
    digitalWrite(D2,HIGH);
  } else {
    digitalWrite(D2,LOW);
  }
  
  client.loop();
  //delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }
 
 //sound = digitalRead(dOut);
 //Serial.println(sound);

  millisCurrent = millis();
  millisElapsed = millisCurrent - millisLast;

  if(digitalRead(dOut) == LOW) {
    sampleBufferValue++;
  }

  if(millisElapsed > sample_Time) {
    Serial.println(sampleBufferValue);
    sampleBufferValue = 0;
    millisLast = millisCurrent;
  }


//publish a message roughly every second.
  if (millis() - lastMillis > 500) {
  lastMillis = millis();
    String msg = "{\"volume\":"+(String)sampleBufferValue+"}";
    client.publish("/vol",msg);
  }


}
