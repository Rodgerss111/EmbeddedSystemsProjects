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
 if (digitalRead(button1)==HIGH){
  buttonStatus1 = HIGH;
  buttonStatus2 = LOW;
  buttonStatus3 = LOW; 
  buttonStatusReset = LOW;
 }else if (digitalRead(button2)==HIGH){
  buttonStatus1 = LOW;
  buttonStatus2 = HIGH;
  buttonStatus3 = LOW;
  buttonStatusReset = LOW; 
 }else if (digitalRead(button3)==HIGH){
  buttonStatus1 = LOW;
  buttonStatus2 = LOW;
  buttonStatus3 = HIGH;
  buttonStatusReset = LOW; 
 }else if (digitalRead(resetButton)==HIGH){
  buttonStatus1 = LOW;
  buttonStatus2 = LOW;
  buttonStatus3 = LOW; 
  buttonStatusReset = HIGH;
 }

  if (buttonStatus1 == HIGH){
    ledClear();
    Song_Button1();
  } else if (buttonStatus2 == HIGH){
    Song_Button2();
  } else if (buttonStatus3 == HIGH){
    Song_Button3();
  } else if (buttonStatusReset == HIGH){
    buttonStatus1 == LOW;
    buttonStatus2 == LOW;
    buttonStatus3 == LOW;
    
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

void highLed() {
    digitalWrite(Green1, HIGH);
    digitalWrite(Yellow1, HIGH);
    digitalWrite(Red1, HIGH);
    digitalWrite(Blue1, HIGH);
    digitalWrite(Blue2, HIGH);
    digitalWrite(Red2, HIGH);
    digitalWrite(Yellow2, HIGH);
    digitalWrite(Green2, HIGH);

}

void Song_Button1() {
  
  delay1 = 1200;

  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  delay(delay1);
  ledClear();

  delay(240);
  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  delay(delay1);
  ledClear();

  
  delay(250);
  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Blue1, HIGH);
  digitalWrite(Blue2, HIGH);
  delay(delay1);
  ledClear();

  delay(250);
  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  delay(delay1);
  ledClear();

  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  delay(100);
  ledClear();
  
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  delay(200);
  ledClear();

  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  delay(1000);
  ledClear();

 //2nd part

  delay(300);
  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  delay(delay1);
  ledClear();
 
  delay(300);
  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  delay(600);
  ledClear();

  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  delay(400);
  ledClear();

  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  delay(400);
  ledClear();

  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  delay(delay1);
  ledClear();
 
  //1 
  delay(295);
  digitalWrite(Blue1, HIGH);
  digitalWrite(Blue2, HIGH);
  delay(1100);
  ledClear();

  delay(300);
  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  delay(delay1);
  ledClear();

  //2

  delay(300);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  delay(1100);
  ledClear();

  delay(300);
  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  delay(delay1);
  ledClear();

  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  delay(170);
  ledClear();
  
  digitalWrite(Blue1, HIGH);
  digitalWrite(Blue2, HIGH);
  delay(195);
  ledClear();


  //3

  delay(300);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  delay(1100);
  ledClear();

  delay(300);
  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);

  delay(delay1);
  ledClear();

  //4

  delay(300);
  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  delay(1100);
  ledClear();

  delay(300);
  digitalWrite(Blue1, HIGH);
  digitalWrite(Blue2, HIGH);
  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  delay(delay1);
  ledClear();

  //5

  delay(340);
  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  delay(1100);
  ledClear();

  delay(350);
  digitalWrite(Blue1, HIGH);
  digitalWrite(Blue2, HIGH);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  delay(delay1);
  ledClear();

  //6

  delay(350);
  digitalWrite(Green2, HIGH);
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Red2, HIGH);
  delay(1100);
  ledClear();

  delay(350);
  digitalWrite(Green1, HIGH);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Red1, HIGH);
  delay(delay1);
  ledClear();

  //7

  delay(350);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  delay(1100);
  ledClear();

  delay(350);
  digitalWrite(Blue1, HIGH);
  digitalWrite(Blue2, HIGH);
  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  delay(delay1);
  ledClear();
 
  //8

  delay(350);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  delay(1000);
  ledClear();

  delay(350);
  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  delay(delay1);
  ledClear();

  //9

  delay(350);
  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Blue1, HIGH);
  digitalWrite(Blue2, HIGH);
  delay(1000);
  ledClear();

  delay(350);
  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  delay(delay1);
  ledClear();

  //10

  delay(350);
  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  digitalWrite(Blue1, HIGH);
  digitalWrite(Blue2, HIGH);
  delay(1000);
  ledClear();

  delay(350);
  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  delay(delay1);
  ledClear();

  //11

  delay(107);
  
  digitalWrite(Blue2, HIGH);
  digitalWrite(Red2, HIGH);
  delay(445);
  ledClear();
  
  delay(50);
  digitalWrite(Blue1, HIGH);
  digitalWrite(Red1, HIGH);
  delay(445);
  ledClear();

  delay(50);
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Red2, HIGH);
  delay(445);
  ledClear();

  delay(50);

  digitalWrite(Yellow1, HIGH);
  digitalWrite(Red1, HIGH);
  delay(445);
  ledClear();
  
  delay(50);
  digitalWrite(Green2, HIGH);
  digitalWrite(Yellow2, HIGH);
  delay(445);
  ledClear();

  delay(50);
  digitalWrite(Green1, HIGH);
  digitalWrite(Yellow1, HIGH);
  delay(445);
  ledClear();

  delay(50);
  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  delay(445);
  ledClear();

 //final

  delay(50);
  digitalWrite(Blue1, HIGH);
  digitalWrite(Blue2, HIGH);
  delay(440);
  ledClear();

   delay(50);
  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  delay(490);
  ledClear();

  delay(50);
  digitalWrite(Blue1, HIGH);
  digitalWrite(Blue2, HIGH);
  delay(440);
  ledClear();

  delay(50);
  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  delay(490);
  ledClear();

  delay(50);
  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  delay(250);
  ledClear();

  delay(50);
  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Blue1, HIGH);
  digitalWrite(Blue2, HIGH);
  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  delay(10000);
  ledClear();

}

