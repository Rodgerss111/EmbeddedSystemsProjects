#include <Wire.h>
#include <LiquidCrystal_I2C.h> // For LCD

// Ultrasonic sensor pins
#define TRIG_PIN 2
#define ECHO_PIN 3

// LED and buzzer pins
#define RED_LED 11
#define GREEN_LED 13
#define BUZZER 12

// Buttons
#define BUTTON_PIN A0 // All buttons connected to A0

// Seven Segment Display Pins
#define SEG_A A3
#define SEG_B A2
#define SEG_C A1
#define SEG_D 12
#define SEG_E 8
#define SEG_F 9
#define SEG_G 10
#define DIGIT_1 4
#define DIGIT_2 5
#define DIGIT_3 6
#define DIGIT_4 7

// Constants
#define MAX_TIME 30 // Maximum timer in minutes
#define MIN_TIME 1 // Minimum timer in minutes
#define DISTANCE_THRESHOLD 10 // cm for the ultrasonic sensor
#define INACTIVITY_TIMEOUT 10000 // 10 seconds inactivity timeout

// Variables
int sittingTime = 5; // Default sitting time in minutes
int standingTime = 5; // Default standing time in minutes
bool isSittingTimer = true; // Toggle between sitting and standing
unsigned long previousMillis = 0; // For countdown
unsigned long buttonPressMillis = 0; // Last button press timestamp
unsigned long inactivityMillis = 0; // For inactivity check
unsigned long lastSecondMillis = 0; // To track seconds for countdown
bool buzzerActive = false; // For buzzer state
int buttonValue = 0;
int totalSecondsRemaining; // Total time remaining in seconds

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change I2C address if needed

void setup() {
  // Pin setup
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Setup seven-segment display pins as OUTPUT
  pinMode(SEG_A, OUTPUT);
  pinMode(SEG_B, OUTPUT);
  pinMode(SEG_C, OUTPUT);
  pinMode(SEG_D, OUTPUT);
  pinMode(SEG_E, OUTPUT);
  pinMode(SEG_F, OUTPUT);
  pinMode(SEG_G, OUTPUT);
  pinMode(DIGIT_1, OUTPUT);
  pinMode(DIGIT_2, OUTPUT);
  pinMode(DIGIT_3, OUTPUT);
  pinMode(DIGIT_4, OUTPUT);

  // Initialize LCD
  lcd.init();
  lcd.backlight();

  // Start the timer with the default sitting time
  totalSecondsRemaining = sittingTime * 60;

  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();

  // Read buttons
  buttonValue = analogRead(BUTTON_PIN);
  handleButtons();

  // Manage inactivity for showing the message on LCD
  if (currentMillis - buttonPressMillis > INACTIVITY_TIMEOUT) {
    updateLCD();
  }

  // Countdown logic for the timer (1-second intervals)
  if (currentMillis - lastSecondMillis >= 1000) {
    lastSecondMillis = currentMillis;
    if (totalSecondsRemaining > 0) {
      totalSecondsRemaining--;
    } else {
      // Timer expired, switch between sitting and standing
      toggleTimer();
    }
  }

  // Display countdown on seven-segment display
  displayTimeOnSegment();

  // Handle Ultrasonic Sensor
  checkUltrasonicSensor();

  // Handle buzzer and LED blinking when timers are done
  handleBuzzerAndLED();
}

void handleButtons() {
  if (buttonValue >= 1018 && buttonValue <= 1025) {
    // Button 1: Increment sitting time
    if (isSittingTimer && sittingTime < MAX_TIME) sittingTime++;
    resetTimer();
  } else if (buttonValue >= 920 && buttonValue <= 935) {
    // Button 2: Decrement sitting time
    if (isSittingTimer && sittingTime > MIN_TIME) sittingTime--;
    resetTimer();
  } else if (buttonValue >= 998 && buttonValue <= 1005) {
    // Button 3: Increment standing time
    if (!isSittingTimer && standingTime < MAX_TIME) standingTime++;
    resetTimer();
  } else if (buttonValue >= 1008 && buttonValue <= 1015) {
    // Button 4: Decrement standing time
    if (!isSittingTimer && standingTime > MIN_TIME) standingTime--;
    resetTimer();
  } else if (buttonValue >= 965 && buttonValue <= 975) {
    // Button 5: Toggle between sitting and standing settings
    isSittingTimer = !isSittingTimer;
    resetTimer();
  }

  // Record the time of the last button press
  buttonPressMillis = millis();
}

void resetTimer() {
  // Reset the timer based on the current sitting or standing setting
  if (isSittingTimer) {
    totalSecondsRemaining = sittingTime * 60;
  } else {
    totalSecondsRemaining = standingTime * 60;
  }
}

void toggleTimer() {
  // Switch between sitting and standing timers once the current one ends
  isSittingTimer = !isSittingTimer;
  resetTimer();
  buzzerActive = true; // Activate buzzer when the timer switches
}

void displayTimeOnSegment() {
  int minutes = totalSecondsRemaining / 60;
  int seconds = totalSecondsRemaining % 60;

  displayDigit(minutes / 10, 1); // Tens place of minutes
  displayDigit(minutes % 10, 2); // Ones place of minutes
  displayDigit(seconds / 10, 3); // Tens place of seconds
  displayDigit(seconds % 10, 4); // Ones place of seconds
}

void displayDigit(int number, int digit) {
  // Control which digit to display (1, 2, 3, 4)
  digitalWrite(DIGIT_1, digit == 1);
  digitalWrite(DIGIT_2, digit == 2);
  digitalWrite(DIGIT_3, digit == 3);
  digitalWrite(DIGIT_4, digit == 4);

  // Set the segments for the number
  const bool numbers[10][7] = {
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 0, 0, 1, 1}  // 9
  };

  digitalWrite(SEG_A, numbers[number][0]);
  digitalWrite(SEG_B, numbers[number][1]);
  digitalWrite(SEG_C, numbers[number][2]);
  digitalWrite(SEG_D, numbers[number][3]);
  digitalWrite(SEG_E, numbers[number][4]);
  digitalWrite(SEG_F, numbers[number][5]);
  digitalWrite(SEG_G, numbers[number][6]);
}

void updateLCD() {
  lcd.clear();
  if (isSittingTimer) {
    lcd.setCursor(0, 0);
    lcd.print("Sit Time: ");
    lcd.print(sittingTime);
    lcd.print(" mins");
    lcd.setCursor(0, 1);
    lcd.print("Get ready to work");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Stand Time: ");
    lcd.print(standingTime);
    lcd.print(" mins");
    lcd.setCursor(0, 1);
    lcd.print("Get ready to stand");
  }
}

void checkUltrasonicSensor() {
  // Send pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read pulse
  unsigned long duration = pulseIn(ECHO_PIN, HIGH);
  unsigned int distance = duration * 0.034 / 2; // Calculate distance

  // If hand is detected within 10 cm, stop the buzzer
  if (distance <= DISTANCE_THRESHOLD) {
    buzzerActive = false;
    digitalWrite(BUZZER, LOW);
  }
}

void handleBuzzerAndLED() {
  if (buzzerActive) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, HIGH);
    delay(500);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER, LOW);
    delay(500);
  } else {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
  }
}
