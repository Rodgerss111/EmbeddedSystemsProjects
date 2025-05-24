const int sPins[7] = {A3,A2, A1,12,8,9,10};
const int dPins[4] = {4,5,6,7};

const int dppin = 1;


const int switch1Pin =13;
const int switch2Pin = A0;

int hours = 12;
int minutes = 0;
bool adjustMinutes = true;
bool incrementMode = true;

unsigned long previousMillis = 0;
const long interval = 60000; // for 1 minute
unsigned long lastSwitch1PressTime = 0;
unsigned long lastSwitch2PressTime = 0;
const int debounceDelay = 50;
bool lastSwitch1State = HIGH;
bool lastSwitch2State = HIGH;

//for the seven segment 0 - 9
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
  B01101111,
};



void setup() {
 for (int i = 0; i < 7; i++) {
    pinMode(sPins[i], OUTPUT);
 }

  for (int i = 0; i < 4; i++) {
    pinMode(dPins[i], OUTPUT);
    digitalWrite(dPins[i], HIGH);
  }

  pinMode(dppin, OUTPUT);

  pinMode(switch1Pin, INPUT);
  pinMode(switch2Pin, INPUT);

  displayTime(hours, minutes);

}

void loop() {
  bool switch1State = digitalRead(switch1Pin);
  bool switch2State = digitalRead(switch2Pin);

  digitalWrite(dppin, HIGH);

  if(switch1State != lastSwitch1State) {
      if(switch1State == LOW && millis() - lastSwitch1PressTime > debounceDelay) {
        adjustMinutes = !adjustMinutes;
        lastSwitch1PressTime = millis();
      }
      lastSwitch1State = switch1State;
  }
  

  if(switch2State != lastSwitch2State) {
    if(switch2State == LOW && millis() - lastSwitch2PressTime > debounceDelay) {
      if(incrementMode) {
        if(adjustMinutes) {
          incrementMinute();
        }
        else{
          incrementHour();
        }
      } else{
        if(adjustMinutes){
          decrementMinute();
        }else {
          decrementHour();
        }
      }
      lastSwitch2PressTime = millis();
    }
    lastSwitch2State = switch2State;

  }

  // this will handle the ticking
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    incrementMinute();
  }

// display
displayTime(hours, minutes);

}


void incrementMinute() {
  minutes++;
  if (minutes >= 60) {
    minutes = 0;
    incrementHour();
  }
  }

void decrementMinute() {
  minutes--;
  if(minutes < 0){
    minutes = 59;
    decrementHour();
  }
}

void incrementHour() {
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

// final

void displayTime(int hrs, int mins){
  int digits[4] = {hrs/10, hrs % 10, mins/10, mins % 10};


  for(int i = 0; i < 4; i++) {
    digitalWrite(dPins[i], LOW);

    setSegments(digitCodes[digits[i]]);

    delay(5);
    digitalWrite(dPins[i], HIGH);

  }
}

void setSegments(byte segments) {
  for(int i = 0; i < 7; i++) {
    digitalWrite(sPins[i], (segments >> i) & 0x01);
  }
}






















