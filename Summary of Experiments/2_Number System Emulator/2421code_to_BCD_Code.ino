const int Code1 = 5;
const int Code2 = 4;
const int Code4 = 3;
const int Code8 = 2;

const int BCD1 = 9;
const int BCD2 = 8;
const int BCD4 = 7;
const int BCD8 = 6;

const int switch1 = A0; 
const int switch2 = A1;
const int switch4 = A2; 
const int switch8 = A3; 

int switchStatus1 = 0;
int switchStatus2 = 0;
int switchStatus4 = 0;
int switchStatus8 = 0;

int delay1 = 0;


void setup() {
 
pinMode (Code1, OUTPUT);
pinMode (Code2, OUTPUT);
pinMode (Code4, OUTPUT);
pinMode (Code8, OUTPUT);

pinMode (BCD1, OUTPUT);
pinMode (BCD2, OUTPUT);
pinMode (BCD4, OUTPUT);
pinMode (BCD8, OUTPUT);

pinMode (switch1, INPUT);
pinMode (switch2, INPUT);
pinMode (switch4, INPUT);
pinMode (switch8, INPUT);
Serial.begin(9600);

}


void ledClear() {
    digitalWrite(Code1, LOW);
    digitalWrite(Code2, LOW);
    digitalWrite(Code4, LOW);
    digitalWrite(Code8, LOW);

    digitalWrite(BCD1, LOW);
    digitalWrite(BCD2, LOW);
    digitalWrite(BCD4, LOW);
    digitalWrite(BCD8, LOW);

}

