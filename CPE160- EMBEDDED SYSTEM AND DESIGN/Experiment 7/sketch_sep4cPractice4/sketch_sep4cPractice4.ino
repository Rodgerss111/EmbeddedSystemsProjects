/*
* YL-100 sensor Example
* Based on "Soil Mositure Basic Example" by SparkFun Electronics, Joel Bartlett
* Released under the MIT License(http://opensource.org/licenses/MIT)
*/
int mositure = 0; // Value to store the humidity value
int YL100OUT = A0; // Variable for the number of the analog pin to which the sensor is connected
int YL100VCC = 2; // Variable for pin number for sensor power supply
void setup()
{
Serial.begin(9600); // Open the serial bus via USB
pinMode(YL100VCC, OUTPUT); // Set the power pin to the output
digitalWrite(YL100VCC, LOW); // Set the power level to LOW after power on
}
void loop()
{
Serial.print("Soil moisture = "); // Print the output line prefix
Serial.println(readYL100()); // Get the moisture value from the function and print it
delay(1000); // Delay in 5 seconds before the next data retrieval
}
int readYL100() // Function of reading data from the sensor
{
digitalWrite(YL100VCC, HIGH); // Turn on the sensor power
delay(10); // Delay of 10 milliseconds
mositure = analogRead(YL100OUT); // Read the value from the sensor pin OUT
digitalWrite(YL100VCC, LOW); // Turn off the power
return mositure; // Return the read value
}