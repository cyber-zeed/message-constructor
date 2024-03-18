# Message Constructor

The Message Constructor module provides a convenient way to construct messages with a timestamp and a variable number of arguments concatenated with "&" separator.

## Usage

### Include the Library

1. Include the `message_constructor.h` header file in your Arduino sketch.

#include "message_constructor.h"


2. Instantiate the MessageConstructor Object
   Instantiate an object of the MessageConstructor class.
   MessageConstructor messageConstructor;

3. Construct Messages
Use the constructMessage function to construct messages with a variable number of arguments.

// Example usage with different number of arguments
String message1 = messageConstructor.constructMessage("Variable1");
String message2 = messageConstructor.constructMessage("Var1", "Var2", "Var3");
String message3 = messageConstructor.constructMessage("A", "B", "C", "D", "E");
Print Messages
Print the constructed messages.

Serial.println("Constructed Messages:");
Serial.println(message1);
Serial.println(message2);
Serial.println(message3);

Output
Each constructed message follows the format:

@#<timestamp>#&<arg1>&<arg2>&...&<argN>#@

Where:
<timestamp> is the epoch timestamp in milliseconds.
<arg1>, <arg2>, ..., <argN> are the provided arguments separated by "&".
#@ indicates the end of the message.

Example Output

Constructed Messages:
@#<1000>#&Variable1&#@
@#<2000>#&Var1&Var2&Var3&#@
@#<3000>#&A&B&C&D&E&#@


License
This project is licensed under the MIT License - see the LICENSE file for details.
