#include <Servo.h>
#include <HX711_ADC.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

//C:\Users\user\AppData\Local\Arduino15\libraries 


static const uint8_t PIN_MP3_TX = 12;
static const uint8_t PIN_MP3_RX = 11;

// Global variables
unsigned long autoStartTime = 0;
float autoDurationMinutes = 0.0;
bool autoModeStarted = false;

unsigned long sortStartTime = 0;

unsigned long lastHomeUpdate = 0;
const unsigned long homeUpdateInterval = 500;  // Update every 500 ms

SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

DFRobotDFPlayerMini player;

// pin assignments
#define SERVO1_PIN 7
#define SERVO2_PIN 5
#define LOADCELL_DT 2
#define LOADCELL_SCK 3
#define ENCODER_DT 9
#define ENCODER_CLK 10

// objects
LiquidCrystal_I2C lcd(0x27, 16, 2);
LiquidCrystal_I2C lcd2(0x26, 16, 2);
HX711_ADC LoadCell(LOADCELL_DT, LOADCELL_SCK);
Servo servo1, servo2;

// variables 
bool isAutoMode = false;
unsigned long lastEncoderCheck = 0;
const int encoderDebounce = 5;
int lastEncoderCLK = HIGH;
int classifiedEggs = 0;
const int calibrationValue = 2102;

int gradeACount = 0;
int gradeBCount = 0;

void setup() {
  Serial.begin(9600);
  // Init serial port for DFPlayer Mini
  softwareSerial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd2.init(); 
  lcd2.backlight(); 

  pinMode(ENCODER_DT, INPUT);
  pinMode(ENCODER_CLK, INPUT);

  LoadCell.begin();
  LoadCell.start(2000);
  LoadCell.setCalFactor(calibrationValue);


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System Ready");
  delay(500);

  lcd2.clear();
  lcd2.setCursor(3, 0);
  lcd2.print("Good Day!");
  delay(500);

  displayHomeScreen();

// Start communication with DFPlayer Mini
  if (player.begin(softwareSerial)) {
    Serial.println("OK");

    // Set volume to maximum (0 to 30).
    player.volume(30);
    // Play the "0001.mp3" in the "mp3" folder on the SD card
    player.playMp3Folder(1);

  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }

}

void loop() {
  handleEncoder();

  if (isAutoMode) {
    if (!autoModeStarted) {
      autoStartTime = millis();      // Record start time
      autoDurationMinutes = 0.0;     // Reset duration
      autoModeStarted = true;
    }
    runAutoMode();
  } else {
    if (autoModeStarted) {
      // Calculate duration in minutes (with decimals)
      autoDurationMinutes = (millis() - autoStartTime) / 60000.0;

      // Send only time duration to ESP32 (serial)
      Serial.print("duration:");
      Serial.println(autoDurationMinutes, 2);

      autoModeStarted = false;  // Reset flag
    }

    displayHomeScreen();
  }

  // Always update LCD2
  lcd2.setCursor(0, 0);
  lcd2.print("Grade A: ");
  lcd2.print(gradeACount);
  lcd2.print("    ");

  lcd2.setCursor(0, 1);
  lcd2.print("Grade B: ");
  lcd2.print(gradeBCount);
  lcd2.print("    ");
}
// rotary encoder

void handleEncoder() {
  int currentCLK = digitalRead(ENCODER_CLK);

  // Detect falling edge (HIGH → LOW transition)
  if (currentCLK != lastEncoderCLK && currentCLK == LOW) {
    int dtValue = digitalRead(ENCODER_DT);

    // Rotation direction determined by DT pin state
    if (dtValue == HIGH) {
      // Clockwise rotation → Auto Mode
      // Play the "0001.mp3" in the "mp3" folder on the SD card
     player.playMp3Folder(3);
     animateTransition();
      if (!isAutoMode) {
        isAutoMode = true;
        animateTransition();
      }
    } else {
      // Counter-clockwise rotation → Home Mode
      if (isAutoMode) {
        isAutoMode = false;
        animateTransition();
      }
    }
  }
  
  lastEncoderCLK = currentCLK;  // Save current state for next check
}

