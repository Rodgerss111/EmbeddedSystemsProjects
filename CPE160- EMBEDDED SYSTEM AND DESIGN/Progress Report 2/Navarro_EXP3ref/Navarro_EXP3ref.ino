#include <LiquidCrystal_I2C.h> // Include library for I2C LCD control

// Define pins for 7-segment display
const int sPins[7] = {A3, A2, A1, 12, 8, 9, 10}; // Segment pins
const int dPins[4] = {4, 5, 6, 7}; // Digit pins
const int dppin = 1; // Unused digit pin
const int buzzAlarm = 11; // Buzzer pin
const int ledGreen = 13; // Green LED pin
const int triggerPin = 3; // Ultrasonic sensor trigger pin
const int echoPin = 2; // Ultrasonic sensor echo pin

const int switch1Pin = A0; // Pin for button input
int sittingMinutes = 19; // Default sitting timer duration
int standingMinutes = 9; // Default standing timer duration
int maxMinutes = 30; // Maximum allowed minutes for timers
bool settingSitting = true; // Flag to track current timer mode (sitting or standing)
bool adjustMode = true; // Flag for adjustment mode

// Variables for timing and message display
unsigned long previousMillis = 0; // Store last time update
unsigned long messageMillis = 0; // Store last message time
const long interval = 1000; // 1 second interval for countdown
const long messageInterval = 5000; // 5 seconds for each motivational message on LCD
int minutes = sittingMinutes; // Initialize current minutes
int seconds = 0; // Initialize seconds
bool timerRunning = true; // Flag to control timer state (running or paused)
int messageIndex = 0; // Index for motivational messages
int cm = 0; // Variable for ultrasonic distance measurement

// Byte array for displaying digits on the 7-segment display
byte digitCodes[10] = {
  B00111111, B00000110, B01011011, B01001111,
  B01100110, B01101101, B01111101, B00000111,
  B01111111, B01101111
};

// Create an instance of the LCD display
LiquidCrystal_I2C dis(0x27, 16, 2); // I2C address, columns, rows

// Motivational messages for sitting and standing
const char* sittingMessages[] = {
  " Focus on Work!  ", " Keep Grinding!  ", "  Stay Sharp!!  ",
  "You're on Track!", "Reach your Goal"
};

const char* standingMessages[] = {
  "Stand & Stretch!", "Move your Body!!", " Shake it out!!  ", 
  "Feel Refreshed!!", " Time to Stand!  "
};

void setup() {
  Serial.begin(9600); // Start serial communication for debugging
  
  // Initialize pin modes
  pinMode(buzzAlarm, OUTPUT); // Set buzzer pin as output
  pinMode(ledGreen, OUTPUT); // Set green LED pin as output
  pinMode(triggerPin, OUTPUT); // Set ultrasonic trigger pin as output
  pinMode(echoPin, INPUT); // Set ultrasonic echo pin as input

  // Set segment pins as output
  for (int i = 0; i < 7; i++) {
    pinMode(sPins[i], OUTPUT);
  }

  // Set digit pins as output and turn them off initially
  for (int i = 0; i < 4; i++) {
    pinMode(dPins[i], OUTPUT);
    digitalWrite(dPins[i], HIGH);
  }

  pinMode(dppin, OUTPUT); // Set unused digit pin as output
  displayTime(minutes, seconds); // Display initial time

  // Initialize and display startup messages on the LCD
  dis.init();
  dis.backlight();
  dis.clear();
  dis.setCursor(0, 0);
  dis.print("StandUp Reminder");
  dis.setCursor(3, 1);
  dis.print("Good Day!");

  // Display a series of dots as a loading animation
  for (int a = 12; a <= 15; a++) {
    dis.setCursor(a, 1);
    dis.print(".");
    delay(1500);
  }
  dis.clear(); // Clear the display after the loading animation
}

