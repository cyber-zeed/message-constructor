#ifndef MESSAGE_CONSTRUCTOR_H
#define MESSAGE_CONSTRUCTOR_H

//#include <Arduino.h>  - Uncomment if using arduino

class MessageConstructor {
public:
    // Constructor
    MessageConstructor() {}

    // Destructor
    ~MessageConstructor() {}

    // Function to construct the message with a variable number of arguments
    template<typename... Args>
    String constructMessage(Args&&... args) {
        String message = "@#<" + String(millis()) + ">#";
        constructMessageHelper(message, std::forward<Args>(args)...); // Call helper function
        message += "#@";
        return message;
    }

private:
    // Helper function to concatenate arguments
    template<typename T, typename... Args>
    void constructMessageHelper(String& message, T&& arg, Args&&... args) {
        message += "&" + String(arg);
        constructMessageHelper(message, std::forward<Args>(args)...); // Recur for remaining arguments
    }

    // Base case for the recursive helper function
    void constructMessageHelper(String& message) {}
};

#endif /* MESSAGE_CONSTRUCTOR_H */
