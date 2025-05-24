

 const int lightLed = 10;


bool motorState = false;


int portIN1 = 4;
int portIN2 = 5;
int portIN3 = 6;
int portIN4 = 7;


void setup() {
  Serial.begin(9600);
  pinMode(lightLed, OUTPUT);
  
for(char r = 0; r < rows; r++){
  pinMode(rowPins[r], INPUT);
  digitalWrite(rowPins[r], HIGH);
}

for(char c = 0; c < cols; c++){
  pinMode(colPins[c], OUTPUT);
  }
pinMode(portIN1, OUTPUT);
pinMode(portIN2, OUTPUT);
pinMode(portIN3, OUTPUT);
pinMode(portIN4, OUTPUT);

}

void loop() {
char key = getKey();
 if(key != 0){
    Serial.println(key);
  }
 
   buttonState = digitalRead(switching);

  if (key == '7') {
 
    if (buttonState == LOW) {
      digitalWrite(lightLed, !digitalRead(lightLed)); 
    }
    delay(50); 
  }

  switching = buttonState; 

  if (key == '4') {
 
    if (buttonState == LOW) {
      digitalWrite(buzzAlarm, !digitalRead(buzzAlarm)); 
    }
    delay(50); 
  }

  if (key == '#') {
 
    resetAll();

  }
    if (key == '1') {
      motorState = !motorState; // Toggle motor state
    }
  
  if(motorState){
 
      stepSequence(1,0,0,0);
      delay(2);
      stepSequence(0,1,0,0);
      delay(2);
      stepSequence(0,0,1,0);
      delay(2);
      stepSequence(0,0,0,1);
      delay(2);
  }else {
    stepSequence(0, 0, 0, 0); // Turn off all coils when motor is off
  }

   if (key == '2') {
      servoState = !servoState; // Toggle motor state
    }

   if(servoState){
    for(int angle = 0; angle <= 180; angle ++){
      int pulseWidth = map(angle, 0, 180, 500, 2500);
      digitalWrite(servoPin, HIGH);
      delayMicroseconds(pulseWidth);
      digitalWrite(servoPin, LOW);
      delay(20 - pulseWidth / 1000);
    }  for(int angle = 180; angle >= 0; angle --){
      int pulseWidth = map(angle, 0, 180, 500, 2500);
      digitalWrite(servoPin, HIGH);
      delayMicroseconds(pulseWidth);
      digitalWrite(servoPin, LOW);
      delay(20 - pulseWidth / 1000);
    }
  }
}

char getKey(){
  char k = 0;
  for(char c = 0; c < cols; c++){
    digitalWrite(colPins[c], LOW);
    for(char r = 0; r < rows; r++){
      if(digitalRead(rowPins[r]) == LOW){
        delay(20);
        while(digitalRead(rowPins[r]) == LOW);
        k = keys[r][c];
      }
    }
    digitalWrite(colPins[c], HIGH);
  }
  return k;
}

void stepSequence(int in1, int in2, int in3, int in4){
  digitalWrite(portIN1, in1);
  digitalWrite(portIN2, in2);
  digitalWrite(portIN3, in3);
  digitalWrite(portIN4, in4);
}

void resetAll(){
  switching = 0;
  buttonState = 0;
  motorState = false;
  servoState = false;
  digitalWrite(lightLed, LOW);
  digitalWrite(buzzAlarm, LOW);
}