void Song_Button2(){


  digitalWrite(Yellow2, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Red2, HIGH);
  delay(300);
  ledClear();

  digitalWrite(Yellow1, HIGH);
  digitalWrite(Green1, HIGH);
  digitalWrite(Red1, HIGH);
  delay(295);
  ledClear();

  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  delay(230);
  ledClear();

  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  delay(215);
  ledClear();

  digitalWrite(Blue1, HIGH);
  digitalWrite(Blue2, HIGH);
  delay(300);
  ledClear();

  //start

  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  delay(700);
  ledClear();

  digitalWrite(Blue1, HIGH);
  digitalWrite(Blue2, HIGH);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  delay(700);
  ledClear();

  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  delay(350);
  ledClear();

  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  delay(310);
  ledClear();

  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  delay(350);
  ledClear();

  digitalWrite(Blue1, HIGH);
  digitalWrite(Blue2, HIGH);
  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  delay(1000);
  ledClear();

  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  delay(270);
  ledClear();

  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  digitalWrite(Blue1, HIGH);
  digitalWrite(Blue2, HIGH);
  delay(240);
  ledClear();

  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  delay(270);
  ledClear();

  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  delay(240);
  ledClear();

  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  delay(370);
  ledClear();


  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  delay(320);
  ledClear();


  digitalWrite(Blue1, HIGH);
  digitalWrite(Blue2, HIGH);
  delay(340);
  ledClear();

  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  delay(2500);
  ledClear();

  //break

  digitalWrite(Blue1, HIGH);
  digitalWrite(Blue2, HIGH);
  delay(2640);
  ledClear();

  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  delay(480);
  ledClear();

  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  delay(1100);
  ledClear();

  digitalWrite(Green2, HIGH);
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Red2, HIGH);
  delay(330);
  ledClear();

  digitalWrite(Blue1, HIGH);
  digitalWrite(Blue2, HIGH);
  delay(300);
  ledClear();

  digitalWrite(Green1, HIGH);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Red1, HIGH);
  delay(2950);
  ledClear();

  //Final

  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  delay(400);
  ledClear();

  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  delay(350);
  ledClear();

  digitalWrite(Red1, HIGH);
  digitalWrite(Red2, HIGH);
  delay(300);
  ledClear();

  digitalWrite(Green1, HIGH);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Yellow2, HIGH);
  delay(350);
  ledClear();

  digitalWrite(Blue1, HIGH);
  digitalWrite(Blue2, HIGH);
  digitalWrite(Red2, HIGH);
  digitalWrite(Red1, HIGH);
  delay(300);
  ledClear();

  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Yellow2, HIGH);
  delay(395.5);
  ledClear();

  digitalWrite(Blue1, HIGH);
  digitalWrite(Blue2, HIGH);
  digitalWrite(Red2, HIGH);
  digitalWrite(Red1, HIGH);
  delay(3000);
  ledClear();

  digitalWrite(Yellow2, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Red2, HIGH);
  delay(300);
  ledClear();

  digitalWrite(Yellow1, HIGH);
  digitalWrite(Green1, HIGH);
  digitalWrite(Red1, HIGH);
  delay(4000);
  ledClear();

}

