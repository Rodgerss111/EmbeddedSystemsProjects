
const int Binary1 = 5;
const int Binary2 = 4;
const int Binary4 = 3;
const int Binary8 = 2;

const int Complement1 = 9;
const int Complement2 = 8;
const int Complement4 = 7;
const int Complement8 = 6;

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
 
pinMode (Binary1, OUTPUT);
pinMode (Binary2, OUTPUT);
pinMode (Binary4, OUTPUT);
pinMode (Binary8, OUTPUT);

pinMode (Complement1, OUTPUT);
pinMode (Complement2, OUTPUT);
pinMode (Complement4, OUTPUT);
pinMode (Complement8, OUTPUT);

pinMode (switch1, INPUT);
pinMode (switch2, INPUT);
pinMode (switch4, INPUT);
pinMode (switch8, INPUT);
Serial.begin(9600);


}

void ledClear() {
    digitalWrite(Binary1, LOW);
    digitalWrite(Binary2, LOW);
    digitalWrite(Binary4, LOW);
    digitalWrite(Binary8, LOW);

    digitalWrite(Complement1, LOW);
    digitalWrite(Complement2, LOW);
    digitalWrite(Complement4, LOW);
    digitalWrite(Complement8, LOW);
   

}

void loop() {
  
  int state1 = digitalRead(switch1);
  int state2 = digitalRead(switch2);
  int state4 = digitalRead(switch4);
  int state8 = digitalRead(switch8);
// Binary Input
//0
  if(state8 == 0 & state4 == 0 & state2 == 0 & state1 == 0){
    digitalWrite(Binary1, LOW);
    digitalWrite(Binary2, LOW);
    digitalWrite(Binary4, LOW);
    digitalWrite(Binary8, LOW);
    ledClear();
//1
  }else if (state8 == 0 & state4 == 0 & state2 == 0 & state1 == 1){
    digitalWrite(Binary1, HIGH);
    digitalWrite(Binary2, LOW);
    digitalWrite(Binary4, LOW);
    digitalWrite(Binary8, LOW);
    ledClear();
//2
  }else if (state8 == 0 & state4 == 0 & state2 == 1 & state1 == 0){
    digitalWrite(Binary1, LOW);
    digitalWrite(Binary2, HIGH);
    digitalWrite(Binary4, LOW);
    digitalWrite(Binary8, LOW);
    ledClear();
//3
  }else if (state8 == 0 & state4 == 0 & state2 == 1 & state1 == 1){
    digitalWrite(Binary1, HIGH);
    digitalWrite(Binary2, HIGH);
    digitalWrite(Binary4, LOW);
    digitalWrite(Binary8, LOW);
    ledClear();
//4
  }else if (state8 == 0 & state4 == 1 & state2 == 0 & state1 == 0){
    digitalWrite(Binary1, LOW);
    digitalWrite(Binary2, LOW);
    digitalWrite(Binary4, HIGH);
    digitalWrite(Binary8, LOW);
    ledClear();
//5
  }else if (state8 == 0 & state4 == 1 & state2 == 0 & state1 == 1){
    digitalWrite(Binary1, HIGH);
    digitalWrite(Binary2, LOW);
    digitalWrite(Binary4, HIGH);
    digitalWrite(Binary8, LOW);
    ledClear();
//6
  }else if (state8 == 0 & state4 == 1 & state2 == 1 & state1 == 0){
    digitalWrite(Binary1, LOW);
    digitalWrite(Binary2, HIGH);
    digitalWrite(Binary4, HIGH);
    digitalWrite(Binary8, LOW);
    ledClear();
//7
  }else if (state8 == 0 & state4 == 1 & state2 == 1 & state1 == 1){
    digitalWrite(Binary1, HIGH);
    digitalWrite(Binary2, HIGH);
    digitalWrite(Binary4, HIGH);
    digitalWrite(Binary8, LOW);
    ledClear();
//8
  }else if (state8 == 1 & state4 == 0 & state2 == 0 & state1 == 0){
    digitalWrite(Binary1, LOW);
    digitalWrite(Binary2, LOW);
    digitalWrite(Binary4, LOW);
    digitalWrite(Binary8, HIGH);
    ledClear();
//9
  }else if (state8 == 1 & state4 == 0 & state2 == 0 & state1 == 1){
    digitalWrite(Binary1, HIGH);
    digitalWrite(Binary2, LOW);
    digitalWrite(Binary4, LOW);
    digitalWrite(Binary8, HIGH);
    ledClear();
//10
  }else if (state8 == 1 & state4 == 0 & state2 == 1 & state1 == 0){
    digitalWrite(Binary1, LOW);
    digitalWrite(Binary2, HIGH);
    digitalWrite(Binary4, LOW);
    digitalWrite(Binary8, HIGH);
    ledClear();
//11
  }else if (state8 == 1 & state4 == 0 & state2 == 1 & state1 == 1){
    digitalWrite(Binary1, HIGH);
    digitalWrite(Binary2, HIGH);
    digitalWrite(Binary4, LOW);
    digitalWrite(Binary8, HIGH);
    ledClear();
//12
  }else if (state8 == 1 & state4 == 1 & state2 == 0 & state1 == 0){
    digitalWrite(Binary1, LOW);
    digitalWrite(Binary2, LOW);
    digitalWrite(Binary4, HIGH);
    digitalWrite(Binary8, HIGH);
    ledClear();
//13
  }else if (state8 == 1 & state4 == 1 & state2 == 0 & state1 == 1){
    digitalWrite(Binary1, HIGH);
    digitalWrite(Binary2, LOW);
    digitalWrite(Binary4, HIGH);
    digitalWrite(Binary8, HIGH);
    ledClear();
//14
  }else if (state8 == 1 & state4 == 1 & state2 == 1 & state1 == 0){
    digitalWrite(Binary1, LOW);
    digitalWrite(Binary2, HIGH);
    digitalWrite(Binary4, HIGH);
    digitalWrite(Binary8, HIGH);
    ledClear();
//15
  }else if (state8 == 1 & state4 == 1 & state2 == 1 & state1 == 1){
    digitalWrite(Binary1, HIGH);
    digitalWrite(Binary2, HIGH);
    digitalWrite(Binary4, HIGH);
    digitalWrite(Binary8, HIGH);
    ledClear();

  }
  //2's Complement Output
  //0
  if(state8 == 0 & state4 == 0 & state2 == 0 & state1 == 0){
    digitalWrite(Complement1, LOW);
    digitalWrite(Complement2, LOW);
    digitalWrite(Complement4, LOW);
    digitalWrite(Complement8, LOW);
    ledClear();
//1
  }else if(state8 == 0 & state4 == 0 & state2 == 0 & state1 == 1){
    digitalWrite(Complement1, HIGH);
    digitalWrite(Complement2, HIGH);
    digitalWrite(Complement4, HIGH);
    digitalWrite(Complement8, HIGH);
    ledClear();
//2
  }else if(state8 == 0 & state4 == 0 & state2 == 1 & state1 == 0){
    digitalWrite(Complement1, LOW);
    digitalWrite(Complement2, HIGH);
    digitalWrite(Complement4, HIGH);
    digitalWrite(Complement8, HIGH);
    ledClear();
//3
  }else if(state8 == 0 & state4 == 0 & state2 == 1 & state1 == 1){
    digitalWrite(Complement1, HIGH);
    digitalWrite(Complement2, LOW);
    digitalWrite(Complement4, HIGH);
    digitalWrite(Complement8, HIGH);
    ledClear();
//4
  }else if(state8 == 0 & state4 == 1 & state2 == 0 & state1 == 0){
    digitalWrite(Complement1, LOW);
    digitalWrite(Complement2, LOW);
    digitalWrite(Complement4, HIGH);
    digitalWrite(Complement8, HIGH);
    ledClear();
   //5
  }else if(state8 == 0 & state4 == 1 & state2 == 0 & state1 == 1){
    digitalWrite(Complement1, HIGH);
    digitalWrite(Complement2, HIGH);
    digitalWrite(Complement4, LOW);
    digitalWrite(Complement8, HIGH);
    ledClear();
   //6
  }else if(state8 == 0 & state4 == 1 & state2 == 1 & state1 == 0){
    digitalWrite(Complement1, LOW);
    digitalWrite(Complement2, HIGH);
    digitalWrite(Complement4, LOW);
    digitalWrite(Complement8, HIGH);
    ledClear();
   //7
  }else if(state8 == 0 & state4 == 1 & state2 == 1 & state1 == 1){
    digitalWrite(Complement1, HIGH);
    digitalWrite(Complement2, LOW);
    digitalWrite(Complement4, LOW);
    digitalWrite(Complement8, HIGH);
    ledClear();
   //8
  }else if(state8 == 1 & state4 == 0 & state2 == 0 & state1 == 0){
    digitalWrite(Complement1, LOW);
    digitalWrite(Complement2, LOW);
    digitalWrite(Complement4, LOW);
    digitalWrite(Complement8, HIGH);
    ledClear();
   //9
  }else if(state8 == 1 & state4 == 0 & state2 == 0 & state1 == 1){
    digitalWrite(Complement1, HIGH);
    digitalWrite(Complement2, HIGH);
    digitalWrite(Complement4, HIGH);
    digitalWrite(Complement8, LOW);
    ledClear();
   //10
  }else if(state8 == 1 & state4 == 0 & state2 == 1 & state1 == 0){
    digitalWrite(Complement1, LOW);
    digitalWrite(Complement2, HIGH);
    digitalWrite(Complement4, HIGH);
    digitalWrite(Complement8, LOW);
    ledClear();
   //11
  }else if(state8 == 1 & state4 == 0 & state2 == 1 & state1 == 1){
    digitalWrite(Complement1, HIGH);
    digitalWrite(Complement2, LOW);
    digitalWrite(Complement4, HIGH);
    digitalWrite(Complement8, LOW);
    ledClear();
   //12
  }else if(state8 == 1 & state4 == 1 & state2 == 0 & state1 == 0){
    digitalWrite(Complement1, LOW);
    digitalWrite(Complement2, LOW);
    digitalWrite(Complement4, HIGH);
    digitalWrite(Complement8, LOW);
    ledClear();
   //13
  }else if(state8 == 1 & state4 == 1 & state2 == 0 & state1 == 1){
    digitalWrite(Complement1, HIGH);
    digitalWrite(Complement2, HIGH);
    digitalWrite(Complement4, LOW);
    digitalWrite(Complement8, LOW);
    ledClear();
   //14
  }else if(state8 == 1 & state4 == 1 & state2 == 1 & state1 == 0){
    digitalWrite(Complement1, LOW);
    digitalWrite(Complement2, HIGH);
    digitalWrite(Complement4, LOW);
    digitalWrite(Complement8, LOW);
    ledClear();
   //15
  }else if(state8 == 1 & state4 == 1 & state2 == 1 & state1 == 1){
    digitalWrite(Complement1, HIGH);
    digitalWrite(Complement2, LOW);
    digitalWrite(Complement4, LOW);
    digitalWrite(Complement8, LOW);
    ledClear();

  }
  






}



