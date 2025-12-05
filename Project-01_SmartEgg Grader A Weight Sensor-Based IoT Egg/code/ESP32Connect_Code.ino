#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Galaxy";
const char* password = "puxt3235";
const char* apiKey = "18A6ZBU4I3OLZZ44";
const int channelID = 2964917;

#define RXD2 16
#define TXD2 17

String receivedData = "";

// Function declaration before usage
void sendToThingSpeak(String data);

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

void loop() {
  if (Serial2.available()) {
    receivedData = Serial2.readStringUntil('\n');
    receivedData.trim();

    if (receivedData.length() > 0) {
      // Check the prefix of the received data
      if (receivedData.startsWith("data:")) {
        // Future implementation for egg grade data (not yet handled)
        String data = receivedData.substring(5);
        // Example: sendToThingSpeak("field1=gradeA&field2=gradeB"); (not implemented here)
        
      } else if (receivedData.startsWith("duration:")) {
        String durationStr = receivedData.substring(9);
        float minutes = durationStr.toFloat();

        // Send to ThingSpeak as field4 only
        String url = "field4=" + String(minutes, 2);
        sendToThingSpeak(url);

      } else {
        // If not labeled, send the raw received string
        sendToThingSpeak(receivedData);
      }
    }
  }
}

void sendToThingSpeak(String data) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String server = "http://api.thingspeak.com/update?api_key=" + String(apiKey) + "&" + data;
    Serial.println("Sending to ThingSpeak: " + server);

    http.begin(server);
    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("Response: " + payload);
    } else {
      Serial.println("Error in sending: " + String(httpCode));
    }

    http.end();
  }
}