void Song_Button3(){
 
  digitalWrite(Blue1, HIGH);
  digitalWrite(Blue2, HIGH);
  delay(1000);
  ledClear();

  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Red2, HIGH);
  digitalWrite(Red1, HIGH);
  delay(1035);
  ledClear();

  delay(200);
  digitalWrite(Blue1, HIGH);
  digitalWrite(Blue2, HIGH);
  digitalWrite(Red2, HIGH);
  digitalWrite(Red1, HIGH);
  delay(600);
  ledClear();

  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  delay(750);
  ledClear();

  digitalWrite(Blue1, HIGH);
  digitalWrite(Blue2, HIGH);
  digitalWrite(Red2, HIGH);
  digitalWrite(Red1, HIGH);
  delay(200);
  ledClear();

  digitalWrite(Yellow1, HIGH);
  digitalWrite(Green1, HIGH);
  digitalWrite(Red1, HIGH);
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Red2, HIGH);
  delay(1100);
  ledClear();

  //2

  delay(100);
  digitalWrite(Blue1, HIGH);
  digitalWrite(Blue2, HIGH);
  delay(1100);
  ledClear();
  
  delay(200);
  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  delay(900);
  ledClear();


  digitalWrite(Blue1, HIGH);
  digitalWrite(Blue2, HIGH);
  digitalWrite(Red2, HIGH);
  digitalWrite(Red1, HIGH);
  delay(600);
  ledClear();

  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  delay(300);
  ledClear();

  digitalWrite(Yellow1, HIGH);
  digitalWrite(Green1, HIGH);
  digitalWrite(Red1, HIGH);
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Red2, HIGH);
  delay(1000);
  ledClear();

  //3rd
  delay(100);
  digitalWrite(Blue1, HIGH);
  digitalWrite(Blue2, HIGH);
  delay(1200);
  ledClear();

  digitalWrite(Green1, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Red2, HIGH);
  digitalWrite(Red1, HIGH);
  delay(1690);
  ledClear();

  digitalWrite(Blue1, HIGH);
  digitalWrite(Blue2, HIGH);
  delay(200);
  ledClear();

  digitalWrite(Yellow1, HIGH);
  digitalWrite(Green1, HIGH);
  digitalWrite(Red1, HIGH);
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Red2, HIGH);
 


}






