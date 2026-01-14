/*
 * Example Arduino sketch demonstrating the MessageConstructor library
 */

#include "message_constructor.h"

MessageConstructor mc;

void setup() {
  Serial.begin(9600);
  
  // Wait for serial connection (useful for some Arduino boards)
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  Serial.println("MessageConstructor Library Demo");
}

void loop() {
  // Example 1: Message with no arguments
  Serial.println("Example 1 - No args:");
  Serial.println(mc.constructMessage());
  
  // Example 2: Message with one argument
  Serial.println("Example 2 - One arg:");
  Serial.println(mc.constructMessage("Hello"));
  
  // Example 3: Message with multiple arguments
  Serial.println("Example 3 - Multiple args:");
  Serial.println(mc.constructMessage("Temperature", 25.5, "Celsius"));
  
  // Example 4: Message with different data types
  int sensorValue = analogRead(A0);  // Read analog pin
  float voltage = sensorValue * (5.0 / 1023.0);
  Serial.println("Example 4 - Mixed data types:");
  Serial.println(mc.constructMessage("Sensor:", sensorValue, "Voltage:", voltage, "OK"));
  
  delay(2000); // Wait 2 seconds before next set of messages
}