void loop() {

  int state1 = digitalRead(switch1);
  int state2 = digitalRead(switch2);
  int state4 = digitalRead(switch4);
  int state8 = digitalRead(switch8);
  
  //2421 code input
  //0
  if(state8 == 0 & state4 == 0 & state2 == 0 & state1 == 0){
    digitalWrite(Code1, LOW);
    digitalWrite(Code2, LOW);
    digitalWrite(Code4, LOW);
    digitalWrite(Code8, LOW);
    ledClear();
//1
  }else if (state8 == 0 & state4 == 0 & state2 == 0 & state1 == 1){
    digitalWrite(Code1, HIGH);
    digitalWrite(Code2, LOW);
    digitalWrite(Code4, LOW);
    digitalWrite(Code8, LOW);
    ledClear();
//2
  }else if (state8 == 0 & state4 == 0 & state2 == 1 & state1 == 0){
    digitalWrite(Code1, LOW);
    digitalWrite(Code2, HIGH);
    digitalWrite(Code4, LOW);
    digitalWrite(Code8, LOW);
    ledClear();
//3
  }else if (state8 == 0 & state4 == 0 & state2 == 1 & state1 == 1){
    digitalWrite(Code1, HIGH);
    digitalWrite(Code2, HIGH);
    digitalWrite(Code4, LOW);
    digitalWrite(Code8, LOW);
    ledClear();
//4
  }else if (state8 == 0 & state4 == 1 & state2 == 0 & state1 == 0){
    digitalWrite(Code1, LOW);
    digitalWrite(Code2, LOW);
    digitalWrite(Code4, HIGH);
    digitalWrite(Code8, LOW);
    ledClear();
//5
  }else if (state8 == 1 & state4 == 0 & state2 == 1 & state1 == 1){
    digitalWrite(Code1, HIGH);
    digitalWrite(Code2, HIGH);
    digitalWrite(Code4, LOW);
    digitalWrite(Code8, HIGH);
    ledClear();
//6
  }else if (state8 == 1 & state4 == 1 & state2 == 0 & state1 == 0){
    digitalWrite(Code1, LOW);
    digitalWrite(Code2, LOW);
    digitalWrite(Code4, HIGH);
    digitalWrite(Code8, HIGH);
    ledClear();
//7
  }else if (state8 == 1 & state4 == 1 & state2 == 0 & state1 == 1){
    digitalWrite(Code1, HIGH);
    digitalWrite(Code2, LOW);
    digitalWrite(Code4, HIGH);
    digitalWrite(Code8, HIGH);
    ledClear();
//8
  }else if (state8 == 1 & state4 == 1 & state2 == 1 & state1 == 0){
    digitalWrite(Code1, LOW);
    digitalWrite(Code2, HIGH);
    digitalWrite(Code4, HIGH);
    digitalWrite(Code8, HIGH);
    ledClear();
//9
  }else if (state8 == 1 & state4 == 1 & state2 == 1 & state1 == 1){
    digitalWrite(Code1, HIGH);
    digitalWrite(Code2, HIGH);
    digitalWrite(Code4, HIGH);
    digitalWrite(Code8, HIGH);
    ledClear();
  }


  //BCD output
  //0
  if(state8 == 0 & state4 == 0 & state2 == 0 & state1 == 0){
    digitalWrite(BCD1, LOW);
    digitalWrite(BCD2, LOW);
    digitalWrite(BCD4, LOW);
    digitalWrite(BCD8, LOW);
    ledClear();
//1
  }else if (state8 == 0 & state4 == 0 & state2 == 0 & state1 == 1){
    digitalWrite(BCD1, HIGH);
    digitalWrite(BCD2, LOW);
    digitalWrite(BCD4, LOW);
    digitalWrite(BCD8, LOW);
    ledClear();
//2
  }else if (state8 == 0 & state4 == 0 & state2 == 1 & state1 == 0){
    digitalWrite(BCD1, LOW);
    digitalWrite(BCD2, HIGH);
    digitalWrite(BCD4, LOW);
    digitalWrite(BCD8, LOW);
    ledClear();
//3
  }else if (state8 == 0 & state4 == 0 & state2 == 1 & state1 == 1){
    digitalWrite(BCD1, HIGH);
    digitalWrite(BCD2, HIGH);
    digitalWrite(BCD4, LOW);
    digitalWrite(BCD8, LOW);
    ledClear();
//4
  }else if (state8 == 0 & state4 == 1 & state2 == 0 & state1 == 0){
    digitalWrite(BCD1, LOW);
    digitalWrite(BCD2, LOW);
    digitalWrite(BCD4, HIGH);
    digitalWrite(BCD8, LOW);
    ledClear();
//5
  }else if (state8 == 1 & state4 == 0 & state2 == 1 & state1 == 1){
    digitalWrite(BCD1, HIGH);
    digitalWrite(BCD2, LOW);
    digitalWrite(BCD4, HIGH);
    digitalWrite(BCD8, LOW);
    ledClear();
//6
  }else if (state8 == 1 & state4 == 1 & state2 == 0 & state1 == 0){
    digitalWrite(BCD1, LOW);
    digitalWrite(BCD2, HIGH);
    digitalWrite(BCD4, HIGH);
    digitalWrite(BCD8, LOW);
    ledClear();
//7
  }else if (state8 == 1 & state4 == 1 & state2 == 0 & state1 == 1){
    digitalWrite(BCD1, HIGH);
    digitalWrite(BCD2, HIGH);
    digitalWrite(BCD4, HIGH);
    digitalWrite(BCD8, LOW);
    ledClear();
//8
  }else if (state8 == 1 & state4 == 1 & state2 == 1 & state1 == 0){
    digitalWrite(BCD1, LOW);
    digitalWrite(BCD2, LOW);
    digitalWrite(BCD4, LOW);
    digitalWrite(BCD8, HIGH);
    ledClear();
//9
  }else if (state8 == 1 & state4 == 1 & state2 == 1 & state1 == 1){
    digitalWrite(BCD1, HIGH);
    digitalWrite(BCD2, LOW);
    digitalWrite(BCD4, LOW);
    digitalWrite(BCD8, HIGH);
    ledClear();
  }

 

}
