#include <Servo.h>

Servo myservo;
Servo myservo1;

int pos = 0;
int cm = 0;

long readUltrasonicDistance(int triggerPin, int echoPin) {
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
}

void loop() {

  cm = 0.017 * readUltrasonicDistance(3, 2);

  if (cm < 10) { 
    Serial.print(cm);
    Serial.println("cm");
    // Default the Bin is open
    // Close the bin
    for (pos = 0; pos <= 120; pos += 1) {
      myservo.write(pos);
      delay(12);
    }
    delay(500);


  }




  if (cm < 10) { 
    Serial.print(cm);
    Serial.println("cm");

    
    for (pos = 0; pos <= 120; pos += 1) {
      myservo1.write(pos);
      delay(8);
    }
    delay(500);

    
    for (pos = 120; pos >= 0; pos -= 1) {
      myservo1.write(pos);
      delay(12);
    }

    for (pos = 120; pos >= 0; pos -= 1) {
      myservo.write(pos);
      delay(15);
    }

  
  }

 
}
