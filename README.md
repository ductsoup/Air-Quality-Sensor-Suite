#Air Quality Sensor Suite
An air quality sensor suite based on Open Source Hardware with Modbus TCP communications for interfacing with commercial SCADA and building automation solutions.

##Overview
This suite is designed to measure temperature, humidity (DHT22), particulate dust (PPD42NS or SM-PWM-01A) and the presence of fuel gases (MQ-2).

![AQSS Overview](/images/osh.png)

##Design Notes
At low concentrations it can be difficult to obtain a stable and reliable reading from the PPD42NS. To moderate that problem the Arduino sketch uses interrupt pins rather than `pulseIn(pin, LOW);` which can cause blocking. It also uses an adjustable smoothing filter technique commonly used with analog PLC inputs. Together these greatly improve the sensitivity and reliability of the particulate dust data.

The design incorporates a version of [Yun-ModbusTK-Example] (https://github.com/ductsoup/Yun-ModbusTK-Example) to communicate with the SCADA solution over Modbus TCP. 

A 3D printed enclosure design is available at [Thingiverse] (http://www.thingiverse.com/thing:1002168).
