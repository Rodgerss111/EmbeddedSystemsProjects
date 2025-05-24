#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 10
#define DHTTYPE DHT11

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
 delay(1000);
 lcd.setCursor(0, 0);
 lcd.print("   My Weather");
 lcd.setCursor(0, 1);
 lcd.print("System is On");
 for(int a = 12; a <= 15; a++){
  lcd.setCursor(a, 1);
  lcd.print(".");
  delay(1500);
 }
 lcd.clear();
}

void loop() {
  humid = dht.readHumidity();
  temp = dht.readTemperature();

  Serial.print("Humidity: ");
  Serial.print(humid);
  Serial.print(" Temperature: ");
  Serial.print(" ° Celsius");

  lcd.setCursor(0,0);
  lcd.print("   Monitoring  ");

  lcd.setCursor(0, 1);
  lcd.print("T: ");
  lcd.print(temp);
  lcd.print("C");

  lcd.setCursor(10, 1);
  lcd.print("H: ");
  lcd.print(humid);
  lcd.print("%");

  delay(1000);

}



