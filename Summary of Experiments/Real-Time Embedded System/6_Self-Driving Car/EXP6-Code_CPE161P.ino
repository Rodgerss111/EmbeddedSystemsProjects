#include<IRremote.hpp>

const int irRemotePin = 8; // the irRemote receiver pin
int motorLpwm = 10;
int motorRpwm = 9;
int motorSpeed = 60;
int turn = 10;

int motorRightPin1 = 2;
int motorRightPin2 = 3;
int motorLeftPin1 = 4;
int motorLeftPin2 = 5;

void setup() {
  Serial.begin(9600);
  pinMode(motorRightPin1, OUTPUT);
  pinMode(motorRightPin2, OUTPUT);
  pinMode(motorLeftPin1, OUTPUT);
  pinMode(motorLeftPin2, OUTPUT);
  IrReceiver.begin(irRemotePin, ENABLE_LED_FEEDBACK); // start IR receiver
  
}

void loop() {
  // check if IR signal is recieverd
 if (IrReceiver.decode()){
  Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); //print received IR data
  IrReceiver.printIRResultShort(&Serial); // print a IR result summary

  executeCommand(IrReceiver.decodedIRData.decodedRawData);
  IrReceiver.resume(); // prepare IR for the next command
 }
}

void executeCommand(unsigned long command) {
  switch (command) {
        case 0xE718FF00: Serial.println("2"); moveForward(); break;  // Move forward
        case 0xAD52FF00: Serial.println("8"); moveBackward(); break; // Move backward
        case 0xF708FF00: Serial.println("4"); turnLeft(); break;     // Turn left
        case 0xA55AFF00: Serial.println("6"); turnRight(); break;    // Turn right
        case 0xE31CFF00: Serial.println("5"); carStop(); break;      // Stop the car
        default: break;
    }
}


void moveForward(){

  digitalWrite(motorRightPin1, HIGH);
  digitalWrite(motorRightPin2, LOW);
  analogWrite(motorLpwm, motorSpeed);

  digitalWrite(motorLeftPin1, HIGH);
  digitalWrite(motorLeftPin2, LOW);
  analogWrite(motorRpwm, motorSpeed);

 // setMotorState(HIGH, LOW, LOW, HIGH);
}

void moveBackward(){
 digitalWrite(motorRightPin1, LOW);
 digitalWrite(motorRightPin2, HIGH);
 analogWrite(motorLpwm, motorSpeed);

 digitalWrite(motorLeftPin1, LOW);
 digitalWrite(motorLeftPin2, HIGH);
 analogWrite(motorRpwm, motorSpeed);
  //setMotorState(LOW, HIGH, HIGH, LOW);
}

void turnLeft(){
 digitalWrite(motorRightPin1, HIGH);
 digitalWrite(motorRightPin2, LOW);
 analogWrite(motorLpwm, motorSpeed-turn);

 digitalWrite(motorLeftPin1, LOW);
 digitalWrite(motorLeftPin2, LOW);
 analogWrite(motorRpwm, motorSpeed+turn);
  //setMotorState(LOW, HIGH, LOW, LOW);
}

void turnRight(){
  digitalWrite(motorRightPin1, LOW);
  digitalWrite(motorRightPin2, LOW);
  analogWrite(motorLpwm, motorSpeed+turn);

  digitalWrite(motorLeftPin1, HIGH);
  digitalWrite(motorLeftPin2, LOW);
  analogWrite(motorRpwm, motorSpeed-turn);
  //setMotorState(LOW, LOW, LOW, HIGH);
}


void carStop(){
  digitalWrite(motorRightPin1, LOW);
  digitalWrite(motorRightPin2, LOW);
  analogWrite(motorLpwm, 0);

  digitalWrite(motorLeftPin1, LOW);
  digitalWrite(motorLeftPin2, LOW);
  analogWrite(motorRpwm, 0);
 // setMotorState(LOW, LOW, LOW, LOW);
}



