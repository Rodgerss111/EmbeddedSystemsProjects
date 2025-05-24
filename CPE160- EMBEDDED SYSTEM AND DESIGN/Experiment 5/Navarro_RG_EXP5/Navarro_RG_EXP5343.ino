#include <Servo.h>


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
    delay(500);

    //Close gate
    availableSlots++;
    carsEntered--;
  }
  multiplexDisplay();
}

 //seven segment display






