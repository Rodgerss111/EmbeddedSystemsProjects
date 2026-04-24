
#include <LiquidCrystal_I2C.h>

const int sPins[7] = {A3, A2, A1, 12, 8, 9, 10};
const int dPins[4] = {4, 5, 6, 7};
const int dppin = 1;
const int buzzAlarm = 11;
const int ledGreen = 13;
const int triggerPin = 3;
const int echoPin = 2;

const int switch1Pin = A0; // All buttons
int sittingMinutes = 19;
int standingMinutes = 9;
int maxMinutes = 30;
bool settingSitting = true; // start with sitting timer
bool adjustMode = true; 

unsigned long previousMillis = 0;
unsigned long messageMillis = 0;
const long interval = 1000; // 1 second interval for countdown;
const long messageInterval = 5000; // 5 seconds for each message in the LCD
int minutes = sittingMinutes;
int seconds = 0;
bool timerRunning = true; // Control pause and resume
int messageIndex = 0;
int cm = 0;

byte digitCodes[10] = {
  B00111111, B00000110, B01011011, B01001111,
  B01100110, B01101101, B01111101, B00000111,
  B01111111, B01101111
};

LiquidCrystal_I2C dis(0x27, 16, 2);

const char* sittingMessages[] = {
  " Focus on Work!  ", " Keep Grinding!  ", "  Stay Sharp!!  ",
  "You're on Track!", "Reach your Goal"
};

const char* standingMessages[] = {
  "Stand & Stretch!", "Move your Body!!", " Shake it out!!  ", 
  "Feel Refreshed!!", " Time to Stand!  "
};


void setup() {
  Serial.begin(9600);
 
  pinMode(buzzAlarm, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  for (int i= 0; i<7; i++){
    pinMode(sPins[i], OUTPUT);
  }

  for (int i=0; i<4; i++){
    pinMode(dPins[i], OUTPUT);
    digitalWrite(dPins[i], HIGH);
  }

  pinMode(dppin, OUTPUT);
  displayTime(minutes, seconds);

  dis.init();
  dis.backlight();
  dis.clear();
  dis.setCursor(0,0);
  dis.print("StandUp Reminder");
  dis.setCursor(3, 1);
  dis.print("Good Day!");

  for (int a = 12; a <= 15; a++){
    dis.setCursor(a, 1);
    dis.print(".");
    delay(1500);
  }
  dis.clear();
}


void loop() {

  int buttonValue = analogRead(switch1Pin);
  Serial.print("Analog value: ");
  Serial.print(buttonValue);

  int allButtons = digitalRead(switch1Pin);

  if (buttonValue <100){
    allButtons = LOW;
  } else if (buttonValue < 150){
    incrementTimer(true);
    delay(500);
  } else if (buttonValue < 250){
    decrementTimer(true);
    delay(500);
  }else if (buttonValue < 350){
    incrementTimer(false);
    delay(500);
  }else if (buttonValue < 850){
    decrementTimer(false);
    delay(500);
  }else {
    switchTimerMode();
    delay(500);
  }

  if (timerRunning) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval){
      previousMillis = currentMillis;
      if (seconds == 0){
        if (minutes > 0){
          minutes--;
          seconds = 59;
        } else {
          completeTimer();
        }
      } else {
        seconds--;
      }
    }
    if (currentMillis - messageMillis >= messageInterval){
      messageMillis = currentMillis;
      displayMotivationalMessage();
    }
  }
    displayTime(minutes, seconds);

}

void incrementTimer(bool sitting) {
  if (sitting) {
    if(sittingMinutes < maxMinutes) sittingMinutes++;
    if(settingSitting) minutes = sittingMinutes;
  } else{
    if (standingMinutes < maxMinutes) standingMinutes++;
    if (!settingSitting) minutes = standingMinutes;
  }
}

void decrementTimer(bool sitting) {
  if (sitting) {
    if(sittingMinutes > 0) sittingMinutes--;
    if(settingSitting) minutes = sittingMinutes;
  } else{
    if (standingMinutes > 0) standingMinutes--;
    if (!settingSitting) minutes = standingMinutes;
    }
  }
void switchTimerMode(){
  settingSitting = !settingSitting;
  timerRunning = true;

  if (settingSitting) {
    minutes = sittingMinutes;
    Serial. println("Switched to Sitting Timer");
    dis.setCursor(2, 1);
    dis.print("Sitting Time ");
    seconds = 59;
  } else {
    minutes = standingMinutes;
    Serial.println("Switched to Standing Timer");
    dis.setCursor(2, 1);
    dis.print("Stand Up Time");
    seconds = 59;
  }
}

void displayMotivationalMessage(){
  dis.setCursor(0, 0);
  if (settingSitting) {
    dis.print(sittingMessages[messageIndex]);
  } else{
    dis.print(standingMessages[messageIndex]);
  }
  messageIndex = (messageIndex + 1) % 5;
}

void displayTime(int mins, int secs){
  int digits[4] = {mins/10, mins % 10, secs/10, secs % 10};

  for (int i=0; i<4; i++) {
    digitalWrite(dPins[i], LOW);
    setSegments(digitCodes[digits[i]]);
    delay(5);
    digitalWrite(dPins[i], HIGH);
  }
}

void setSegments(byte segments) {
  for (int i=0; i<7; i++) {
    digitalWrite(sPins[i], (segments >> i) & 0x01);
  }
}

void completeTimer() {
  turnOffDisplay;
  for (int i=0; i<5; i++){
    digitalWrite(buzzAlarm, HIGH);
    delay(100);
    digitalWrite(buzzAlarm, LOW);
    delay(100);
  }

  if(settingSitting) {
    for (int i=0; i<5; i++){
      digitalWrite(ledGreen, HIGH);
      delay(100);
      digitalWrite(ledGreen, LOW);
      delay(100);
    }
  }
  detectUltrasonic();
}

void turnOffDisplay(){
  for (int i=0; i<4; i++){
    digitalWrite(dPins[i], HIGH);
  }
  for (int i=0; i<7; i++){
    digitalWrite(sPins[i], LOW);
  }
}

void detectUltrasonic() {
  long distance = readUltrasonicDistance(triggerPin, echoPin);
  if (distance <= 10) {
    settingSitting = !settingSitting;
    if (settingSitting) {
      minutes = sittingMinutes;
      dis.setCursor(2, 1);
      dis.print("Sitting Time ");
    } else {
      minutes = standingMinutes;
      dis.setCursor(2, 1);
      dis.print("Stand Up Time");
    }
    seconds = 59;
    timerRunning = true;
  }
}

long readUltrasonicDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}

  

