#include <WiFi.h>
#include <ThingSpeak.h>

// WiFi credentials
const char* ssid = "PLDTHOMEFIBRt6ucX";
const char* password = "PLDTWIFItLK72";

// LDR and LED pins
const int ldrPin = A0;
const int Green1 = 5;
const int Blue1 = 18;
const int Yellow1 = 19;
const int Red1 = 21;
const int Green2 = 3;

// LED status variables
int Green1Status = 0;
int Blue1Status = 0;
int Yellow1Status = 0;
int Red1Status = 0;
int Green2Status = 0;

// ThingSpeak setup
WiFiClient client;
long myChannelNumber = 2946540;
const char myWriteAPIKey[] = "V3OSQVGH8LFTTBE1";

void setup() {
  Serial.begin(9600);
  delay(1000);  

  // Initialize pins
  pinMode(ldrPin, INPUT);
  pinMode(Green1, OUTPUT);
  pinMode(Blue1, OUTPUT);
  pinMode(Yellow1, OUTPUT);
  pinMode(Red1, OUTPUT);
  pinMode(Green2, OUTPUT);

  // Turn off all LEDs at start
  ledClear();

  // Connect to WiFi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Start ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  int ldrValue = analogRead(ldrPin);
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  // Control LEDs based on LDR value
  if (ldrValue <= 500) {
    ledLights();
    Serial.println("LEDs are ON");
  } else {
    ledClear();
    Serial.println("LEDs are OFF");
  }

  // Get current LED states (HIGH = 1, LOW = 0)
  Green1Status = digitalRead(Green1);
  Blue1Status = digitalRead(Blue1);
  Yellow1Status = digitalRead(Yellow1);
  Red1Status = digitalRead(Red1);
  Green2Status = digitalRead(Green2);

  // Send data to ThingSpeak
  ThingSpeak.setField(1, ldrValue);
  ThingSpeak.setField(2, Green1Status);
  ThingSpeak.setField(3, Blue1Status);
  ThingSpeak.setField(4, Yellow1Status);
  ThingSpeak.setField(5, Red1Status);
  ThingSpeak.setField(6, Green2Status);

  int statusCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (statusCode == 200) {
    Serial.println("Channel update successful.");
  } else {
    Serial.print("ThingSpeak update error. Code: ");
    Serial.println(statusCode);
  }

  delay(15000);  // Wait 15 seconds before next update
}

// Turn all LEDs OFF
void ledClear() {
  digitalWrite(Green1, LOW);
  digitalWrite(Yellow1, LOW);
  digitalWrite(Red1, LOW);
  digitalWrite(Blue1, LOW);
  digitalWrite(Green2, LOW);
}

// Turn all LEDs ON
void ledLights() {
  digitalWrite(Green1, HIGH);
  digitalWrite(Blue1, HIGH);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Red1, HIGH);
  digitalWrite(Green2, HIGH);
}
