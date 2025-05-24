
const int Green1 = 9;
const int Yellow1 = 8;
const int Red1 = 7;
const int Blue1 = 6;
const int Blue2 = 5;
const int Red2 = 4;
const int Yellow2 = 3;
const int Green2 = 2;
const int button1 = A3;
const int button2 = A2;
const int button3 = A1;
const int resetButton = A0;


int buttonStatus1 = 0;
int buttonStatus2 = 0;
int buttonStatus3 = 0;
int buttonStatusReset = 0;

int delay1 = 0;

void setup() {

pinMode (Green1, OUTPUT);
pinMode (Yellow1, OUTPUT);
pinMode (Red1, OUTPUT);
pinMode (Blue1, OUTPUT);
pinMode (Blue2, OUTPUT);
pinMode (Red2, OUTPUT);
pinMode (Yellow2, OUTPUT);
pinMode (Green2, OUTPUT);

pinMode (button1, INPUT);
pinMode (button2, INPUT);
pinMode (button3, INPUT);
pinMode (resetButton, INPUT);
Serial.begin(9600);

}

void loop() {
  int state1 = digitalRead(button1);
  int state2 = digitalRead(button2);
  int state3 = digitalRead(button3);


 if (state3 == 1 & state2 == 1 & state1 == 1){
    digitalWrite(Green1,HIGH);
    digitalWrite(Yellow1,HIGH);
    digitalWrite(Red1,HIGH);
    digitalWrite(Blue1,HIGH);
    digitalWrite(Blue1, HIGH);
    delay(500);
    digitalWrite(Green1,LOW);
    digitalWrite(Yellow1,LOW);
    digitalWrite(Red1,LOW);
    digitalWrite(Green1,LOW);
    digitalWrite(Blue1,LOW);
    digitalWrite(Blue1,LOW);
    delay(100);
  }

  else if (state2 == 1 & state1 == 1){
 
    digitalWrite(Yellow1,HIGH);
    digitalWrite(Red1,HIGH);
    digitalWrite(Blue1,HIGH);
    digitalWrite(Red1, HIGH);
    ledClear();
  
}

  if (state2 == 1 & state1 == 1){
  
    digitalWrite(Yellow2,HIGH);
    digitalWrite(Green2,HIGH);
    ledClear();
  }

}


void ledClear() {
      digitalWrite(Green1, LOW);
      digitalWrite(Yellow1, LOW);
      digitalWrite(Red1, LOW);
      digitalWrite(Blue1, LOW);
      digitalWrite(Blue2, LOW);
      digitalWrite(Red2, LOW);
      digitalWrite(Yellow2, LOW);
      digitalWrite(Green2, LOW);

}


