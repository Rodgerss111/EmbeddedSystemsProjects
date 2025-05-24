#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define S0 A3
#define S1 A2
#define S2 A1
#define S3 A0
#define sensorOut 10

int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;
int MIN_VALUE = 50;
int MAX_VALUE = 200;
int rc = 0;
int gc = 0;
int bc = 0;
int ic = 0;

const byte rows = 4;
const byte cols = 4;
char keys[rows][cols] = {
  {'D', '*', '0', '#'},
  {'C', '9', '8', '7'},
  {'B', '6', '5', '4'},
  {'A', '3', '2', '1'}
};

byte rowPins[rows] = {6,7,8,9};
byte colPins[cols] = {2,3,4,5};

// Servo setup
const int servoPin1 = 12;
const int servoPin2 = 11;

bool automaticMode = false;
bool modeSelected = false; // ensure the mode is selected before showing colors

void moveServo(int pin, int angle) {
  int dutyCycle = map(angle, 0, 180, 544, 2400);
  for (int i = 0; i < 50; i++) {
    digitalWrite(pin, HIGH);
    delayMicroseconds(dutyCycle);
    digitalWrite(pin, LOW);
    delay(10);
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("System Starting");

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // setting frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Initializing");
  lcd.setCursor(0, 1);
  lcd.print("System On");

  for (int a = 12; a < 15; a++) {
    lcd.setCursor(a, 1);
    lcd.print(".");
    delay(700);
  }
  lcd.clear();

  pinMode(servoPin1, OUTPUT);
  pinMode(servoPin2, OUTPUT);

  for (byte i = 0; i < rows; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }
  for (byte i = 0; i < cols; i++) {
    pinMode(colPins[i], INPUT_PULLUP);
  }

  lcd.setCursor(0, 0);
  lcd.print("Select Mode: ");
  lcd.setCursor(0, 1);
  lcd.print("A:Auto B:Manual");
}

char getKey() {
  for (byte row = 0; row < rows; row++) {
    digitalWrite(rowPins[row], LOW);
    for (byte col = 0; col < cols; col++) {
      if (digitalRead(colPins[col]) == LOW) {
        digitalWrite(rowPins[row], HIGH);
        return keys[row][col];
      }
    }
    digitalWrite(rowPins[row], HIGH);
  }
  return '\0'; // no key pressed
}

void displayColor(int r, int g, int b, char key) {
  
  if (!modeSelected) return; // ensure mode is selected before displaying color

  if ((r > MAX_VALUE && g > MAX_VALUE && b > MAX_VALUE) || (r < MIN_VALUE && g < MIN_VALUE && b < MIN_VALUE)) {
    lcd.setCursor(0, 0);
    lcd.print("Color Not Found");
    Serial.println("Color Not Found");

  } else {
    lcd.setCursor(0, 0);
    if (r < g && r < b) {
      lcd.print("Color: Red     ");
      Serial.println("Color: Red ");
      if(automaticMode){
        ic++;
       if (servoPin1, 90 && ic >= 2) {
            rc = rc + 1;
            lcd.setCursor(0, 1);
            lcd.print("R:");
            lcd.print(rc);
       }
      
      moveServo(servoPin2, 140);
      delay(1000);
      moveServo(servoPin1, 0);
      delay(1000);
      }
    } else if (g < r && g < b) {
      lcd.print("Color: Green     ");
      Serial.println("Color: Green");
      if(automaticMode){
      ic++;
       if (servoPin1, 90 && ic >= 2) {
            gc = gc + 1;
            lcd.setCursor(6, 1);
            lcd.print("G:");
            lcd.print(gc);
       }
      
      moveServo(servoPin2, 90);
      delay(1000);
      moveServo(servoPin1, 0);
      delay(1000);
      }
    } else if (b < r && b < g) {
      lcd.print("Color: Blue     ");
      Serial.println("Color: Blue");
      if(automaticMode){
        ic++;
       if (servoPin1, 90 && ic >= 2)  {
            bc = bc + 1;
            lcd.setCursor(12, 1);
            lcd.print("B:");
            lcd.print(bc);
       }
     
      moveServo(servoPin2, 45);
      delay(1000);
      moveServo(servoPin1, 0);
      delay(1000);
      }
    } else {
      lcd.print("Color: Mixed       ");
      Serial.println("Mixed Color");
    }
  }

  if (automaticMode) {
    // automatic mode logic
    moveServo(servoPin1, 180);
    delay(1000);

     // enable color detection only at 90 degrees
    moveServo(servoPin1, 90);
    delay(500);
  } else {
    // Manual mode
    if (key == '1') {
      moveServo(servoPin1, 180);
    } else if (key == '2') {
      moveServo(servoPin1, 90);
    } else if (key == '3') {
      moveServo(servoPin1, 0);
    } else if (key == '4') {
      moveServo(servoPin2, 140);
    } else if (key == '5') {
      moveServo(servoPin2, 90);
    } else if (key == '6') {
      moveServo(servoPin2, 45);
    }
  }
}

void loop() {
  char key = getKey();

  if (key) {
    if (key == 'A') {
      automaticMode = true;
      modeSelected = true;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Mode: Automatic");
      delay(1000);
      lcd.clear();
    } else if (key == 'B') {
      automaticMode = false;
      modeSelected = true;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Mode: Manual");
      delay(1000);
      lcd.clear();
    }else if (key == 'D') {
      // Reset mode selection and return to start screen
      modeSelected = false;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Select Mode: ");
      lcd.setCursor(0, 1);
      lcd.print("A:Auto B:Manual");
      return; // Exit the loop iteration to wait for user input
    }
  }

  // setting red (R) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  redFrequency = pulseIn(sensorOut, LOW);
  delay(100);

  // setting green (G) filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  greenFrequency = pulseIn(sensorOut, LOW);
  delay(100);

  // setting blue (B) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blueFrequency = pulseIn(sensorOut, LOW);

  // print rgb frequency values to Serial Monitor
  Serial.print("R = ");
  Serial.print(redFrequency);
  Serial.print(" G = ");
  Serial.print(greenFrequency);
  Serial.print(" B = ");
  Serial.println(blueFrequency);

  // display color only if mode is selected
  displayColor(redFrequency, greenFrequency, blueFrequency, key);
  delay(300);
}
