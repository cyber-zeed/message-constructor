// Test program for MessageConstructor library
// This will work both as a standalone C++ program and on Arduino with minor modifications

#include "message_constructor.h"
#include <iostream>

int main() {
    MessageConstructor mc;
    
    // Test with no arguments
    std::cout << "Message with no args: " << mc.constructMessage().c_str() << std::endl;
    
    // Test with one argument
    std::cout << "Message with one arg: " << mc.constructMessage("Hello").c_str() << std::endl;
    
    // Test with multiple arguments
    std::cout << "Message with multiple args: " << mc.constructMessage("Temperature", 25.5, "Celsius").c_str() << std::endl;
    
    // Test with different data types
    int sensorValue = 1023;
    float voltage = 3.3;
    std::cout << "Mixed data types: " << mc.constructMessage("Sensor:", sensorValue, "Voltage:", voltage, "OK").c_str() << std::endl;
    
    return 0;
}