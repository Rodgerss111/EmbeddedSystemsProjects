#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <ThingSpeak.h>

//wiFi and thingspeak config
const char* ssid = "PLDTHOMEFIBRt6ucX";
const char* password = "PLDTWIFItLK72";
const long channel = 2964917;
const char key[] = "18A6ZBU4I3OLZZ44";

// pin definitions
const int RED_LED = 23, WHITE_LED = 19, buzzer = 13, flamePin = 18;
const int floorBtn = 14;

// variables
int floorLevel = 1;
int flame = 0;
int fireCounts[6] = {0}; // fire counters
bool lastBtnState = HIGH;
unsigned long lastUpdate = 0;
WiFiClient client;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(WHITE_LED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(flamePin, INPUT);
  pinMode(floorBtn, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  lcd.clear();

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(100);
  ThingSpeak.begin(client);

}

void loop() {
  flame = digitalRead(flamePin);

  if (flame == LOW) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(WHITE_LED, LOW);
    if(floorLevel >= 1 && floorLevel <= 5) {
      fireCounts[floorLevel]++;
    }
  } else {
     digitalWrite(buzzer, LOW);
     digitalWrite(RED_LED, LOW);
     digitalWrite(WHITE_LED, HIGH);
  }

  // button for the floor levels
  bool currentBtnState = digitalRead(floorBtn);
  if (lastBtnState == HIGH && currentBtnState == LOW) {
    floorLevel = (floorLevel % 5) + 1;
    delay(200);
  }
  lastBtnState = currentBtnState;

  // LCD output
  lcd.setCursor(0, 0);
  lcd.print("Floor: ");
  lcd.print(floorLevel);
  lcd.print("     ");

  lcd.setCursor(0, 1);
  lcd.print("Flame: ");
  lcd.print(flame == LOW ? "YES " : "No ");
  lcd.print("   "); 

  if (millis() - lastUpdate > 15000) {
    lastUpdate = millis();
    ThingSpeak.setField(1, flame);
    ThingSpeak.setField(2, floorLevel);
    ThingSpeak.setField(3, fireCounts[1]);
    ThingSpeak.setField(4, fireCounts[2]);
    ThingSpeak.setField(5, fireCounts[3]);
    ThingSpeak.setField(6, fireCounts[4]);
    ThingSpeak.setField(7, fireCounts[5]);

    int result = ThingSpeak.writeFields(channel, key);
    if(result == 200) {
      Serial.println("Data sent to ThingSpeak.");
    } else {
      Serial.print("Failed to send data. HTTP error: ");
      Serial.println(result);
    }
  }
}
