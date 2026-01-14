#ifndef MESSAGE_CONSTRUCTOR_H
#define MESSAGE_CONSTRUCTOR_H

#ifdef ARDUINO
#include <Arduino.h>  // Include Arduino header for millis() and String
#else
#include <string>
#include <chrono>
// Define millis() equivalent for non-Arduino platforms
static inline unsigned long millis() {
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}
// Define String equivalent for non-Arduino platforms
using String = std::string;
// Define Arduino String-style constructor for numbers on non-Arduino platforms
template<typename T>
String StringFromNumber(T num) {
    return std::to_string(num);
}
// Specialization for const char* to avoid converting string literals to numbers
inline String StringFromNumber(const char* str) {
    return String(str);
}
// Specialization for String type to avoid double conversion
inline String StringFromNumber(const String& str) {
    return str;
}
#endif

class MessageConstructor {
public:
    // Constructor
    MessageConstructor() {}

    // Destructor
    ~MessageConstructor() {}

    // Function to construct the message with a variable number of arguments
    template<typename... Args>
    String constructMessage(Args&&... args) {
#ifdef ARDUINO
        String message = "@#<" + String(millis()) + ">#";
#else
        String message = "@#<" + StringFromNumber(millis()) + ">#";
#endif
        constructMessageHelper(message, std::forward<Args>(args)...); // Call helper function
        message += "#@";
        return message;
    }

private:
    // Helper function to concatenate arguments
    template<typename T, typename... Args>
    void constructMessageHelper(String& message, T&& arg, Args&&... args) {
#ifdef ARDUINO
        message += "&" + String(arg);
#else
        message += "&" + StringFromNumber(arg);
#endif
        constructMessageHelper(message, std::forward<Args>(args)...); // Recur for remaining arguments
    }

    // Base case for the recursive helper function
    void constructMessageHelper(String& message) {}
};

#endif /* MESSAGE_CONSTRUCTOR_H */
