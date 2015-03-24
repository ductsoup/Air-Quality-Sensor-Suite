
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

void setup () { 
  Serial.begin(115200);
  delay(5000);
  Serial.println(F("Hello world!"));

  pinMode(MQ2_A, INPUT); // 4v full scale or about 820
  pinMode(MQ2_D, INPUT); // active low
}

void loop() {
  int y = analogRead(MQ2_A);
  
  Serial.print(F("Alarm: "));
  Serial.print(digitalRead(MQ2_D) ? F("OFF") : F("ON ")); // Adjust the onboard pot to set threshold
  Serial.print(F(", "));

  Serial.print(y);
  Serial.print(F("/1024 (")); 
  Serial.print(5.0 * float(analogRead(MQ2_A)) / (1024.0 * 4.0));
  Serial.print(F("% FS)"));
  Serial.println();

  delay(1000ul);
}
