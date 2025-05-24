int switch1 = A0;
int switch2 = A1;
int switch4 = A2;
int switch8 = A3;

int a = 3;
int b = 2;
int c = 4;
int d = 5;
int e = 6;
int f = 7;
int g = 8;

const int Excess1 = 9;
const int Excess2 = 10;
const int Excess4 = 11;
const int Excess8 = 12;


void setup() {
  
pinMode (Excess1, OUTPUT);
pinMode (Excess2, OUTPUT);
pinMode (Excess4, OUTPUT);
pinMode (Excess8, OUTPUT);

pinMode (a, OUTPUT);
pinMode (b, OUTPUT);
pinMode (c, OUTPUT);
pinMode (d, OUTPUT);
pinMode (e, OUTPUT);
pinMode (f, OUTPUT);
pinMode (g, OUTPUT);

pinMode (switch1, INPUT);
pinMode (switch2, INPUT);
pinMode (switch4, INPUT);
pinMode (switch8, INPUT);
Serial.begin(9600);

}


void ledClear() {
    digitalWrite(Excess1, LOW);
    digitalWrite(Excess2, LOW);
    digitalWrite(Excess4, LOW);
    digitalWrite(Excess8, LOW);
  
}

void loop() {
  int state1 = digitalRead(switch1);
  int state2 = digitalRead(switch2);
  int state3 = digitalRead(switch4);
  int state4 = digitalRead(switch8);
  Serial.println(state1);
  Serial.println(state2);
  Serial.println(state3);
  Serial.println(state4);
//0
if(state4 == HIGH & state2 ==HIGH & state1 == HIGH){
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
//1
}else if(state3 ==HIGH & state2 == HIGH & state1 == HIGH){
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
//2
}else if(state4 ==HIGH & state3 == HIGH){
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
//3
}else if(state4 ==HIGH & state2 == HIGH){
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
//4
}else if(state4 ==HIGH & state1 == HIGH){
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
//5
}else if(state3 ==HIGH & state2 == HIGH){
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
//6
}else if(state3 ==HIGH & state1 == HIGH){
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
//7
}else if(state2 == HIGH & state1 == HIGH){
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
//8
}else if(state3 ==HIGH){
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
//9
}else if(state4 ==HIGH){
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
//10
}else {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

//excess 3 output
//0
  if(state4 == 0 & state3 == 0 & state2 == 0 & state1 == 0){
    digitalWrite(Excess1, LOW);
    digitalWrite(Excess2, LOW);
    digitalWrite(Excess4, LOW);
    digitalWrite(Excess8, LOW);
    ledClear();
//1
  }else if (state4 == 0 & state3 == 0 & state2 == 0 & state1 == 1){
    digitalWrite(Excess1, HIGH);
    digitalWrite(Excess2, LOW);
    digitalWrite(Excess4, LOW);
    digitalWrite(Excess8, LOW);
    ledClear();
//2
  }else if (state4 == 0 & state3 == 0 & state2 == 1 & state1 == 0){
    digitalWrite(Excess1, LOW);
    digitalWrite(Excess2, HIGH);
    digitalWrite(Excess4, LOW);
    digitalWrite(Excess8, LOW);
    ledClear();
//3
  }else if (state4 == 0 & state3 == 0 & state2 == 1 & state1 == 1){
    digitalWrite(Excess1, HIGH);
    digitalWrite(Excess2, HIGH);
    digitalWrite(Excess4, LOW);
    digitalWrite(Excess8, LOW);
    ledClear();
//4
  }else if (state4 == 0 & state3 == 1 & state2 == 0 & state1 == 0){
    digitalWrite(Excess1, LOW);
    digitalWrite(Excess2, LOW);
    digitalWrite(Excess4, HIGH);
    digitalWrite(Excess8, LOW);
    ledClear();
//5
  }else if (state4 == 0 & state3 == 1 & state2 == 0 & state1 == 1){
    digitalWrite(Excess1, HIGH);
    digitalWrite(Excess2, LOW);
    digitalWrite(Excess4, HIGH);
    digitalWrite(Excess8, LOW);
    ledClear();
//6
  }else if (state4 == 0 & state3 == 1 & state2 == 1 & state1 == 0){
    digitalWrite(Excess1, LOW);
    digitalWrite(Excess2, HIGH);
    digitalWrite(Excess4, HIGH);
    digitalWrite(Excess8, LOW);
    ledClear();
//7
  }else if (state4 == 0 & state3 == 1 & state2 == 1 & state1 == 1){
    digitalWrite(Excess1, HIGH);
    digitalWrite(Excess2, HIGH);
    digitalWrite(Excess4, HIGH);
    digitalWrite(Excess8, LOW);
    ledClear();
//8
  }else if (state4 == 1 & state3 == 0 & state2 == 0 & state1 == 0){
    digitalWrite(Excess1, LOW);
    digitalWrite(Excess2, LOW);
    digitalWrite(Excess4, LOW);
    digitalWrite(Excess8, HIGH);
    ledClear();
//9
  }else if (state4 == 1 & state3 == 0 & state2 == 0 & state1 == 1){
    digitalWrite(Excess1, HIGH);
    digitalWrite(Excess2, LOW);
    digitalWrite(Excess4, LOW);
    digitalWrite(Excess8, HIGH);
    ledClear();
  }

}
