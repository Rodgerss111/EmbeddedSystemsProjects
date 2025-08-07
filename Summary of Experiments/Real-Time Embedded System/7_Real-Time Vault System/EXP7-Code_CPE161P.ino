const char rows = 4;
const char cols = 4;
const int buzzAlarm = 9;
const int servoPin = 12;

const char correctPassword[] = "637921";
char enteredPassword[7];
int passwordIndex = 0;
bool vaultOpen = false;
unsigned long vaultCloseTime = 0;

const char keys[rows][cols] = {
  {'D', '*', '0','#'},
  {'C', '9', '8','7'},
  {'B', '6', '5','4'},
  {'A', '3', '2','1'}
};

char rowPins[rows] = {A5, A4, A3, A2};
char colPins[cols] = {A1, A0, 2, 3};

void setup() {
  Serial.begin(9600);
  pinMode(servoPin, OUTPUT);
  pinMode(buzzAlarm, OUTPUT);

for(char r = 0; r < rows; r++) {
  pinMode(rowPins[r], INPUT);
  digitalWrite(rowPins[r], HIGH);
}


for(char c = 0; c < cols; c++){
  pinMode(colPins[c], OUTPUT);
}
 closeVault();
}

void loop() {
 char key = getKey();
 if(key !=0){
  Serial.println(key);
  handleKeyPress(key);
 }

 if(vaultOpen && millis() >= vaultCloseTime) {
  closeVault();
 }
}

char getKey(){
  char k = 0;
  for (char c = 0; c < cols; c++) {
    digitalWrite(colPins[c], LOW);
    for(char r = 0; r < rows; r++){
      if(digitalRead(rowPins[r]) == LOW){
      delay(20);
      while (digitalRead(rowPins[r]) == LOW);
      k = keys[r][c];
    }
  }
  digitalWrite(colPins[c], HIGH);
}
  return k;
}


void handleKeyPress(char key){
  if(key == '#') {
    passwordIndex = 0;
    Serial.println("Input Reset");
  }else if (key >= '0' && key <= '9'){
    if(passwordIndex < 6){
      enteredPassword[passwordIndex++] = key;
    }
  }else if (key == 'D') {
    enteredPassword[passwordIndex] = '\0';
    checkPassword();
    passwordIndex = 0;
  }else if (key == '*'){
    if (vaultOpen){
      vaultCloseTime += 5000;
      Serial.print("Vault time extented by 5 seconds");
    }
  }
}

void checkPassword(){
  if(strcmp(enteredPassword, correctPassword) == 0){
    Serial.println("Correct Password! Vault Open.");
    buzz(1);
    openVault();
  }else{
    Serial.println("Incorrect Password");
    buzz(5);
  }
}

void openVault(){
  vaultOpen = true;
  delay(1000);
  vaultCloseTime = millis() + 20000;
  moveServo(0); 
}

void closeVault(){
  vaultOpen = false;
  moveServo(90);
  Serial.println("Vault Closed.");
}

void moveServo(int angle){
  int pulseWidth = map(angle, 0, 180, 500, 2500);
  for(int i = 0; i < 50; i++){
    digitalWrite(servoPin, HIGH);
    delayMicroseconds(pulseWidth);
    digitalWrite(servoPin, LOW);
    delay(200);
  }
}


void buzz(int times){
  for(int i = 0; i < times; i++){
    digitalWrite(buzzAlarm, HIGH);
    delay(200);
    digitalWrite(buzzAlarm, LOW);
    delay(200);
  }
}