void loop() {
  // Read analog value from the button
  int buttonValue = analogRead(switch1Pin);
  Serial.print("Analog value: ");
  Serial.print(buttonValue); // Print button value for debugging

  // Read the digital state of the button
  int allButtons = digitalRead(switch1Pin);

  // Determine button press actions based on the analog value
  if (buttonValue < 100) {
    allButtons = LOW; // No button pressed
  } else if (buttonValue < 150) {
    incrementTimer(true); // Increment sitting timer
    delay(500); // Debounce delay
  } else if (buttonValue < 250) {
    decrementTimer(true); // Decrement sitting timer
    delay(500); // Debounce delay
  } else if (buttonValue < 350) {
    incrementTimer(false); // Increment standing timer
    delay(500); // Debounce delay
  } else if (buttonValue < 850) {
    decrementTimer(false); // Decrement standing timer
    delay(500); // Debounce delay
  } else {
    switchTimerMode(); // Switch between sitting and standing timer
    delay(500); // Debounce delay
  }

  // Timer logic
  if (timerRunning) {
    unsigned long currentMillis = millis(); // Get current time in milliseconds
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis; // Update previousMillis
      if (seconds == 0) { // Check if seconds are zero
        if (minutes > 0) {
          minutes--; // Decrease minutes
          seconds = 59; // Reset seconds to 59
        } else {
          completeTimer(); // Timer completed
        }
      } else {
        seconds--; // Decrease seconds
      }
    }

    // Display motivational message at specified intervals
    if (currentMillis - messageMillis >= messageInterval) {
      messageMillis = currentMillis; // Update messageMillis
      displayMotivationalMessage(); // Show a motivational message
    }
  }
  
  displayTime(minutes, seconds); // Update the displayed time
}

void incrementTimer(bool sitting) {
  // Increment the timer based on whether it's the sitting or standing timer
  if (sitting) {
    if (sittingMinutes < maxMinutes) sittingMinutes++; // Increment sitting minutes
    if (settingSitting) minutes = sittingMinutes; // Update displayed minutes if sitting timer is active
  } else {
    if (standingMinutes < maxMinutes) standingMinutes++; // Increment standing minutes
    if (!settingSitting) minutes = standingMinutes; // Update displayed minutes if standing timer is active
  }
}

void decrementTimer(bool sitting) {
  // Decrement the timer based on whether it's the sitting or standing timer
  if (sitting) {
    if (sittingMinutes > 0) sittingMinutes--; // Decrement sitting minutes
    if (settingSitting) minutes = sittingMinutes; // Update displayed minutes if sitting timer is active
  } else {
    if (standingMinutes > 0) standingMinutes--; // Decrement standing minutes
    if (!settingSitting) minutes = standingMinutes; // Update displayed minutes if standing timer is active
  }
}

void switchTimerMode() {
  // Switch between sitting and standing timer modes
  settingSitting = !settingSitting; // Toggle the mode
  timerRunning = true; // Resume the timer

  if (settingSitting) {
    minutes = sittingMinutes; // Set minutes to sitting timer
    Serial.println("Switched to Sitting Timer");
    dis.setCursor(2, 1);
    dis.print("Sitting Time "); // Display current mode on LCD
    seconds = 59; // Reset seconds to 59
  } else {
    minutes = standingMinutes; // Set minutes to standing timer
    Serial.println("Switched to Standing Timer");
    dis.setCursor(2, 1);
    dis.print("Stand Up Time"); // Display current mode on LCD
    seconds = 59; // Reset seconds to 59
  }
}

void displayMotivationalMessage() {
  // Display motivational messages based on current timer mode
  dis.setCursor(0, 0);
  if (settingSitting) {
    dis.print(sittingMessages[messageIndex]); // Show sitting message
  } else {
    dis.print(standingMessages[messageIndex]); // Show standing message
  }
  messageIndex = (messageIndex + 1) % 5; // Cycle through messages
}

void displayTime(int mins, int secs) {
  // Convert minutes and seconds to digits and display on 7-segment
  int digits[4] = {mins / 10, mins % 10, secs / 10, secs % 10}; // Split time into digits

  for (int i = 0; i < 4; i++) {
    digitalWrite(dPins[i], LOW); // Activate digit pin
    setSegments(digitCodes[digits[i]]); // Display corresponding segment code
    delay(5); // Short delay for visibility
    digitalWrite(dPins[i], HIGH); // Deactivate digit pin
  }
}

void setSegments(byte segments) {
  // Set segments of the 7-segment display
