#include <LiquidCrystal_I2C.h>
const int sPins[7] = {A3,A2,A1,12,8,9,10};
const int dPins[4] = {4,5,6,7};

int hours = 0;
int minutes = 0;
int seconds = 0;
bool adjustMinutes = true;
bool incrementMode = true;
LiquidCrystal_I2C lcd(0x27, 16,2);

unsigned long previousMillis = 0;
unsigned long previousMillisSeconds = 0;
const long interval = 60000;
const long intervalSeconds = 1000;
const int debounceDelay = 50;

byte digitCodes[10] = {
  B00111111,
  B00000110,
  B01011011,
  B01001111,
  B01100110,
  B01101101,
  B01111101,
  B00000111,
  B01111111,
  B01101111
};

void setup() {
  lcd.init();
  lcd.backlight();
  for (int i = 0; i < 7; i++){
    pinMode(sPins[i], OUTPUT);
  }
  for(int i = 0; i < 4; i++){
    pinMode(dPins[i], OUTPUT);
    digitalWrite(dPins[i], HIGH);
  }

  displayTime(hours, minutes);
  displaySeconds(seconds);

}

void loop() {
  unsigned long currentMillis = millis();

    if(currentMillis - previousMillisSeconds >= intervalSeconds){
    previousMillisSeconds = currentMillis;
    incrementSeconds();
  }

  if(currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    //incrementMinute();
  }

  displayTime(hours, minutes);
  displaySeconds(seconds);
  
}

void incrementMinute(){
  minutes++;
  if(minutes >= 60){
    minutes = 0;
    incrementHour();
  }
}

void decrementMinutes(){
  minutes--;
  if(minutes < 0){
    minutes = 59;
    decrementHour();
  }
}

void incrementSeconds(){
  seconds++;
  if(seconds >= 60){
    seconds = 0;
    incrementMinute();
  }
}

void incrementHour(){
  hours++;
  if(hours > 12){
    hours = 1;
  }
}

void decrementHour(){
  hours--;
  if(hours < 1){
    hours = 12;
  }
}

void displayTime(int hrs, int mins){
  int digits[4] = {hrs/10, hrs%10, mins/10, mins%10};

  for(int i = 0; i<4; i++){
    digitalWrite(dPins[i], LOW);
    setSegments(digitCodes[digits[i]]);
    delay(4);
    digitalWrite(dPins[i], HIGH);
  }
}

void setSegments(byte segments){
  for(int i = 0; i<7; i++){
    digitalWrite(sPins[i], (segments >> i) & 0x01);
  }
}

void displaySeconds(int secs){
  lcd.clear();
  lcd.setCursor(1,1);

  if(secs < 10) lcd.print("0");
  lcd.print(secs);

}