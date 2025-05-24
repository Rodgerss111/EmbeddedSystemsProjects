#include <Servo.h>

// Servo setup for entrance and exit gates
Servo myservo;    // Entrance gate
Servo myservo1;   // Exit gate

int pos = 0;
int cm = 0;


// Function to read ultrasonic distance
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
  myservo.attach(6); // Attach servo to entrance gate
  myservo1.attach(5); // Attach servo to exit gate
  Serial.begin(9600);

}

void loop() {
  // Gate 1 - Entrance
  cm = 0.01 * readUltrasonicDistance(3, 2);

  if (cm < 1) { 
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

  // Gate 2 - Exit


  if (cm < 1) { // Detect car and check if any cars have entered
    Serial.print(cm);
    Serial.println("cm");

    // Open exit gate
    for (pos = 0; pos <= 120; pos += 1) {
      myservo1.write(pos);
      delay(19);
    }
    delay(500);

    // Close exit gate
    for (pos = 120; pos >= 0; pos -= 1) {
      myservo1.write(pos);
      delay(15);
    }

    for (pos = 120; pos >= 0; pos -= 1) {
      myservo.write(pos);
      delay(15);
    }

  
  }

 
}

