#include <SoftwareSerial.h>
SoftwareSerial XBee(3, 2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  XBee.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available())
  { // If data comes in from serial monitor, send it out to XBee
    XBee.write(Serial.read());
  }
  if (XBee.available())
  { // If data comes in from XBee, send it out to serial monitor
    Serial.write(XBee.read());
  }
  
}
