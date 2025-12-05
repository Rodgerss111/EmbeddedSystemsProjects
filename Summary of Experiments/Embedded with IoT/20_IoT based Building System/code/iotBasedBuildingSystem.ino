#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <ThingSpeak.h>

// WiFi Configuration
const char* ssid = "PLDTHOMEFIBRt6ucX";
const char* password = "PLDTWIFItLK72";

// ThingSpeak Configuration
const long myChannelNumber = 2964917;
const char myWriteAPIKey[] = "18A6ZBU4I3OLZZ44";

// Hardware Configuration
const int ENTRANCE_TRIG = 27;
const int ENTRANCE_ECHO = 26;
const int EXIT_TRIG = 25;
const int EXIT_ECHO = 33;
const int LED_PINS[] = {19, 18, 17, 16, 4}; // 5 LEDs

// System Parameters
const int UPDATE_INTERVAL = 15000;
const int MAX_PEOPLE = 50;
const int DISTANCE_THRESHOLD = 10; // cm
const int DEBOUNCE_DELAY = 500;   // ms

// Global Variables
LiquidCrystal_I2C lcd(0x27, 16, 2);
WiFiClient client;
int peopleCount = 0;
unsigned long lastUpdate = 0;
unsigned long lastEntranceTrigger = 0;
unsigned long lastExitTrigger = 0;


void setup() {
  // Initialize hardware
  initializePins();
  initializeDisplay();
  initializeSerial();
  
  // Connect to WiFi
  connectToWiFi();
  ThingSpeak.begin(client);
}

void loop() {
  // Update people count
  updatePeopleCount();
  
  // Control lights based on occupancy
  updateLighting();
  
  // Update display
  updateDisplay();
  
  // Send data to cloud
  sendToCloud();
  
  delay(100);
}

void initializePins() {
  // Initialize ultrasonic sensors
  pinMode(ENTRANCE_TRIG, OUTPUT);
  pinMode(ENTRANCE_ECHO, INPUT);
  pinMode(EXIT_TRIG, OUTPUT);
  pinMode(EXIT_ECHO, INPUT);
  
  // Initialize LEDs
  for (int i = 0; i < 5; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
  }
}

void initializeSerial() {
  Serial.begin(115200);
  while(!Serial);
}

void initializeDisplay() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System Starting");
}

void connectToWiFi() {
  lcd.clear();
  lcd.print("Connecting WiFi");
  
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    lcd.print(".");
  }
  
  lcd.clear();
  lcd.print("WiFi Connected!");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  delay(2000);
}

int readUltrasonic(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2; // Return distance in cm
}

void updatePeopleCount() {
  int entranceDist = readUltrasonic(ENTRANCE_TRIG, ENTRANCE_ECHO);
  int exitDist = readUltrasonic(EXIT_TRIG, EXIT_ECHO);
  
  unsigned long currentTime = millis();
  
  // Check entrance
  if (entranceDist < DISTANCE_THRESHOLD && 
      currentTime - lastEntranceTrigger > DEBOUNCE_DELAY) {
    peopleCount = min(peopleCount + 1, MAX_PEOPLE);
    lastEntranceTrigger = currentTime;
    Serial.println("Person entered");
  }
  
  // Check exit
  if (exitDist < DISTANCE_THRESHOLD && 
      currentTime - lastExitTrigger > DEBOUNCE_DELAY) {
    peopleCount = max(peopleCount - 1, 0);
    lastExitTrigger = currentTime;
    Serial.println("Person exited");
  }
}

void updateLighting() {
  // Turn off all lights first
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_PINS[i], LOW);
  }
  
  // Control lights based on occupancy
  if (peopleCount == 0) {
    // All lights off
  } 
  else if (peopleCount < 4) {
    // 1 light on
    digitalWrite(LED_PINS[0], HIGH);
  } 
  else if (peopleCount < 10) {
    // 3 lights on
    for (int i = 0; i < 3; i++) {
      digitalWrite(LED_PINS[i], HIGH);
    }
  } 
  else if (peopleCount < 20) {
    // 4 lights on
    for (int i = 0; i < 4; i++) {
      digitalWrite(LED_PINS[i], HIGH);
    }
  } 
  else {
    // All 5 lights on
    for (int i = 0; i < 5; i++) {
      digitalWrite(LED_PINS[i], HIGH);
    }
  }
}

void updateDisplay() {
  
  // Line 1: People count
  lcd.setCursor(0, 0);
  lcd.print("People: ");
  lcd.print(peopleCount);

  if (peopleCount < 10){
  lcd.setCursor(9, 0);
  lcd.print("       ");
  }
  // Line 2: Lights status
  lcd.setCursor(0, 1);
  lcd.print("Lit: ");
  
  if (peopleCount == 0) lcd.print("OFF");
  else if (peopleCount < 4) lcd.print("LOW");
  else if (peopleCount < 10) lcd.print("MED");
  else if (peopleCount < 20) lcd.print("HIGH");
  else lcd.print("FULL");
  
  lcd.print(" (");
  lcd.print(getActiveLights());
  lcd.print("/5) ");
}

int getActiveLights() {
  if (peopleCount == 0) return 0;
  if (peopleCount < 4) return 1;
  if (peopleCount < 10) return 3;
  if (peopleCount < 20) return 4;
  return 5;
}

void sendToCloud() {
  if (millis() - lastUpdate >= UPDATE_INTERVAL) {
    lastUpdate = millis();
    
    // Send data to ThingSpeak
    ThingSpeak.setField(1, peopleCount); // people count
    ThingSpeak.setField(2, getActiveLights()); // active lights
    
    // Send individual LED status
    for (int i = 0; i < 5; i++) {
      ThingSpeak.setField(3 + i, digitalRead(LED_PINS[i])); // usage of lights in the building floor
    }
    
    int status = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey); 
    
    if (status == 200) {
      Serial.println("Cloud update successful");
    } else {
      Serial.println("Cloud update failed. Error: " + String(status));
    }
  }
}
