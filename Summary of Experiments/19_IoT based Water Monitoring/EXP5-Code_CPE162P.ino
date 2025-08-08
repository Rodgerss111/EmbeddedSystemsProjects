#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <ThingSpeak.h>
#include <time.h>

// WiFi Configuration
const char* ssid = "PLDTHOMEFIBRt6ucX";
const char* password = "PLDTWIFItLK72";

// ThingSpeak Configuration
const long myChannelNumber = 2964917;
const char myWriteAPIKey[] = "18A6ZBU4I3OLZZ44";

// Hardware Configuration
const int FLOW_SENSOR_PIN = 13;
const int WHITE_LED = 19;
const int GREEN_LED = 18;
const int BLUE_LED = 5;
const int YELLOW_LED = 4;
const int RED_LED = 23;

// Flow sensor parameters
volatile long pulseCount = 0;
float flowRate = 0.0;
float totalVolume = 0.0;
unsigned long lastTime = 0;
const int CALCULATION_INTERVAL = 2000;

// Volume thresholds
const float VOLUME_LOW = 5.0;
const float VOLUME_MODERATE = 10.0;
const float VOLUME_HIGH = 15.0;
const float VOLUME_MAX = 20.0;

// LCD Object
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Time configuration
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 8 * 3600;  // GMT+8 for Philippines
const int daylightOffset_sec = 0;

// System Parameters
const int UPDATE_INTERVAL = 15000;
unsigned long lastUpdate = 0;
WiFiClient client;

// Flow tracking variables
char flowStartTime[9] = "00:00:00";  // Time when flow started
char flowEndTime[9] = "00:00:00";    // Time when flow ended
bool isFlowing = false;              // Current flow state
bool wasFlowing = false;             // Previous flow state
unsigned long lastTimeSync = 0;
const int TIME_SYNC_INTERVAL = 3600000; // Sync time every hour

// Timer variables
unsigned long flowStartMillis = 0;    // When flow started (millis)
unsigned long flowDuration = 0;       // Total flow duration in ms
char durationString[9] = "00:00:00"; // Formatted duration

// Average flow rate calculation
const int AVG_INTERVAL = 60000;       // 1 minute in ms
float flowRateSum = 0.0;              // Sum of flow rates
int flowRateCount = 0;                // Number of samples
unsigned long lastAvgReset = 0;       // Last time average was reset
float averageFlowRate = 0.0;          // Calculated average

void setup() {
  initializePins();
  initializeDisplay();
  initializeSerial();
  showStartupScreen();
  connectToWiFi();
  syncTime();
  ThingSpeak.begin(client);
  
  attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), pulseCounter, RISING);
  
  // Initialize average timing
  lastAvgReset = millis();
}

void loop() {
  // Sync time periodically
  if (millis() - lastTimeSync > TIME_SYNC_INTERVAL) {
    syncTime();
  }
  
  calculateFlowRate();
  updateFlowTracking();
  calculateAverageFlowRate();  // New function for average calculation
  updateDisplay();
  updateLEDs();
  sendToCloud();
  delay(100);
}

// Time synchronization function
void syncTime() {
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  lastTimeSync = millis();
  Serial.println("Time synchronized");
}

// Flow tracking function
void updateFlowTracking() {
  // Update flow state with hysteresis to prevent flickering
  isFlowing = (flowRate > 0.1);  // Threshold to ignore noise
  
  if (isFlowing && !wasFlowing) {
    // Flow just started - record start time
    struct tm timeinfo;
    if (getLocalTime(&timeinfo)) {
      strftime(flowStartTime, sizeof(flowStartTime), "%H:%M:%S", &timeinfo);
    }
    flowStartMillis = millis();  // Start the timer
    Serial.println("Flow started");
  } 
  else if (!isFlowing && wasFlowing) {
    // Flow just ended - record end time and duration
    struct tm timeinfo;
    if (getLocalTime(&timeinfo)) {
      strftime(flowEndTime, sizeof(flowEndTime), "%H:%M:%S", &timeinfo);
    }
    flowDuration = millis() - flowStartMillis;  // Final duration
    formatDuration(flowDuration);               // Format for display
    Serial.println("Flow ended");
  }
  
  wasFlowing = isFlowing;  // Update previous state
}

// New function: Calculate average flow rate
void calculateAverageFlowRate() {
  unsigned long currentTime = millis();
  
  // Add current flow rate to sum
  flowRateSum += flowRate;
  flowRateCount++;
  
  // Check if 1 minute has passed
  if (currentTime - lastAvgReset >= AVG_INTERVAL) {
    // Calculate average
    if (flowRateCount > 0) {
      averageFlowRate = flowRateSum / flowRateCount;
    } else {
      averageFlowRate = 0.0;
    }
    
    // Reset for next interval
    flowRateSum = 0.0;
    flowRateCount = 0;
    lastAvgReset = currentTime;
    
    Serial.print("Average Flow Rate: ");
    Serial.print(averageFlowRate, 2);
    Serial.println(" L/min");
  }
}

