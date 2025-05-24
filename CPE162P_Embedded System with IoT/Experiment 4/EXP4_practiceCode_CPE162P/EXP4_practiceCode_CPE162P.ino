#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <ThingSpeak.h>

// WiFi credentials
const char* ssid = "PLDTHOMEFIBRt6ucX";
const char* password = "PLDTWIFItLK72";

// ThingSpeak setup
WiFiClient client;
long myChannelNumber = 2964917;
const char myWriteAPIKey[] = "18A6ZBU4I3OLZZ44";

LiquidCrystal_I2C dis(0x27, 16, 2);
Servo myservo1;
int pos = 0;
unsigned long lastUpdate = 0;
const unsigned long updateInterval = 15000;

void setup() {
  myservo1.attach(5);
  Serial.begin(9600);
  dis.init();
  dis.backlight();
  dis.clear();
      // Start with motor OFF
  delay(1000);
  
  dis.setCursor(0, 0);
  dis.print(" MY IRRIGRATION");
  dis.setCursor(0, 1);
  dis.print("SYSTEM IS ON ");

  // LCD animation
  for (int a = 12; a <= 15; a++) {
    dis.setCursor(a, 1);
    dis.print(".");
    delay(1000);
  }

  // WiFi setup
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  ThingSpeak.begin(client);
  dis.clear();
}

void loop() {
  int value = analogRead(A0);
  Serial.println(value);
  int servoStatus = 0;

  if (value >= 900) {
    dis.setCursor(0, 1);
    dis.print("Moisture : VLOW ");
        // Motor ON
    dis.setCursor(0, 0);
    dis.print("MOTOR IS ON ");
    moveServo();
  } else if (value >= 700) {
    dis.setCursor(0, 1);
    dis.print("MOISTURE : LOW ");
        // Motor ON
    dis.setCursor(0, 0);
    dis.print("MOTOR IS ON ");
    moveServo();
  } else if (value >= 500) {
    dis.setCursor(0, 1);
    dis.print("MOISTURE : MID ");
        // Motor ON
    dis.setCursor(0, 0);
    dis.print("MOTOR IS ON ");
    moveServo();
  } else if (value >= 310) {
    dis.setCursor(0, 1);
    dis.print("MOISTURE:NORMAL");
         // Motor OFF
    dis.setCursor(0, 0);
    dis.print("MOTOR IS OFF ");
    resetServo();
  } else {
    dis.setCursor(0, 1);
    dis.print("MOISTURE : HIGH");
       // Motor OFF
    dis.setCursor(0, 0);
    dis.print("MOTOR IS OFF ");
    resetServo();
  }

  // Track servo status
  servoStatus = (pos > 0) ? 1 : 0;

  // ThingSpeak update
  if (millis() - lastUpdate >= updateInterval) {
    lastUpdate = millis();
    ThingSpeak.setField(1, value);     // Moisture
    ThingSpeak.setField(2, servoStatus); // Motor state
    int statusCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    
    if (statusCode == 200) {
      Serial.println("Channel update successful.");
    } else {
      Serial.print("Update failed. Code: ");
      Serial.println(statusCode);
    }
  }
  delay(1000);
}

void moveServo() {
  for (pos = 0; pos <= 120; pos += 1) {
    myservo1.write(pos);
    delay(19);
  }
  delay(1000);
  for (pos = 120; pos >= 0; pos -= 1) {
    myservo1.write(pos);
    delay(5);
  }
}

void resetServo() {
  if (pos != 0) {
    myservo1.write(0);
    pos = 0;
  }
}