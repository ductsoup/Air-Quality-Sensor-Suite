
//
// 2015-02-16
// Checkout sketch for MQ-2 gas sensor 
// Written by ductsoup, public domain
//
// MQ-2 Gas Sensor Module Smoke Methane Butane Detection For Arduino
// http://www.newegg.com/Product/Product.aspx?Item=9SIA2C51DB0450&cm_re=mq-2-_-295-0001-00066-_-Product
// 
// Sensor Datasheet
// http://seeedstudio.com/wiki/images/3/3f/MQ-2.pdf
//
// Vcc - 5V
// GND - Ground
// DOUT - Digital pin 12
// AOUT - Analog pin 0
//
#define MQ2_D  12
#define MQ2_A  A0  

#define CONSOLE
#ifdef CONSOLE
#include <Console.h>
#define emit(s) Console.print(s);
#define emitln(s) Console.println(s);
#else
#define emit(s) Serial.print(s);
#define emitln(s) Serial.println(s);
#endif

void setup () { 
#ifdef CONSOLE
  Bridge.begin();
  Console.begin();
  while (!Console);
#else
  Serial.begin(115200);
#endif

  emitln(F("Hello world!"));

  pinMode(MQ2_A, INPUT); // 4v full scale or about 820
  pinMode(MQ2_D, INPUT); // active low
}

void loop() {
  int y = analogRead(MQ2_A);
  
  emit(F("Alarm: "));
  emit(digitalRead(MQ2_D) ? F("OFF") : F("ON ")); // Adjust the onboard pot to set threshold
  emit(F(", "));

  emit(y);
  emit(F("/1024 (")); 
  emit(5.0 * float(analogRead(MQ2_A)) / (1024.0 * 4.0));
  emit(F("% FS)"));
  emitln();

  delay(1000ul);
}
