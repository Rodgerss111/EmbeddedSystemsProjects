
#include <LiquidCrystal_I2C.h>

const int led1 = 13;
const int switch1 = A0; 
int switchStatus1 = 0;
int analogValue;


int delay1 = 0;

LiquidCrystal_I2C dis(0x27, 16, 2);

void setup() {

pinMode (led1, OUTPUT);
pinMode (switch1, INPUT);
Serial.begin(9600);
dis.init();
dis.backlight();
dis.clear();
dis.setCursor(0, 0);
dis.print("StandUp Reminder");
dis.setCursor(3, 1);
dis.print("Good Day!");
for (int a = 12; a <= 15; a++) {
    dis.setCursor(a, 1);
    dis.print(".");
    delay(1500);
}
dis.clear();
}



void ledClear() {
    
    digitalWrite(led1, LOW);
   
}


void loop() {

  int buttonValue = analogRead(switch1); 
  int state1 = digitalRead(switch1);
  Serial.print("Analog value: ");
  Serial.println(buttonValue);

   int allButtons = digitalRead(switch1);

  if (buttonValue < 100) {
    allButtons = LOW;

  }else if(buttonValue < 150){
    digitalWrite(led1, HIGH);
    Serial.println("Button 1 Pressed");
    dis.setCursor(1, 0);
    dis.print("B1");
     delay(1000);
     ledClear();

  }else if(buttonValue < 250){
    digitalWrite(led1, HIGH);
    Serial.println("Button 2 Pressed");
    dis.setCursor(1, 0);
    dis.print("B2");
     delay(1000);
     ledClear();
   
 }else if(buttonValue < 350){
    digitalWrite(led1, HIGH);
    Serial.println("Button 3 Pressed");
    dis.setCursor(1, 0);
    dis.print("B3");
     delay(1000);
     ledClear();

  }else if(buttonValue < 850){
    digitalWrite(led1, HIGH);
    Serial.println("Button 4 Pressed");
    dis.setCursor(1, 0);
    dis.print("B4");
     delay(1000);
     ledClear();
   
 }else {
    digitalWrite(led1, HIGH);
    Serial.println("Button 5 Pressed");
    dis.setCursor(1, 0);
    dis.print("B5");
     delay(1000);
     ledClear();
   
  }
  




}



