
#include <DHT.h>
#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 10
#define DHTTYPE DHT11
const int buzzAlarm = 3;
int angle = 0;

Servo ServoSwitch;

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

int humid;
int temp;

void setup() {
  Serial.begin(9600);
  Serial.println("Temperature and Humidity Sensor");
  dht.begin();
  lcd.init();
  lcd.backlight();
  ServoSwitch.attach(9);
  pinMode(buzzAlarm, OUTPUT);
}

void loop() {
  
  humid = dht.readHumidity();
  temp = dht.readTemperature();

  Serial.print("Humidity: ");
  Serial.print(humid);
  Serial.print("%, Temperature: ");
  Serial.print(" ° Celsius");

  lcd.setCursor(1, 0);
  lcd.print("Kettle is ");
  displayTNH();

  lcd.setCursor(0, 1);
  lcd.print("T: ");
  lcd.print(temp);
  lcd.print("C");

  lcd.setCursor(10, 1);
  lcd.print("H: ");
  lcd.print(humid);
  lcd.print("%");

  delay(1000);

  if(temp >= 60){
    digitalWrite(buzzAlarm, HIGH);
    for(angle = 0; angle <= 180; angle++){
      ServoSwitch.write(angle);
      delay(20);
      break;
      delay(2000);
    
    }
  }else if(temp < 60){
    digitalWrite(buzzAlarm, LOW);
    for(angle = 180; angle > 0; angle--){
      ServoSwitch.write(angle);
      delay(20);
      break;
      delay(2000);

    }
  }


  }

  void displayTNH(){
    if(temp >= 60){
    lcd.setCursor(11, 0);
    lcd.print("OFF");
   
    }else if(temp < 60){
    lcd.setCursor(11, 0);
    lcd.print("ON ");
    }


}
