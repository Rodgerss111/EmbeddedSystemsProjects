#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <ThingSpeak.h>

// WiFI credentials
const char* ssid = "PLDTHOMEFIBRt6ucX";
const char* password = "PLDTWIFItLK72";

// ThingSpeak setup
WiFiClient client;
long myChannelNumber = 2964917;
const char myWriteAPIKey[] = "18A6ZBU4I3OLZZ44";

#define DHTPIN 32   // DHT11 data pin connected to GPIO32
#define DHTTYPE DHT11
#define THERMISTOR_PIN 36 // Analog sensor pin GPIO36

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long lastUpdate = 0;
const unsigned long updateInterval = 15000; // 15 seconds minimum for thingspeak

// average temperature
float tempSum = 0;
int tempCount = 0;
unsigned long avgStartTime = 0;
unsigned long avgInterval = 300000; // 5 minutes in milliseconds

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("   My Weather");
  lcd.setCursor(0,1);
  lcd.print("System is ON");
  delay(3000);
  lcd.clear();

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  ThingSpeak.begin(client);

  avgStartTime = millis(); // start timer for average temperature
}

void loop() {
  // reading analog temperature - LM35
  int sensorValue = analogRead(THERMISTOR_PIN);
  float voltage = sensorValue * (3.3 / 4095.0); // esp32 ADC is 12-bit
  float temperature = voltage * 100.0;   // LM35: 10mv per Celsius

  float humidity = dht.readHumidity();  // read DHT11 sensor
  
  // Handle errors
  if (isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    humidity = 0;
  }

  // debug output
  Serial.print("Voltage: ");
  Serial.println(voltage, 2);
  Serial.print("Temperature: ");
  Serial.print(temperature, 1);
  Serial.println(" °C");
  Serial.print("Humidity: ");
  Serial.print(humidity, 1);
  Serial.println(" %");

  // display on LCD
  lcd.setCursor(0, 0);
  lcd.print("   Monitoring  ");
  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(temperature, 1);
  lcd.print((char)223);
  lcd.print("C H:");
  lcd.print(humidity, 1);
  lcd.print("%");

  // accumulate for average
  tempSum += temperature;
  tempCount++;

  //Send current data every 15 seconds
  if (millis() - lastUpdate >= updateInterval){
    lastUpdate = millis();

    ThingSpeak.setField(1, temperature);   //Field 1 = temperature
    ThingSpeak.setField(2, humidity);  //Field 2 = humidity

    // only send average if 5 minutes have passed
    if (millis() - avgStartTime >= avgInterval){
      float avgTemp = tempSum / tempCount;
      ThingSpeak.setField(3, avgTemp); // Field 3 = average temp

      Serial.print("5-minute average temp");
      Serial.println(avgTemp, 2);

    // Reset accumulators
    tempSum = 0;
    tempCount = 0;
    avgStartTime = millis();
    }
    int statusCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    if (statusCode == 200){
      Serial.println("Channel update successfull.");
  } else {
    Serial.print("ThingSpeak update failed. Code: ");
    Serial.print(statusCode);
      }
    }
    delay(1000); // reduce flicker and allow sensor to settle
  }
