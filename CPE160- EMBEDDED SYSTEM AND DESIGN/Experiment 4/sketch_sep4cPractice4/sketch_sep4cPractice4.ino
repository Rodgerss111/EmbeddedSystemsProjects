//Libraries

#include <DHT.h>
#include <Wire.h>
#include <Servo.h>
//I2C LCD:

#include <LiquidCrystal_I2C.h>
const int buzzAlarm = 3;
int angle = 0;

Servo myServo;


LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display

  

//Constants

#define DHTPIN 10    // what pin we're connected to

#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino



//Variables

//int chk;

int h;  //Stores humidity value

int t; //Stores temperature value



void setup()

{

    Serial.begin(9600);

    Serial.println("Temperature and Humidity Sensor Test");

    dht.begin();

    lcd.init(); //initialize the lcd

    lcd.backlight(); //open the backlight
    myServo.attach(9);
    pinMode(buzzAlarm,OUTPUT);

}



void loop()

{

    //Read data and store it to variables h (humidity) and t (temperature)

    // Reading temperature or humidity takes about 250 milliseconds!

    h = dht.readHumidity();

    t = dht.readTemperature();

    

    //Print temp and humidity values to serial monitor

    Serial.print("Humidity: ");

    Serial.print(h);

    Serial.print(" %, Temp: ");

    Serial.print(t);

    Serial.println(" ° Celsius");

        

// set the cursor to (0,0):

// print from 0 to 9:



    lcd.setCursor(0, 0);

    lcd.println(" Simple Circuits");

    

    lcd.setCursor(0, 1);

    lcd.print(" T:");

    lcd.print(t);

    lcd.print("C");

     

    lcd.setCursor(11, 1);

    lcd.print("H:");

    lcd.print(h);

    lcd.print("%");

    

  delay(1000); 


 if (h >= 95){
    digitalWrite(buzzAlarm,HIGH);
    for (angle = 0; angle<=180 ; angle++){
      myServo.write(angle);
      delay(20);
      break;
      delay(2000);
    }
  }
  else if(h < 95){
    digitalWrite(buzzAlarm,LOW);
    for (angle = 180; angle > 0; angle--){
      myServo.write(angle);
      delay(20);
      break;
      delay(2000);
    }
  }





}