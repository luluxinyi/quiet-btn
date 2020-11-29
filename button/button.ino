

#include <ESP8266WiFi.h>
#include <MQTT.h>

const char ssid[] = "xinyi";
const char pass[] = "xinyi123";

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;
int btnState = 0;
int btnPin = D5;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting..."); 
  while (!client.connect("arduino", "quitebtn", "12345678")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("/hello");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
}

void setup() {
  Serial.begin(115200);
  pinMode (btnPin, INPUT); 
  WiFi.begin(ssid, pass);

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
  // You need to set the IP address directly.
  client.begin("broker.shiftr.io", net);
  client.onMessage(messageReceived);

  connect();
}

void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }
  btnState = digitalRead(btnPin);
  Serial.println(btnState);
  
  // publish a message roughly every second.
  if (millis() - lastMillis > 1000) {
    lastMillis = millis();
    String msg = "{\"btnState\":"+(String)btnState+"}";
    client.publish("/btn",msg);//括号里要写1）topic，用于noodl；2）string
    
  }
  
}
