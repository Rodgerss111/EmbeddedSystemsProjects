#include <Servo.h>

Servo myservo; 
Servo myservo1;


int pos = 0;
int cm = 0;

int availableSlots = 10;
int carsEntered = 0;

int segmentPins[7] = {A5, A4, A3, A2, A1, A0, 10};
int digitPins[4] = {4, 13, 12, 11};


byte digitPatterns[10] = {
  0b00111111,
  0b00000110,
  0b01011011,
  0b01001111,
  0b01100110,
  0b01101101,
  0b01111101,
  0b00000111,
  0b01111111,
  0b01101111,

};

long readUltrasonicDistance(int triggerPin, int echoPin){
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

void displayDigit(int digit, int position) {
  for(int i = 0; i < 4; i++){
    digitalWrite(digitPins[i], HIGH);
  }

  setSegments(digitPatterns[digit]);
  digitalWrite(digitPins[position], LOW);

}

void setSegments(byte segments){
  for (int i = 0; i<7; i++){
    digitalWrite(segmentPins[i], (segments >> i)& 0x01);
  }
}


void setup() {
  myservo.attach(6);
  myservo1.attach(5);
  Serial.begin(9600);

  for (int i = 0; i<7; i++){
    pinMode(segmentPins[i], OUTPUT);
  }
  for (int i = 0; i<4; i++){
    pinMode(digitPins[i], OUTPUT);
  }

}

void loop() {
  //Gate1 - Entrance
  cm = 0.017 * readUltrasonicDistance(3, 2);

  if (cm < 9 && availableSlots > 0){
    Serial.print(cm);
    Serial.print("cm");

   
    //close
    availableSlots--;
    carsEntered++;
  }

  //Gate 2 - Exit
  cm = 0.017 * readUltrasonicDistance(9, 8);

  if (cm<5 && carsEntered > 0){
    Serial.print(cm);
    Serial.println("cm");

    for (pos = 0; pos<= 120; pos += 1){
      myservo1.write(pos);
      delay(15);
    }
    delay(500);

    //Close gate

    for(pos = 120; pos >= 0; pos -=1){
      myservo1.write(pos);
      delay(15);
    }
    availableSlots++;
    carsEntered--;
  }
  multiplexDisplay();
}

 //seven segment display
  void multiplexDisplay(){
    int numbers[4]= {availableSlots / 10, availableSlots % 10, carsEntered / 10, carsEntered % 10};
    for (int i = 0;i < 4;i++){
      displayDigit(numbers[i], i);
      delay(2);
    }
  }





