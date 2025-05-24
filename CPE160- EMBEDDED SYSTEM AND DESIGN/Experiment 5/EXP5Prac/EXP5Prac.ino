#include <Servo.h>

// Servo setup for entrance and exit gates
Servo myservo;    // Entrance gate
Servo myservo1;   // Exit gate

int pos = 0;
int cm = 0;

// Initial parking state
int availableSlots = 10; // Total parking slots available
int carsEntered = 0;     // Total cars that have entered

// Segment pin connections (A to G)
int segmentPins[7] = {A5, A4, A3, A2, A1, A0, 10};
// Digit control pins (D4 to D1)
int digitPins[4] = {4, 13, 12, 11};

// Digit patterns for 0-9 on a 7-segment display
byte digitPatterns[10] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111  // 9
};

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

// Function to display a digit on the 7-segment display
void displayDigit(int digit, int position) {
  // Disable all digit displays
  for (int i = 0; i < 4; i++) {
    digitalWrite(digitPins[i], HIGH);
  }

  // Set segments for the current digit
  setSegments(digitPatterns[digit]);

  // Enable the current digit display
  digitalWrite(digitPins[position], LOW);
}

// Function to set segments of the 7-segment display
void setSegments(byte segments) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], (segments >> i) & 0x01);
  }
}

void setup() {
  myservo.attach(6); // Attach servo to entrance gate
  myservo1.attach(5); // Attach servo to exit gate
  Serial.begin(9600);

  // Initialize segment and digit pins
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
  }
}

void loop() {
  // Gate 1 - Entrance
  cm = 0.017 * readUltrasonicDistance(3, 2);

  if (cm < 9 && availableSlots > 0) { // Detect car and check available slots
    Serial.print(cm);
    Serial.println("cm");

    // Open entrance gate
    for (pos = 0; pos <= 120; pos += 1) {
      myservo.write(pos);
      delay(15);
    }
    delay(500);

    // Close entrance gate
    for (pos = 120; pos >= 0; pos -= 1) {
      myservo.write(pos);
      delay(15);
    }

    availableSlots--; // Decrease available slots
    carsEntered++;    // Increase cars entered count
  }

  // Gate 2 - Exit
  cm = 0.017 * readUltrasonicDistance(9, 8);

  if (cm < 5 && carsEntered > 0) { // Detect car and check if any cars have entered
    Serial.print(cm);
    Serial.println("cm");

    // Open exit gate
    for (pos = 0; pos <= 120; pos += 1) {
      myservo1.write(pos);
      delay(15);
    }
    delay(500);

    // Close exit gate
    for (pos = 120; pos >= 0; pos -= 1) {
      myservo1.write(pos);
      delay(15);
    }

    availableSlots++; // Increase available slots
    carsEntered--;    // Decrease cars entered count
  }

  // Update the 7-segment display
  multiplexDisplay();
}

// Function to multiplex the 7-segment display
void multiplexDisplay() {
  int numbers[4] = {availableSlots / 10, availableSlots % 10, carsEntered / 10, carsEntered % 10};

  // Loop through each digit and display it
  for (int i = 0; i < 4; i++) {
    displayDigit(numbers[i], i);
    delay(2); // Short delay to reduce flickering
  }
}
