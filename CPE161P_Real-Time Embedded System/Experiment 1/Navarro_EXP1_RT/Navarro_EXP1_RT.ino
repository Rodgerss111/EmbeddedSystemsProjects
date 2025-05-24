const int sPins[7] = {6, 7, 8 ,9, 10, 11, 12};
const int dPins[4] = {2, 3, 4, 5};

const int switch1Pin = A5;
const int switch2Pin = A4;
const int switch3Pin = A3;
const int switch4Pin = A2;
const int switch5Pin = A1;

const int teamALED = A0;
const int teamBLED = 13;

int teamA = 0;
int teamB = 0;

bool adjustScore = true;
bool incrementMode = true;

unsigned long lastSwitch1PressTime = 0;
unsigned long lastSwitch2PressTime = 0;
unsigned long lastSwitch3PressTime = 0;
unsigned long lastSwitch4PressTime = 0;
unsigned long lastSwitch5PressTime = 0;

bool lastSwitch1State = HIGH;
bool lastSwitch2State = HIGH;
bool lastSwitch3State = HIGH;
bool lastSwitch4State = HIGH;
bool lastSwitch5State = HIGH;

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

void setup(){
  for (int i = 0; i < 7; i++){
    pinMode(sPins[i], OUTPUT);
  }

  for(int i = 0; i < 4; i++){
    pinMode(dPins[i], OUTPUT);
    digitalWrite(dPins[i], HIGH);
  }

  pinMode(switch1Pin, INPUT);
  pinMode(switch2Pin, INPUT);
  pinMode(switch3Pin, INPUT);
  pinMode(switch4Pin, INPUT);
  pinMode(switch5Pin, INPUT);

  pinMode(teamALED, OUTPUT);
  pinMode(teamBLED, OUTPUT);


  displayScore(teamA, teamB);


}

void loop(){

bool switch1State = digitalRead(switch1Pin);
bool switch2State = digitalRead(switch2Pin);
bool switch3State = digitalRead(switch3Pin);
bool switch4State = digitalRead(switch4Pin);
bool switch5State = digitalRead(switch5Pin);

if(switch1State != lastSwitch1State){
if(switch1State != LOW){
  if(incrementMode){
    if(adjustScore){
      incrementAThree();
    }
    else{
      incrementBThree();
    }
  }
}

lastSwitch1State = switch1State;

}

if(switch2State != lastSwitch2State){
if(switch2State != LOW){
  if(incrementMode){
    if(adjustScore){
      incrementATwo();
    }
    else{
      incrementBTwo();
    }
  }
}


lastSwitch2State = switch2State;

}

if(switch3State != lastSwitch3State){
if(switch3State != LOW){
  if(incrementMode){
    if(adjustScore){
      incrementAOne();
    }
    else{
      incrementBOne();
    }
  }
}


lastSwitch3State = switch3State;

}

if(switch4State != lastSwitch4State){

if(switch4State != lastSwitch4State) {
  if(switch4State == LOW){
    adjustScore = !adjustScore;
  }
}
lastSwitch4State = switch4State;

}

if(switch5State != lastSwitch5State){
if(switch5State != LOW){
  if(incrementMode){
    if(adjustScore){
      decrementA();
    }
    else{
      decrementB();
    }
  }
}

lastSwitch5State = switch5State;

}

if(adjustScore){
  digitalWrite(teamALED, HIGH);
  digitalWrite(teamBLED, LOW);
}else{
  digitalWrite(teamBLED, HIGH);
  digitalWrite(teamALED, LOW);
}

displayScore(teamA, teamB);


}

void incrementAThree(){
  teamA += 3;
  if (teamA >= 99) {
    teamA = 0;
  }
}


void incrementATwo(){
  teamA += 2;
  if (teamA >= 99) {
    teamA = 0;
  }
}

void incrementAOne(){
  teamA += 1;
  if (teamA >= 99) {
    teamA = 0;
  }
}

void incrementBThree(){
  teamB += 3;
  if (teamB >= 99) {
    teamB = 0;
  }
}
void incrementBTwo(){
  teamB += 2;
  if (teamB >= 99) {
    teamB = 0;
  }
}

void incrementBOne(){
  teamB += 1;
  if (teamB >= 99) {
    teamB = 0;
  }
}


void decrementA(){
  teamA --;
  if (teamA < 0) {
    teamA = 0;
  }
}

void decrementB(){
  teamB --;
  if (teamB < 0) {
    teamB = 0;
  }
}

void displayScore(int team1, int team2){
  int digits[4] = {team1/10, team1%10, team2/10, team2%10};

  for(int i = 0; i < 4; i++) {
    digitalWrite(dPins[i], LOW);

    setSegments(digitCodes[digits[i]]);

    delay(5);
    digitalWrite(dPins[i], HIGH);
  }
}


void setSegments(byte segments){
  for (int i = 0; i < 7; i++) {
    digitalWrite(sPins[i], (segments >> i) & 0x01);
  }
}