// Format milliseconds to HH:MM:SS
void formatDuration(unsigned long duration) {
  unsigned long seconds = duration / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours = minutes / 60;
  
  seconds %= 60;
  minutes %= 60;
  hours %= 100; // Limit to 2 digits
  
  snprintf(durationString, sizeof(durationString), "%02lu:%02lu:%02lu", hours, minutes, seconds);
}

// Optimized display function
void updateDisplay() {
  static bool firstRun = true;
  static char lastStatusLine[17] = "";
  static char lastDataLine[17] = "";
  
  // Build status line
  char statusLine[17];
  if (isFlowing) {
    // Update duration during flow
    unsigned long currentDuration = millis() - flowStartMillis;
    formatDuration(currentDuration);
    snprintf(statusLine, sizeof(statusLine), "FLOWING %s", durationString);
  } else {
    snprintf(statusLine, sizeof(statusLine), "LAST D: %s", durationString); // LD means Last Duration, it is the last recorded duration of the continuous flow of water through the flow sensor  
  }
  
  // Build data line
  char dataLine[17];
  snprintf(dataLine, sizeof(dataLine), "F:%5.1fL V:%5.1fL", flowRate, totalVolume);
  
  // Update only changed portions of the display
  if (firstRun || strcmp(statusLine, lastStatusLine) != 0) {
    lcd.setCursor(0, 0);
    lcd.print(statusLine);
    strcpy(lastStatusLine, statusLine);
  }
  
  if (firstRun || strcmp(dataLine, lastDataLine) != 0) {
    lcd.setCursor(0, 1);
    lcd.print(dataLine);
    strcpy(lastDataLine, dataLine);
  }
  
  firstRun = false;
  
  // Debugging output (every 5 seconds)
  static unsigned long lastSerialOutput = 0;
  if (millis() - lastSerialOutput > 5000) {
    Serial.print("Status: ");
    Serial.print(statusLine);
    Serial.print(" | Data: ");
    Serial.println(dataLine);
    lastSerialOutput = millis();
  }
}

// Initialization Functions
void initializePins() {
  pinMode(WHITE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(FLOW_SENSOR_PIN, INPUT_PULLUP);
  allLEDsOff();
}

void initializeSerial() {
  Serial.begin(115200);
  while(!Serial); // Wait for serial connection
}

void initializeDisplay() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

// Core Functions
void connectToWiFi() {
  lcd.clear();
  lcd.print("Connecting WiFi");
  
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    lcd.print(".");
  }
  
  lcd.clear();
  lcd.print("WiFi Connected!");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  delay(2000);
  lcd.clear();
}

// Flow Sensor Functions
void pulseCounter() {
  pulseCount++;
}

void calculateFlowRate() {
  static unsigned long lastCalculation = 0;
  unsigned long currentTime = millis();
  
  if ((currentTime - lastCalculation) > CALCULATION_INTERVAL) {
    lastCalculation = currentTime;
    
    // Calculate flow rate
    float newFlowRate = 2.663 * pulseCount / 1000 * 30; // Liters per minute
    
    // Calculate total volume
    totalVolume += newFlowRate * (CALCULATION_INTERVAL / 60000.0);
    
    // Apply smoothing to flow rate
    flowRate = (flowRate * 0.7) + (newFlowRate * 0.3);
    
    // Reset pulse counter
    pulseCount = 0;
  }
}

// LED Control
void updateLEDs() {
  allLEDsOff();
  
  if (totalVolume < VOLUME_LOW) {
    digitalWrite(WHITE_LED, HIGH);
  } else if (totalVolume < VOLUME_MODERATE) {
    digitalWrite(YELLOW_LED, HIGH);
  } else if (totalVolume < VOLUME_HIGH) {
    digitalWrite(GREEN_LED, HIGH);
  } else if (totalVolume < VOLUME_MAX) {
    digitalWrite(BLUE_LED, HIGH);
  } else {
    digitalWrite(RED_LED, HIGH);
  }
}

void allLEDsOff() {
  digitalWrite(WHITE_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
}

// Cloud Functions
void sendToCloud() {
  if(millis() - lastUpdate >= UPDATE_INTERVAL) {
    lastUpdate = millis();
    
    ThingSpeak.setField(1, flowRate);           // Current flow rate
    ThingSpeak.setField(2, totalVolume);        // Total volume
    ThingSpeak.setField(3, averageFlowRate);    // Average flow rate per minute
    
    int status = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    
    if(status == 200) {
      Serial.println("Cloud update OK");
    } else {
      Serial.print("Cloud update failed: ");
      Serial.println(status);
    }
  }
}

// Utility Functions
void showStartupScreen() {
  lcd.setCursor(0, 0);
  lcd.print("Water Volume");
  lcd.setCursor(0, 1);
  lcd.print("Monitoring Vol.");
  delay(2000);
  lcd.clear();
}
