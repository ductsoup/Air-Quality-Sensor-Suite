//
// 2015-02-16
// Checkout sketch for SM-PWM-01A particle sensor 
// Written by ductsoup, public domain
//
// Amphenol Advanced Sensors SM-PWM-01A
// http://www.digikey.com/product-detail/en/SM-PWM-01A/235-1372-ND/5012137
// Application Notes
// http://www.digikey.com/Web%20Export/Supplier%20Content/amphenol-advanced-sensors-45/pdf/amphenol-advanced-smart-sensor.pdf?redirected=1
// 
// Pin1 - GND
// Pin2 - OUTPUT P2 particles > 2um - Micro digital pin 9
// Pin3 - 5V
// Pin4 - OUTPUT P1 particles ~ 1um - Micro digital pin 10
// Pin5 - NC
//
#define P2  9
#define P1 10
#define SAMPLE_MS 10000ul
#define FILTER_WEIGHT 30.0
//
// Use interrupts to time low pulse occupancy because this class of devices notoriously 
// returns zeros at low concentrations. Using pulseIn(pin, LOW) can cause blocking 
// problems in the loop() function. 
//
// Here we're using pin change interrups to conserve dedicated hardware interrupt pins.
//
// http://www.howmuchsnow.com/arduino/airquality/grovedust/
//
// Also consider eliminating the constant term in the concentration calculation above if 
// using a smoothing filter. 
//
// http://plchowto.com/plc-filter/
//
int state09 = HIGH, state10 = HIGH;
unsigned long start09, start10; 
volatile unsigned long lpo09, lpo10; // low pulse occupancy in microseconds

unsigned long limit(unsigned long x) {
  // PPD42NS only, not required for this device 
  //  return (x < 10000ul || x > 90000ul) ? 0 : x;
  return x;
}

ISR (PCINT0_vect) {
  unsigned long us = micros();

  // determine which pins changed state and take appropriate action
  if (state09 != digitalRead(P2)) 
    if ((state09 = digitalRead(P2)) == LOW) 
      start09 = us;
    else 
      lpo09 += limit(us - start09);
  if (state10 != digitalRead(P1)) 
    if ((state10 = digitalRead(P1)) == LOW) 
      start10 = us;
    else 
      lpo10 += limit(us - start10);
} 

void setup () { 
  Serial.begin(115200);
  delay(5000ul);
  Serial.println(F("Hello world!"));

  // Enable pin change interrupt
  // Note: These values are specific to Arduino Micro, for other devices refer to:  
  // http://gammon.com.au/interrupts
  PCMSK0 |= bit (PCINT5);  // want pin  9
  PCMSK0 |= bit (PCINT6);  // want pin 10
  PCIFR  |= bit (PCIF0);   // clear any outstanding interrupts
  PCICR  |= bit (PCIE0);   // enable pin change interrupts for D8 to D13

  pinMode(9, INPUT);      
  pinMode(10, INPUT);
  // PPD42NS only, enabling pullup resistors is not required for this device
  // digitalWrite(9, HIGH);
  // digitalWrite(10, HIGH);

  delay(SAMPLE_MS); // wait for first sample
}

float conc09 = 0, conc10 = 0;

void loop() {
  float ratio, conc;
  
  ratio = 0.1 * float(lpo09) / float(SAMPLE_MS);
  conc = 1.1 * ratio * ratio * ratio  - 3.8 * ratio * ratio + 520 * ratio; // + 0.62;
  conc09 = (conc  + conc09 * (FILTER_WEIGHT - 1.0)) / FILTER_WEIGHT;
  Serial.print(ratio); 
  Serial.print(F("% >2um, low pulse occupancy time (us) = "));
  Serial.print(lpo09); 
  Serial.print(F(" concentration = "));
  Serial.println(conc);
  Serial.print(F("Filtered: "));
  Serial.println(conc09);
  lpo09 = 0;
  
  ratio = 0.1 * float(lpo10) / float(SAMPLE_MS);
  conc = 1.1 * ratio * ratio * ratio  - 3.8 * ratio * ratio + 520 * ratio; // + 0.62;
  conc10 = (conc  + conc10 * (FILTER_WEIGHT - 1.0)) / FILTER_WEIGHT;
  Serial.print(ratio); 
  Serial.print(F("% ~1um, low pulse occupancy time (us) = "));
  Serial.print(lpo10); 
  Serial.print(F(" concentration = "));
  Serial.println(conc);
  Serial.print(F("Filtered: "));
  Serial.println(conc10);
  lpo10 = 0;

  Serial.println();
  delay(SAMPLE_MS);
}