// Home Screen
void displayHomeScreen() {
  if (millis() - lastHomeUpdate >= homeUpdateInterval) {
    lastHomeUpdate = millis();

    //lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Home Screen ");
    lcd.setCursor(0, 1);
    lcd.print("Eggs: ");
    lcd.print(classifiedEggs);

    lcd.setCursor(9, 1);
    lcd.print(autoDurationMinutes, 1);  // Show 1 decimal place
    if(autoDurationMinutes > 1.9){
    lcd.print("mins");
    }else{
      lcd.print("min");
    }

 delay(50);  // Optional: adjust if needed
  }
}

void animateTransition(){
  for (int i = 0; i < 16; i++) {
    lcd.clear();
    lcd.setCursor(i, 0);
    lcd.print(isAutoMode ? "Auto Mode" : "Home Mode");
    delay(30);
  }
  lcd.clear();
}

// Auto Mode
void runAutoMode(){
  sortStartTime = millis(); // Start timing
  servo1.attach(SERVO1_PIN);

  // Slowly move to 180°
  smoothServoMove(servo1, 180, 70, 17);
  delay(3500);

  // Fast return to 180°
  smoothServoMove(servo1, 70, 180, 3);
  delay(500);

  servo1.detach();

  float finalWeight = 0;
  unsigned long start = millis();

  while (millis() - start < 2500) {
    LoadCell.update();
    float weightGrams = LoadCell.getData();
    float weightKg = weightGrams / 1000.0;
    finalWeight = weightGrams;

    lcd.setCursor(0, 0);
    lcd.print("Weight: ");
    lcd.print(weightGrams, 1);
    lcd.print("g   ");

    lcd.setCursor(0, 1);
    lcd.print(weightKg, 3);
    lcd.print("kg   ");

    delay(100);
  }

  if (finalWeight < 1.0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Too Light (<20g)");
    lcd.setCursor(0, 1);
    lcd.print("Back to Home...");
    delay(2000);
    isAutoMode = false;
    player.volume(30);
    player.playMp3Folder(2);
    animateTransition();
    return;
  }

 servo2.attach(SERVO2_PIN);

  if (finalWeight > 28 && finalWeight < 55) {
    smoothServoMove(servo2, 90, 60, 10);
    delay(4000);
    gradeACount++;
    player.playMp3Folder(5);
    delay(3000);
  } if (finalWeight > 20.0 && finalWeight < 27) {
    smoothServoMove(servo2, 90, 130, 10);
    delay(4000);
    gradeBCount++;
    player.playMp3Folder(6);
    delay(4000);
  }
  servo2.write(90);
  delay(500);
  servo2.detach();


  classifiedEggs++;
  delay(1000);

  // ===> SEND TO ESP32/THINGSPeak here after sorting ===
  unsigned long sortDuration = (millis() - sortStartTime) / 1000; // in seconds
  Serial.print("field1="); Serial.print(classifiedEggs);
  Serial.print("&field2="); Serial.print(gradeACount);
  Serial.print("&field3="); Serial.print(gradeBCount);
  Serial.print("&field4="); Serial.println(autoDurationMinutes);
  // ESP32 reads this string via Serial and uploads to ThingSpeak
  player.playMp3Folder(4);
   delay(2000);
}
// ===> END MODIFIED SECTION




// Smooth servo movement function
void smoothServoMove(Servo &servo, int fromAngle, int toAngle, int stepDelay) {
  int step = (fromAngle < toAngle) ? 1 : -1;
  for (int angle = fromAngle; angle != toAngle; angle += step) {
    servo.write(angle);
    delay(stepDelay);
  }
  servo.write(toAngle); // ensure it lands exactly
}

