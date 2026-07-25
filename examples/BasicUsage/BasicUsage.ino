#include <MessageConstructor.h>

MessageConstructor constructor;

void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  Serial.println(constructor.constructMessage("status", "ready"));
  Serial.println(constructor.constructMessage("temperature", 25.5, "C"));
  Serial.println(constructor.constructMessage("escaped", "A&B", "x#y"));
}

void loop() {}
