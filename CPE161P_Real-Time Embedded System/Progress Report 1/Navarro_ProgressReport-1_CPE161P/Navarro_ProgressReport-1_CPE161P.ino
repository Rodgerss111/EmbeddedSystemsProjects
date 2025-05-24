#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte rows = 4;
const byte cols = 4;
char keys [rows][cols]{
  {'D','*','0','#'},
  {'C','9','8','7'},
  {'B','6','5','4'},
  {'A','3','2','1'}
};

byte rowPins[rows] = {9, 8, 7, 6};
byte colPins[cols] = {5, 4, 3, 2};

// Servo setuo
const int servoPin1 = 12;
const int servoPin2 = 11;

bool automaticMode = false;

void moveServo(int pin, int angle){
  int dutyCycle = map(angle, 0, 180, 544, 2400);
  for (int i = 0; i < 50; i++){
    digitalWrite(pin, HIGH);
    delayMicroseconds(dutyCycle);
    digitalWrite(pin, LOW);
    delay(10);
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("System Starting");

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" Initializing");
  lcd.setCursor(0,1);
  lcd.print("System in On");

  for (int a = 12; a< 15; a++){
    lcd.setCursor(a, 1);
    lcd.print(".");
    delay(700);
  }
  lcd.clear();

  pinMode(servoPin1, OUTPUT);
  pinMode(servoPin2, OUTPUT);
  
  for (byte i = 0; i < rows; i++){
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }
  for(byte i = 0; i < cols; i++){
    pinMode(colPins[i], INPUT_PULLUP);
  }
  lcd.setCursor(0,0);
  lcd.print("Select Mode: ");
  lcd.setCursor(0,1);
  lcd.print("A:Auto B:Manual");
}

char getKey(){
  for (byte row = 0; row < rows; row++){
    digitalWrite(rowPins[row], LOW);
    for (byte col = 0;col < cols; col++){
      if(digitalRead(colPins[col]) == LOW){
      digitalWrite(rowPins[row], HIGH);
      return keys[row][col];
      }
    }
    digitalWrite(rowPins[row], HIGH);
  }
  return '\0'; // no key pressed
}

void loop() {
  char key = getKey();

  if (key) {
    if(key == 'A'){
      automaticMode = true;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Mode: Automatic");
    }else if (key =='B'){
      automaticMode = false;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Mode: Manual");
    }
  }


  if(automaticMode){
    // automatic mode logic
    moveServo(servoPin1, 180);
    delay(1000);
    moveServo(servoPin1, 90);
    delay(1000);
    moveServo(servoPin2, 140);
    delay(1000);
    moveServo(servoPin2, 90);
    delay(1000);
     moveServo(servoPin2, 30);
    delay(1000);
    moveServo(servoPin1, 0);
    delay(1000);
  

  }else {
    if(key == '1'){
      moveServo(servoPin1, 180);
    }else if (key == '2'){
      moveServo(servoPin1, 90);
    }else if (key == '3'){
      moveServo(servoPin1, 0);
    }else if (key == '4'){
      moveServo(servoPin2, 140);
    }else if (key == '5'){
      moveServo(servoPin2, 90);
    }else if (key == '6'){
      moveServo(servoPin2, 20);
    }
  }

}
