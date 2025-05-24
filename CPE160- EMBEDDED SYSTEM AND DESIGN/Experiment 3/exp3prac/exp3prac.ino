// Pin definitions for seven-segment displays
const int segPins[7] = {2, 3, 4, 5, 6, 7, 8};  // Pins connected to segments a-g
const int digitPins[4] = {9, 10, 11, 12};      // Pins for controlling which digit is active

const int dppin = 1;

// Pin definitions for switches
const int switch1Pin = 13;   // Pin for mode toggle (hour/minute)
const int switch2Pin = A0;   // Pin for increment/decrement button

// Time variables
int hours = 12;
int minutes = 0;
bool adjustMinutes = true;   // true = adjust minutes, false = adjust hours
bool incrementMode = true;   // true = increment, false = decrement

// Timing variables for clock and debounce
unsigned long previousMillis = 0;
const long interval = 60000; // Clock update interval (1 minute)
unsigned long lastSwitch1PressTime = 0;
unsigned long lastSwitch2PressTime = 0;
const int debounceDelay = 50; // Debounce delay
bool lastSwitch1State = HIGH;
bool lastSwitch2State = HIGH;

// Seven-segment display encoding for digits 0-9
byte digitCodes[10] = {
  B00111111, // 0
  B00000110, // 1
  B01011011, // 2
  B01001111, // 3
  B01100110, // 4
  B01101101, // 5
  B01111101, // 6
  B00000111, // 7
  B01111111, // 8
  B01101111  // 9
};

void setup() {
  // Set segment pins as outputs
  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
  }

  // Set digit control pins as outputs
  for (int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
    digitalWrite(digitPins[i], HIGH); // Disable all displays initially
  }

  pinMode(dppin, OUTPUT);

  // Set switch pins as inputs with pull-up resistors
  pinMode(switch1Pin, INPUT);
  pinMode(switch2Pin, INPUT);

  // Display initial time
  displayTime(hours, minutes);
}

void loop() {
  // Read the state of the switches
  bool switch1State = digitalRead(switch1Pin);
  bool switch2State = digitalRead(switch2Pin);

  digitalWrite(dppin, HIGH);

  // Handle switch 1 (toggle between adjusting minutes or hours)
  if (switch1State != lastSwitch1State) {
    if (switch1State == LOW && millis() - lastSwitch1PressTime > debounceDelay) {
      adjustMinutes = !adjustMinutes; // Toggle between minute/hour adjustment
      lastSwitch1PressTime = millis();
    }
    lastSwitch1State = switch1State;
  }

  // Handle switch 2 (increment or decrement the time)
  if (switch2State != lastSwitch2State) {
    if (switch2State == LOW && millis() - lastSwitch2PressTime > debounceDelay) {
      if (incrementMode) {
        if (adjustMinutes) {
          incrementMinute();
        } else {
          incrementHour();
        }
      } else {
        if (adjustMinutes) {
          decrementMinute();
        } else {
          decrementHour();
        }
      }
      lastSwitch2PressTime = millis();
    }
    lastSwitch2State = switch2State;
  }

  // Handle clock ticking
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    incrementMinute();  // Update the clock every minute
  }

  // Continuously update the display
  displayTime(hours, minutes);
}

// Function to increment the clock by one minute
void incrementMinute() {
  minutes++;
  if (minutes >= 60) {
    minutes = 0;
    incrementHour();  // Only increment hours when minutes roll over
  }
}

// Function to decrement the clock by one minute
void decrementMinute() {
  minutes--;
  if (minutes < 0) {
    minutes = 59;
    decrementHour();  // Only decrement hours when minutes roll under
  }
}

// Function to increment the clock by one hour
void incrementHour() {
  hours++;
  if (hours > 12) {
    hours = 1;
  }
}

// Function to decrement the clock by one hour
void decrementHour() {
  hours--;
  if (hours < 1) {
    hours = 12;
  }
}

// Function to display the time on the seven-segment displays
void displayTime(int hrs, int mins) {
  int digits[4] = {hrs / 10, hrs % 10, mins / 10, mins % 10}; // Extract digits

  for (int i = 0; i < 4; i++) {
    // Activate current digit
    digitalWrite(digitPins[i], LOW);

    // Display corresponding segments
    setSegments(digitCodes[digits[i]]);

    // Delay to stabilize display
    delay(5);

    // Deactivate current digit
    digitalWrite(digitPins[i], HIGH);
  }
}

// Function to set the segments of the display
void setSegments(byte segments) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segPins[i], (segments >> i) & 0x01);
  }
}



