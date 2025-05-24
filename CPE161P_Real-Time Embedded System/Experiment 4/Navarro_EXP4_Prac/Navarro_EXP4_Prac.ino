#include <Arduino.h>
#include <IRremote.hpp>
#include <Servo.h>
#define plus 0xA3C8EDDB   //clockwise rotation button
#define minus 0xF076C13B  //counter clockwise rotation button

const int IR_RECEIVE_PIN = 7;
const int redPin = 10;

void setup()
{
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
  pinMode(redPin, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
  servo.attach(11);     //servo pin
}

void loop(){
  if (IrReceiver.decode()) 
  {
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    IrReceiver.printIRResultShort(&Serial);

    switch(IrReceiver.decodedIRData.decodedRawData)
    {
      case 0xE31CFF00: //Keypad button "5"
        Serial.println("5");
        digitalWrite(redPin, HIGH);
        break;
      default:
        break;
    }

    IrReceiver.resume(); // Enable receiving of the next value
  }


  if (IrReceiver.decode()) 
  {
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    IrReceiver.printIRResultShort(&Serial);

    switch(IrReceiver.decodedIRData.decodedRawData)
    {
      case 0xE31CFF00: //Keypad button "5"
        Serial.println("5");
        if (redPin, HIGH){
        digitalWrite(redPin, LOW);
        }
        break;
      default:
        break;
    }

    IrReceiver.resume();
}



}