#include <WiFi.h>
#include <ThingSpeak.h>
#include <IRremote.hpp>

// WiFi credentials
const char* ssid = "PLDTHOMEFIBRt6ucX";
const char* password = "PLDTWIFItLK72";

// ThingSpeak setup
WiFiClient client;
long myChannelNumber = 2946540;
const char myWriteAPIKey[] = "V3OSQVGH8LFTTBE1";

// IR and device pins
const int irRemotePin = 16;  // Changed from 15 to avoid boot issues
const int lightLed = 22;
const int buzzAlarm = 23;
int portIN1 = 5;
int portIN2 = 18;
int portIN3 = 19;
int portIN4 = 21;

// State variables
bool motorState = false;
int lightStatus = 0;
int buzzerStatus = 0;
int fanStatus = 0;

// ThingSpeak timer
unsigned long lastUpdate = 0;
const unsigned long updateInterval = 15000;

void setup() {
  Serial.begin(9600);
  delay(1000);

  pinMode(lightLed, OUTPUT);
  pinMode(buzzAlarm, OUTPUT);
  pinMode(portIN1, OUTPUT);
  pinMode(portIN2, OUTPUT);
  pinMode(portIN3, OUTPUT);
  pinMode(portIN4, OUTPUT);

  IrReceiver.begin(irRemotePin, ENABLE_LED_FEEDBACK);  // Start IR receiver

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
}

void loop() {
  // Handle IR input
  if (IrReceiver.decode()) {
    Serial.print("Received IR code: ");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    IrReceiver.printIRResultShort(&Serial);
    executeCommand(IrReceiver.decodedIRData.decodedRawData);
    IrReceiver.resume();
  }

  // Stepper motor control
  if (motorState) {
    stepSequence(1, 0, 0, 0);
    delay(2);
    stepSequence(0, 1, 0, 0);
    delay(2);
    stepSequence(0, 0, 1, 0);
    delay(2);
    stepSequence(0, 0, 0, 1);
    delay(2);
  } else {
    stepSequence(0, 0, 0, 0);
  }

  // ThingSpeak update every 15 seconds
  if (millis() - lastUpdate >= updateInterval) {
    lastUpdate = millis();

    lightStatus = digitalRead(lightLed);
    buzzerStatus = digitalRead(buzzAlarm);
    fanStatus = motorState ? 1 : 0;

    ThingSpeak.setField(1, lightStatus);
    ThingSpeak.setField(2, buzzerStatus);
    ThingSpeak.setField(3, fanStatus);

    int statusCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    if (statusCode == 200) {
      Serial.println("Channel update successful.");
    } else {
      Serial.print("ThingSpeak update error. Code: ");
      Serial.println(statusCode);
    }
  }
}

void executeCommand(unsigned long command) {
  switch (command) {
    case 0xF30CFF00: Serial.println("1: Toggle Motor"); moveStepper(); break;
    case 0xF708FF00: Serial.println("4: Toggle Light"); lightControl(); break;
    case 0xE31CFF00: Serial.println("5: Toggle Buzzer"); buzzerControl(); break;
    case 0xB54AFF00: Serial.println("9: Reset All"); resetAll(); break;
    default: Serial.println("Unrecognized command."); break;
  }
}

void moveStepper() {
  motorState = !motorState;
}

void lightControl() {
  digitalWrite(lightLed, !digitalRead(lightLed));
  delay(50);
}

void buzzerControl() {
  digitalWrite(buzzAlarm, !digitalRead(buzzAlarm));
  delay(50);
}

void stepSequence(int in1, int in2, int in3, int in4) {
  digitalWrite(portIN1, in1);
  digitalWrite(portIN2, in2);
  digitalWrite(portIN3, in3);
  digitalWrite(portIN4, in4);
}

void resetAll() {
  motorState = false;
  digitalWrite(lightLed, LOW);
  digitalWrite(buzzAlarm, LOW);
}
