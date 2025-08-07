#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <ThingSpeak.h>
#include <ESP32Servo.h>

// WiFi Configuration
const char* ssid = "PLDTHOMEFIBRt6ucX";
const char* password = "PLDTWIFItLK72";

// ThingSpeak Configuration
const long myChannelNumber = 2964917 ;
const char myWriteAPIKey[] = "18A6ZBU4I3OLZZ44";

//hardware configuration
const int MOISTURE_PIN = 34;
const int WHITE_LED = 19;
const int YELLOW_LED = 4;
const int GREEN_LED = 18;
const int BLUE_LED = 5;
const int RED_LED = 23;
const int SERVO_PIN = 13;

//default calibration values (4095 for dry and 1550 for saturated)
int dryValue = 4095;
int saturatedValue = 1550;
const int NUM_READINGS = 50;

//LCD and servo
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo irrigationServo;
int servoPosition = 0;

// system parameters
const int UPDATE_INTERVAL = 5000;
unsigned long lastUpdate = 0;
WiFiClient client;
bool servoActivated = false;


void setup() {
  initializePins();
  initializeDisplay();
  initializeSerial();
  showStartupScreen();
  calibrateSensor();
  connectToWiFi();
  ThingSpeak.begin(client);
}

void loop() {
 int moisture = readMoisture();
 updateDisplay(moisture);
 updateLEDs(moisture);
 sendToCloud(moisture);
 delay(1000);
}

 // initialize functions
 void initializePins() {
  pinMode(WHITE_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  irrigationServo.attach(SERVO_PIN);
  allLEDsOff();
 }

 void initializeSerial() {
  Serial.begin(115200);
  while(!Serial);
 }
 void initializeDisplay() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
 }

 // core functions
 void calibrateSensor(){
  lcd.clear();
  lcd.print("Calibration Mode");

  // dry calibration
  lcd.setCursor(0,1);
  lcd.print("Dry Measurement");
  dryValue = getStableReading();

  // wet calibration
  lcd.setCursor(0, 1);
  lcd.print("Wet Measurement");
  saturatedValue = getStableReading();

  lcd.clear();
  lcd.print("Calibration Done!");
  lcd.setCursor(0, 1);
  lcd.print(dryValue);
  lcd.print(" - ");
  lcd.print(saturatedValue);
  delay(2000);
 }

 int getStableReading() {
  int total = 0;
  for(int i = 0; i < NUM_READINGS; i++) {
    total += analogRead(MOISTURE_PIN);
    delay(50);
  }
  return total / NUM_READINGS;
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

 // moisture functions
  int readMoisture() {
    return analogRead(MOISTURE_PIN);
  }

 void updateDisplay(int moisture ) {
    lcd.clear();

    // line 1: Raw value
    lcd.setCursor(0, 0);
    lcd.print("Raw: ");
    lcd.print(moisture);

    // line 2: Moisture level
    lcd.setCursor(0, 1);
    lcd.print("Level: ");
    lcd.print(getMoistureLevelString(moisture));
  } 

    String getMoistureLevelString(int value) {
      if(value >= dryValue - (dryValue - saturatedValue)*0.2) return "Dry       ";
      if(value >= dryValue - (dryValue - saturatedValue)*0.4) return "Low       ";
      if(value >= dryValue - (dryValue - saturatedValue)*0.6) return "Moderate  ";
      if(value >= saturatedValue + 100) return "High       ";
      return "Saturated";
    }
    
    // control function
  void activateMotor() {
      servoActivated = true;
      for (servoPosition = servoPosition; servoPosition <= 120; servoPosition++) {
        irrigationServo.write(servoPosition);
        delay(19);
      }
      delay(1000);
      for (servoPosition = servoPosition; servoPosition >= 0; servoPosition--) {
        irrigationServo.write(servoPosition);
        delay(5);
      }
      delay(1000);
    }

  void deactivateMotor() {
      servoActivated = false;
      servoPosition = 0;
    }

    // LED control
  void updateLEDs(int moisture) {
      allLEDsOff();

      int range = dryValue - saturatedValue;
      if(moisture >= dryValue - range*0.2) {
        digitalWrite(WHITE_LED, HIGH);
        activateMotor();
      } else if(moisture >= dryValue - range*0.4) {
        digitalWrite(YELLOW_LED, HIGH);
        activateMotor();
      } else if(moisture >= dryValue - range*0.6) {
        digitalWrite(GREEN_LED, HIGH);
        deactivateMotor();
      } else if(moisture >= saturatedValue + 100) {
        digitalWrite(BLUE_LED, HIGH);
        deactivateMotor();
      } else {
        digitalWrite(RED_LED, HIGH);
        deactivateMotor();
      }
    }

  void allLEDsOff() {
      digitalWrite(WHITE_LED, LOW);
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(BLUE_LED, LOW);
      digitalWrite(RED_LED, LOW);
    }

  // cloud functions
  void sendToCloud(int moisture) {
    if(millis() - lastUpdate >= UPDATE_INTERVAL) {
      lastUpdate = millis();

      ThingSpeak.setField(1, moisture);
      ThingSpeak.setField(2, map(moisture, dryValue, saturatedValue, 0, 100));
      ThingSpeak.setField(3, servoActivated);

      int status = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

      if(status == 200) {
        lcd.clear();
        lcd.print("Cloud Update OK");
        delay(1000);
      }
    }
  }
  // ultility function
  void showStartupScreen() {
    lcd.setCursor(0,0);
    lcd.print("Soil Moisture");
    lcd.setCursor(0, 1);
    lcd.print("Monitoring Time!");
    delay(2000);
    lcd.clear();
  }



