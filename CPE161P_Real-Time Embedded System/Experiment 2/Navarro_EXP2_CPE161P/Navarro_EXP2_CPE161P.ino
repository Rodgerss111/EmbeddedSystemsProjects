
const int sPins[7] = {A3,A2, A1,12,8,9,10};
const int dPins[4] = {4,5,6,7};
const int buzzerAlarm = 13;
const int ledGreen = 2;
const int ledYellow = 3;
const int ledRed = 11;
const int triggerPin = A5;
const int echoPin = A4;

const int switchPins = A0;
int timeGo = 60;
int timeStop = 0;
int maxCountdown = 60;
bool settingStop = true;
bool isStopTimerRunning = true;

unsigned long previousMillis = 0;

const long interval  = 1000;
bool timerRunning = true;
int messageIndex = 0;
int cm = 0;

byte digitCodes[10]{
  B00111111, B00000110, B01011011, B01001111,
  B01100110, B01101101, B01111101, B00000111,
  B01111111, B01101111
};



void setup() {
  Serial.begin(9600);

  pinMode(buzzerAlarm, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  for(int i= 0; i<7; i++){
    pinMode(sPins[i], OUTPUT);
  }

  for (int i=0; i<4; i++){
    pinMode(dPins[i], OUTPUT);
    digitalWrite(dPins[i], HIGH);

  }

  displayTimer(timeStop, timeGo);

}

void loop() {
  int buttonValue = analogRead(switchPins);
  Serial.print("Analog value: ");
  Serial.print(buttonValue);

  int allButtons = digitalRead(switchPins);

  if (buttonValue < 5){
    allButtons = LOW;
  } else if (buttonValue < 25){
    Serial.println("Button 1 Pressed");
    decrementTimer();
    delay(500);
  } else{
    incrementTimer();
    Serial.println("Button 2 Pressed");
    delay(500);
  }

    unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (isStopTimerRunning) {
      
      if (timeStop < 60) {
       timeStop++;
       detectUltrasonic();
       digitalWrite(ledRed, HIGH);
         if(timeStop >= 30){
          digitalWrite(ledYellow, HIGH);
          digitalWrite(ledRed, LOW);
        }else{
          digitalWrite(ledYellow, LOW);

        }
      } else {
        // Switch to Go Timer
        isStopTimerRunning = false;
       timeStop = 0; // Reset Stop Timer
       digitalWrite(ledRed, LOW);

      } 
      
    } else {
      // Countdown for Go Timer
      if (timeGo > 0) {
        timeGo--;
        digitalWrite(ledGreen, HIGH);
        if(timeGo <= 30){
          digitalWrite(ledYellow, HIGH);
          digitalWrite(ledGreen, LOW);
        }else{
          digitalWrite(ledYellow, LOW);
        }
      } else {
        // Switch to Stop Timer
        isStopTimerRunning = true;
        timeGo = 60; // Reset Go Timer
        digitalWrite(ledGreen, LOW);
      }
    }

  }
 displayTimer(timeStop, timeGo);
}

 void incrementTimer(){
  if (isStopTimerRunning == false) {
         timeGo += 30;
      } if (timeGo >= 60) {
        timeGo = 60;
    }
 }

  void decrementTimer(){
  if (isStopTimerRunning == true) {
         timeStop -= 15;
      } if (timeStop <= 0) {
        timeStop = 0;
    }
 }


 void displayTimer(int forStop, int forGo){
  int digits[4] = {forStop/10, forStop % 10, forGo/10, forGo % 10};

  for (int i=0; i<4; i++){
    digitalWrite(dPins[i], LOW);
    setSegments(digitCodes[digits[i]]);
    delay(5);
    digitalWrite(dPins[i], HIGH);
  }
 }

void setSegments(byte segments){
  for (int i=0; i<7; i++){
    digitalWrite(sPins[i], (segments >> i)& 0x01);
  }
}

void detectUltrasonic(){
  long distance = readUltrasonicDistance(triggerPin, echoPin);
  if(distance <= 10){
    digitalWrite(buzzerAlarm, HIGH);
    delay(5000);
  }else{
    digitalWrite(buzzerAlarm, LOW);
  }
}

long readUltrasonicDistance(int triggerPin, int echoPin){
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  return pulseIn(echoPin, HIGH) * 0.034 /2;
}




