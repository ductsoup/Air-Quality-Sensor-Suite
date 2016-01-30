// Example testing sketch for communications
// Written by Ductsoup, public domain
// Updated to use Yun console
#define CONSOLE
#ifdef CONSOLE
#include <Console.h>
#define emit(s) Console.print(s);
#define emitln(s) Console.println(s);
#else
#define emit(s) Serial.print(s);
#define emitln(s) Serial.println(s);
#endif

void setup() {
#ifdef CONSOLE
  Bridge.begin();
  Console.begin();
  while (!Console);
#else
  Serial.begin(115200);
#endif
  delay(2000);
  emitln("Communications check!");
}

void loop() {
  emit(".");
  delay(2000);
}
