#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C dis(0x27, 16, 2);
#include <Servo.h>
Servo myservo1;   // Exit gate
int pos = 0;
int cm = 0;
 
void setup() {
  myservo1.attach(7);
  Serial.begin(9600);
  dis.init();
  dis.backlight();
  dis.clear();
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  delay(1000);
  dis.setCursor(0, 0);
  dis.print("IRRIGATION");
  dis.setCursor(0, 1);
  dis.print("SYSTEM IS ON ");
  for (int a = 12; a <= 15; a++) {
    dis.setCursor(a, 1);
    dis.print(".");
    delay(1500);
  }
  dis.clear();
}
 
void loop() {
  int value = analogRead(A0);
  Serial.println(value);



  

  if (value >= 900) {
        dis.setCursor(0, 1);
    dis.print("MOISTURE : VLOW ");
     digitalWrite(2, LOW);
    dis.setCursor(0, 0);
    dis.print("MOTOR IS ON ");
     // Open exit gate
    for (pos = 0; pos <= 120; pos += 1) {
      myservo1.write(pos);
      delay(19);
    }
    delay(1000);

    // Close exit gate
    for (pos = 120; pos >= 0; pos -= 1) {
      myservo1.write(pos);
      delay(5);
    }
     delay(1000);
  }
    else if (value >= 700) {
        dis.setCursor(0, 1);
    dis.print("MOISTURE : LOW ");
     digitalWrite(2, LOW);
    dis.setCursor(0, 0);
    dis.print("MOTOR IS ON ");
    // Open exit gate
    for (pos = 0; pos <= 120; pos += 1) {
      myservo1.write(pos);
      delay(19);
    }
    delay(1000);

    // Close exit gate
    for (pos = 120; pos >= 0; pos -= 1) {
      myservo1.write(pos);
      delay(5);
    }
    delay(1000);
  }
    else if (value >= 500) {
        dis.setCursor(0, 1);
    dis.print("MOISTURE : MID  ");
    digitalWrite(2, LOW);
    dis.setCursor(0, 0);
    dis.print("MOTOR IS ON ");
    // Open exit gate
    for (pos = 0; pos <= 120; pos += 1) {
      myservo1.write(pos);
      delay(19);
    }
    delay(1000);

    // Close exit gate
    for (pos = 120; pos >= 0; pos -= 1) {
      myservo1.write(pos);
      delay(5);
    }
     delay(1000);
  }


    else if (value >= 310 ) {
       dis.setCursor(0, 1);
    dis.print("MOISTURE : NORMAL ");
    digitalWrite(2, HIGH);
    dis.setCursor(0, 0);
    dis.print("MOTOR IS OFF ");
     
  }
    else {
        // LEVEL 5 LED
        dis.setCursor(0, 1);
    dis.print("MOISTURE : HIGH ");
      digitalWrite(2, HIGH);
    dis.setCursor(0, 0);
    dis.print("MOTOR IS OFF ");
    
    }




}