#include <WiFi.h>
#include <ThingSpeak.h>

const char* ssid = "PLDTHOMEFIBRt6ucX";
const char* password = "PLDTWIFItLK72";

const int ldrPin = A0;
const int Green1 = 5;
const int Red1 = 18;
const int Blue1 = 19;
const int Yellow1 = 21;
const int Green2 = 3;

//LED status variables
int Green1Status = 0;
int Red1Status = 0;
int Blue1Status = 0;
int Yellow1Status = 0;
int Green2Status = 0;

// ThingSpeak setup
WiFiClient client;
long myChannelNumber = 2954171 ;
const char myWriteAPIKey[] = "7U4W9J6MTU110C7S";

void setup() {
  Serial.begin(9600);
  delay(1000);

  pinMode(ldrPin, INPUT);
  pinMode(Green1, OUTPUT);
  pinMode(Red1, OUTPUT);
  pinMode(Blue1, OUTPUT);
  pinMode(Yellow1, OUTPUT);
  pinMode(Green2, OUTPUT);

  ledClear();

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Start ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  int ldrValue = analogRead(ldrPin);
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  // Control LEDs based on LDR value
  if(ldrValue <= 500){
    ledLights();
    Serial.println("LEDs are ON");
  }else {
    ledClear();
    Serial.println("LEDs are OFF");
  }

  Green1Status = digitalRead(Green1);
  Red1Status = digitalRead(Red1);
  Blue1Status = digitalRead(Blue1);
  Yellow1Status = digitalRead(Yellow1);
  Green2Status = digitalRead(Green2);

  ThingSpeak.setField(1, ldrValue);
  ThingSpeak.setField(2, Green1Status);
  ThingSpeak.setField(3, Red1Status);
  ThingSpeak.setField(4, Blue1Status);
  ThingSpeak.setField(5, Yellow1Status);
  ThingSpeak.setField(6, Green2Status);
  
  int statusCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(statusCode == 200){
    Serial.println("Channel update successful.");
  }else {
    Serial.print("ThingSpeak update error. Code: ");
    Serial.println(statusCode);
  }
  delay(15000);

}

// Turn all LEDs OFF
void ledClear(){
  digitalWrite(Green1, LOW);
  digitalWrite(Red1, LOW);
  digitalWrite(Blue1, LOW);
  digitalWrite(Yellow1, LOW);
  digitalWrite(Green2, LOW);
}

// Turb all LEDs ON
void ledLights(){
  digitalWrite(Green1, HIGH);
  digitalWrite(Red1, HIGH);
  digitalWrite(Blue1, HIGH);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Green2, HIGH);
}


